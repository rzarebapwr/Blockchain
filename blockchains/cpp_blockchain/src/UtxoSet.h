//
// Created by KQ794TB on 22/12/2019.
//

#ifndef CPP_BLOCKCHAIN_UTXOSET_H
#define CPP_BLOCKCHAIN_UTXOSET_H

#include <iostream>
#include <map>

#include "Transactions.h"


struct Utxo {
    std::string address;
    uint64_t value;
};


class UtxoSet {
public:
    UtxoSet();
    void update(const Transaction &transaction);
    [[nodiscard]] bool contains(const Input &input) const;
    [[nodiscard]] size_t getSize() const;
    [[nodiscard]] uint64_t getTotal() const;

private:
    std::map<std::string, Utxo> container;

    void insertUtxo(const std::string &txHash, const Output &output, uint16_t index);
    void removeUsedUtxo(const Input &usedInput);
};


#endif //CPP_BLOCKCHAIN_UTXOSET_H
