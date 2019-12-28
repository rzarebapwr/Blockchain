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


Transaction Wallet::createTransaction(uint64_t nSatoshis, const std::string &receiverAddress) {

}


std::tuple<std::vector<Input>, uint64_t> Wallet::getInputsNeeded(uint64_t nSatoshis, const UtxoSet &utxoSet) {
    std::map<std::string, Output> Utxos = utxoSet.getUtxosForAddress(address);
    std::vector<Input> inputs;

    uint64_t toSpend = 0;
    for (const auto &[key, val]: Utxos) {
        int pos = key.find_first_of('_');
        Sha256Hash prevHash = cryptography::hashStrToSha256(key.substr(0, pos));
        uint16_t index = std::stoi(key.substr(pos+1));

        inputs.emplace_back(Input{prevHash, index});
        toSpend += val.getValue();

        if (toSpend >= nSatoshis)
            break;
    }
    return {inputs, toSpend};
}