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


Transaction Wallet::createTransaction(const UtxoSet &utxoSet, uint64_t nSatoshis, const std::string &receiverAddress, uint64_t fee) const {
    /*
     * Simple Transaction scheme, one output plus change if needed.
     * TODO make it possible to create payroll payments scheme (multiple outputs)
     */
    auto [inputs, toSpend] = getInputsNeeded(nSatoshis, utxoSet);

    if (toSpend < nSatoshis + fee)
        throw std::out_of_range("Cannot create transaction - not enough coins available!");

    // TODO calculate change, make outputs methods
    // TODO simplify this
    uint64_t coinsLeft = toSpend - nSatoshis;
    uint64_t changeCoins = coinsLeft - fee;

    Output output1{nSatoshis, receiverAddress};
    Output changeOutput{changeCoins, address};
    std::vector<Output> outputs{output1, changeOutput};

    Transaction t{inputs, outputs, 0, 0};
    t.sign(privateKey);
    return t;
}


std::string Wallet::getAddress() const {
    return address;
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


