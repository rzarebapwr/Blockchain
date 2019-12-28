//
// Created by KQ794TB on 10/12/2019.
//

#ifndef CPP_BLOCKCHAIN_WALLET_H
#define CPP_BLOCKCHAIN_WALLET_H

#include "cryptography.h"
#include "Transactions.h"


class Wallet {
public:
    Wallet();
    Transaction createTransaction(uint64_t nSatoshis, const std::string &receiverAddress);



private:
    Uint256 privateKey;
    CurvePoint publicKey;
    std::string address;

    std::tuple<std::vector<Input>, uint64_t> getInputsNeeded(uint64_t nSatoshis, const UtxoSet &utxoSet);






};


#endif //CPP_BLOCKCHAIN_WALLET_H
