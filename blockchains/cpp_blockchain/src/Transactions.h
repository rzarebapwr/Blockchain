//
// Created by KQ794TB on 28/10/2019.
//

#ifndef CPP_BLOCKCHAIN_TRANSACTIONS_H
#define CPP_BLOCKCHAIN_TRANSACTIONS_H

#include "cryptography.h"
#include <iostream>
#include <map>

static const uint32_t COINBASE_LOCK_TIME = 100;
static const uint32_t BITCOIN_FACTOR = 100000000;  // Satoshis


class UtxoSet;


struct ScriptSig {
    ScriptSig(const Uint256 &privateKey, const Sha256Hash &txid);
    CurvePoint publicKey;
    cryptography::Signature signature;
};


class Input {
public:
    Input(const Sha256Hash &prevOutputHash, uint16_t outputIndex, const ScriptSig &scriptsig);
    [[nodiscard]] std::string getStringRepr() const;
    [[nodiscard]] Sha256Hash getPrevHash() const;
    [[nodiscard]] uint16_t getIndex() const;
    [[nodiscard]] ScriptSig getScriptSig() const;
    void setScriptSig(ScriptSig s);

private:
    Sha256Hash prevOutputHash;
    uint16_t outputIndex;
    ScriptSig scriptSig;
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


class Transaction {
public:
    Transaction(std::vector<Input> inputs, std::vector<Output> outputs, uint32_t lockTime, int32_t version);
    void sign(const Uint256 &privateKey);
    [[nodiscard]] bool verify(int currentBlockHeight, const UtxoSet &utxoSet) const;
    [[nodiscard]] Sha256Hash getHash() const;
    [[nodiscard]] std::vector<Input> getInputs() const;
    [[nodiscard]] std::vector<Output> getOutputs() const;

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
    Sha256Hash getHashToSign(size_t inputIndex) const;

};


#endif //CPP_BLOCKCHAIN_TRANSACTIONS_H
