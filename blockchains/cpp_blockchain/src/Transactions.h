//
// Created by KQ794TB on 28/10/2019.
//

#ifndef CPP_BLOCKCHAIN_TRANSACTIONS_H
#define CPP_BLOCKCHAIN_TRANSACTIONS_H

#include "cryptography.h"
#include <map>
#include <iostream>

static const uint32_t COINBASE_LOCK_TIME = 100;
static const uint32_t BITCOIN_FACTOR = 100000000;  // Satoshis


struct ScriptSig {
    // Used to unlock previous output (specific ScriptPubKey)
    cryptography::Signature signature;
    CurvePoint publicKey;
};


class ScriptPubKey {
    // Used to lock output
public:
    explicit ScriptPubKey(std::string address);
    bool execute(const ScriptSig &scriptSig, const Sha256Hash &transactionHash);
    [[nodiscard]] std::string getAddress() const;
private:
    const std::string address;
};


class Input {
public:
    Input(const Sha256Hash &prevOutputHash, uint16_t outputIndex, const ScriptSig &scriptsig);
    [[nodiscard]] std::string getStringRepr() const;

    template <typename UtxoSet>
    bool isSpendable(UtxoSet &&transactions);

private:
    Sha256Hash prevOutputHash;
    uint16_t outputIndex;
    ScriptSig scriptSig;
};


// TODO Consider changing to struct?
class Output {
public:
    Output(uint64_t value, ScriptPubKey scriptPubKey);
    [[nodiscard]] std::string getStringRepr() const;
    [[nodiscard]] uint64_t getValue() const;
    [[nodiscard]] ScriptPubKey getScriptPubKey() const;

private:
    uint64_t value;
    ScriptPubKey scriptPubKey;
};


class Transaction {
public:
    Transaction(std::vector<Input> inputs, std::vector<Output> outputs, uint32_t lockTime, int32_t version);
    [[nodiscard]] Sha256Hash getHash() const;
    [[nodiscard]] Output getOutput(int index) const;


    template <typename T, typename UtxoSet>
    bool verify(T currentBlockHeight, UtxoSet &&transactions);


//    [[nodiscard]] bool scriptPubKeyExecute(int index, ScriptSig scriptSig) const;
    static Transaction generateCoinBase(uint64_t nSatoshis, const std::string &minerAddress);

private:
    Sha256Hash hash = cryptography::sha256(0);
    int32_t version;
    uint16_t nInputs;
    uint16_t nOutputs;
    uint32_t lockTime;
    std::vector<Input> inputs;
    std::vector<Output> outputs;

    [[nodiscard]] std::string getStringRepr() const;
};



template <typename UtxoSet>
bool Input::isSpendable(UtxoSet &&transactions) {
    try {
        Transaction previousTransaction = transactions.at(cryptography::sha256HashToStr(prevOutputHash));
        Output output = previousTransaction.getOutput(outputIndex);
        return output.getScriptPubKey().execute(scriptSig, prevOutputHash);
    } catch (const std::out_of_range &error) {
        std::cout << "Transaction " << cryptography::sha256HashToStr(prevOutputHash) << " not found in UTXO set!";
        return false;
    }
}


template <typename T, typename UtxoSet>
bool Transaction::verify(T currentBlockHeight, UtxoSet &&transactions) {

    // 1. If transaction is locked until some point in time
    if (lockTime > currentBlockHeight)
        return false;

    uint64_t totalInputsSatoshis = 0;

    // TODO Consider performance refactor,
    // TODO check total satoshis !
    for (auto &i : inputs) {
//        bool isSpendable = i.isSpendable(transactions);
//        if (!isSpendable)
        if (!i.isSpendable(std::forward<UtxoSet>(transactions)))
            return false;

    }
    return true;
}


//#include "Transactions.tpp" // To avoid linking errors with template methods
#endif //CPP_BLOCKCHAIN_TRANSACTIONS_H
