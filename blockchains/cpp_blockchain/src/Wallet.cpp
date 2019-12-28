//
// Created by KQ794TB on 10/12/2019.
//

#include "Wallet.h"
#include "UtxoSet.h"


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




    }
}