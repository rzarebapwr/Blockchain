//
// Created by KQ794TB on 10/12/2019.
//

#include "Wallet.h"
#include "UtxoSet.h"
#include "Transactions.h"


Wallet::Wallet()
: privateKey(cryptography::generateRandomUint256()),
publicKey(cryptography::generatePublicKey(privateKey)),
address(cryptography::generateAddress(publicKey)) {
}


Transaction Wallet::createTransaction(const UtxoSet &utxoSet, const std::map<std::string, uint64_t> &paymentMap, uint64_t fee) const {
    uint64_t nSatoshisToSpend = getNSatoshisToSpend(paymentMap);
    auto [inputs, nAvailable] = getInputsNeeded(nSatoshisToSpend, utxoSet);

    if (nAvailable < nSatoshisToSpend + fee)
        throw std::out_of_range("Cannot create transaction - not enough coins available!");

    std::vector<Output> outputs = createOutputs(paymentMap);
    outputs.emplace_back(getChangeOutput(nSatoshisToSpend, nAvailable, fee));

    Transaction tx{inputs, outputs, 0, 0};
    tx.sign(privateKey);
    return tx;
}


std::string Wallet::getAddress() const {
    return address;
}


uint64_t Wallet::getNSatoshisToSpend(const std::map<std::string, uint64_t> &paymentMap) const {
    uint64_t toSpend = 0;
    for (const auto &[key, val]: paymentMap)
        toSpend += val;
    return toSpend;

}


std::tuple<std::vector<Input>, uint64_t> Wallet::getInputsNeeded(uint64_t nSatoshis, const UtxoSet &utxoSet) const {
    std::map<std::string, Output> Utxos = utxoSet.getUtxosForAddress(address);
    std::vector<Input> inputs;

    uint64_t toSpend = 0;
    for (const auto &[key, val]: Utxos) {
        int pos = key.find_first_of('_');
        Sha256Hash prevHash = cryptography::hashStrToSha256(key.substr(0, pos));
        uint16_t outputIndex = std::stoi(key.substr(pos+1));

        inputs.emplace_back(Input{prevHash, outputIndex});
        toSpend += val.getValue();

        if (toSpend >= nSatoshis)
            break;
    }
    return {inputs, toSpend};
}


Output Wallet::getChangeOutput(uint64_t nSatoshisToSpend, uint64_t nAvailable, uint64_t fee) const {
    uint64_t coinsLeft = nAvailable - nSatoshisToSpend;
    uint64_t changeCoins = coinsLeft - fee;
    return {changeCoins, address};
}

std::vector<Output> Wallet::createOutputs(const std::map<std::string, uint64_t> &paymentMap) const {
    std::vector<Output> outputs;
    outputs.reserve(paymentMap.size());

    for (const auto &[key, val]: paymentMap)
        outputs.emplace_back(Output{val, key});
    return outputs;
}




