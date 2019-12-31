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
    [[nodiscard]] Transaction createTransaction(const UtxoSet &utxoSet, uint64_t nSatoshis,
                                                const std::string &receiverAddress, uint64_t fee) const;
    [[nodiscard]] std::string getAddress() const;

private:
    Uint256 privateKey;
    CurvePoint publicKey;
    std::string address;

    [[nodiscard]] std::tuple<std::vector<Input>, uint64_t> getInputsNeeded(uint64_t nSatoshis,
                                                                           const UtxoSet &utxoSet) const;
};


#endif //CPP_BLOCKCHAIN_WALLET_H
