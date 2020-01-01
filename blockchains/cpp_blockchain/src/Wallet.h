//
// Created by KQ794TB on 10/12/2019.
//

#ifndef CPP_BLOCKCHAIN_WALLET_H
#define CPP_BLOCKCHAIN_WALLET_H

#include <map>

#include "cryptography.h"
#include "Transactions.h"


class Wallet {
public:
    Wallet();
    [[nodiscard]] Transaction createTransaction(const UtxoSet &utxoSet, const std::map<std::string, uint64_t> &paymentMap, uint64_t fee) const;
    [[nodiscard]] std::string getAddress() const;

private:
    Uint256 privateKey;
    CurvePoint publicKey;
    std::string address;

    [[nodiscard]] uint64_t getNSatoshisToSpend(const std::map<std::string, uint64_t> &paymentMap) const;
    [[nodiscard]] std::tuple<std::vector<Input>, uint64_t> getInputsNeeded(uint64_t nSatoshis, const UtxoSet &utxoSet) const;
    [[nodiscard]] Output getChangeOutput(uint64_t nSatoshisToSpend, uint64_t nAvailable, uint64_t fee) const;
    [[nodiscard]] std::vector<Output> createOutputs(const std::map<std::string, uint64_t> &paymentMap) const;
};


#endif //CPP_BLOCKCHAIN_WALLET_H
