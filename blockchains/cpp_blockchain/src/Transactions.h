//
// Created by KQ794TB on 28/10/2019.
//

#ifndef CPP_BLOCKCHAIN_TRANSACTIONS_H
#define CPP_BLOCKCHAIN_TRANSACTIONS_H

#include "cryptography.h"
#include <iostream>

static const uint32_t COINBASE_LOCK_TIME = 100;
static const uint32_t BITCOIN_FACTOR = 100000000;  // Satoshis


class UtxoSet;

struct ScriptSig {
    // Used to unlock previous output (specific ScriptPubKey)
    cryptography::Signature signature;
    CurvePoint publicKey;
};


class Output {
public:
    Output(uint64_t value, std::string address);
    [[nodiscard]] bool executeScriptPubKey(const ScriptSig &scriptSig, const Sha256Hash &transactionHash) const;
    [[nodiscard]] uint64_t getValue() const;
    [[nodiscard]] std::string getAddress() const;
private:
    uint64_t value;
    std::string address;
};


class Input {
public:
    Input(const Sha256Hash &prevOutputHash, uint16_t outputIndex, const ScriptSig &scriptsig);
    [[nodiscard]] std::string getStringRepr() const;

    [[nodiscard]] Output getUsedOutput(const UtxoSet &utxoSet) const;
    [[nodiscard]] bool isSpendable(const UtxoSet &utxoSet) const;
//    template <typename UtxoSet>
//    Output getUsedOutput(UtxoSet &&transactions) const;
//
//    template <typename UtxoSet>
//    bool isSpendable(UtxoSet &&transactions) const;

private:
    Sha256Hash prevOutputHash;
    uint16_t outputIndex;
    ScriptSig scriptSig;
};


class Transaction {
public:
    Transaction(std::vector<Input> inputs, std::vector<Output> outputs, uint32_t lockTime, int32_t version);
    [[nodiscard]] bool verify(int currentBlockHeight, const UtxoSet &utxoSet) const;
    [[nodiscard]] Sha256Hash getHash() const;
    [[nodiscard]] Output getOutput(int index) const;
    [[nodiscard]] std::vector<Output> getOutputs() const;

//    template <typename T, typename UtxoSet>
//    bool verify(T currentBlockHeight, UtxoSet &&transactions);

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


class UtxoSet {
public:
    UtxoSet();
    [[nodiscard]] std::vector<Output> getUtxosForAddress(const std::string &address) const;
    [[nodiscard]] int getSize() const;
    void update(const Transaction &transaction);

private:
    std::vector<Output> container;

    bool insertOutput(const Output &transaction);
    bool removeOutput(const std::string &hash);

};


//template <typename UtxoSet>
//Output Input::getUsedOutput(UtxoSet &&transactions) const {
//    try {
//        Transaction previousTransaction = transactions.at(cryptography::sha256HashToStr(prevOutputHash));
//        return previousTransaction.getOutput(outputIndex);
//    } catch (const std::out_of_range &error) {
//        throw std::invalid_argument("Output index out of range!");
//    }
//
//}

//template <typename UtxoSet>
//bool Input::isSpendable(UtxoSet &&transactions) const {
//    try {
//        Transaction previousTransaction = transactions.at(cryptography::sha256HashToStr(prevOutputHash));
//        Output output = previousTransaction.getOutput(outputIndex);
//        return output.getScriptPubKey().execute(scriptSig, prevOutputHash);
//    } catch (const std::out_of_range &error) {
//        std::cout << "Transaction " << cryptography::sha256HashToStr(prevOutputHash) << " not found in UTXO set!";
//        return false;
//    }
//}





//template <typename T, typename UtxoSet>
//bool Transaction::verify(T currentBlockHeight, UtxoSet &&transactions) {
//
//    // 1. If transaction is locked until some point in time.
//    if (lockTime > currentBlockHeight)
//        return false;
//
//    // 2. If there is lack of input or output
//    if (inputs.empty() || outputs.empty())
//        return false;
//
//    // 3. If any scriptSig in inputs does not executes with assiociated output.
//    // 4. If total amount of inputs satoshis is less than outputs to spend.
//
//    uint64_t totalInputsSatoshis = 0;
//    uint64_t totalOutputsSatoshis = 0;
//
//    for (auto &i : inputs) {
//        // TODO Simplify this!
//        if (!i.isSpendable(std::forward<UtxoSet>(transactions)))
//            return false;
//
//        Output output = i.getUsedOutput(std::forward<UtxoSet>(transactions));
//        totalInputsSatoshis += output.getValue();
//    }
//
//    for (auto &o : outputs)
//        totalOutputsSatoshis += o.getValue();
//
//    return totalInputsSatoshis >= totalOutputsSatoshis;
//}




//#include "Transactions.tpp" // To avoid linking errors with template methods
#endif //CPP_BLOCKCHAIN_TRANSACTIONS_H
