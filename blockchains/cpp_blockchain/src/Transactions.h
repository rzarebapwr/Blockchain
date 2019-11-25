//
// Created by KQ794TB on 28/10/2019.
//

#ifndef CPP_BLOCKCHAIN_TRANSACTIONS_H
#define CPP_BLOCKCHAIN_TRANSACTIONS_H

#include "cryptography.h"

//struct ScriptSig {
//    // Used to unlock previous output
//    cryptography::Signature signature;
//    CurvePoint publicKey;
//};
//
//
//class ScriptPubKey {
//    // Used to lock output
//public:
//    explicit ScriptPubKey(const std::string &address);
//    bool execute(const ScriptSig &scriptSig);
//
//private:
//    const std::string address;
//};
//
//
//struct Input {
//    Sha256Hash prevOutputHash;
//    uint16_t outputIndex;
//    ScriptSig scriptSig;
//};
//
//
//struct Output {
//    uint64_t value;
//    ScriptPubKey scriptPubKey;
//};
//
//
//class Transaction {
//public:
//    Transaction(const std::vector<Input> &inputs, const std::vector<Output> &outputs, uint32_t lockTime, int32_t version);
//
//
//private:
//    Sha256Hash hash;
//    int32_t version;
//    uint16_t nInputs;
//    uint16_t nOutputs;
//    uint32_t lockTime;
//    uint32_t size;
//    std::vector<Input> inputs;
//    std::vector<Output> outputs;









//};


#endif //CPP_BLOCKCHAIN_TRANSACTIONS_H
