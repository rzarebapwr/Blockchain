//
// Created by KQ794TB on 28/10/2019.
//
#include <iostream>

#include "Transactions.h"


/*
 * ScriptPubKey
 */
ScriptPubKey::ScriptPubKey(std::string address)
: address(std::move(address)){}


bool ScriptPubKey::execute(const ScriptSig &scriptSig, const Sha256Hash &transactionHash) const {
    /*
     * Pseudo Script executing
     */
    CurvePoint publicKey = scriptSig.publicKey; // OP DUP
    std::string generatedAddress = cryptography::generateAddress(scriptSig.publicKey); // OP_HASH160
    bool opEqualVerify = (address == generatedAddress); // OP_EQUALVERIFY
    bool opCheckSig = cryptography::verifySignature(publicKey, transactionHash, scriptSig.signature); // OP_CHECKSIG
    return opEqualVerify && opCheckSig;
}


std::string ScriptPubKey::getAddress() const {
    return address;
}


/*
 * Input
 */
Input::Input(const Sha256Hash &prevOutputHash, uint16_t outputIndex, const ScriptSig &scriptsig)
: prevOutputHash(prevOutputHash), outputIndex(outputIndex), scriptSig(scriptsig){}


std::string Input::getStringRepr() const {
    std::stringstream ss;
    ss << cryptography::sha256HashToStr(prevOutputHash);
    ss << outputIndex;
    ss << cryptography::Uint256ToStr(scriptSig.signature.r);
    ss << cryptography::Uint256ToStr(scriptSig.signature.s);
    ss << cryptography::Uint256ToStr(Uint256{scriptSig.publicKey.x});
    ss << cryptography::Uint256ToStr(Uint256{scriptSig.publicKey.y});

    return ss.str();
}




/*
 * Output
 */
Output::Output(uint64_t value, ScriptPubKey scriptPubKey)
: value(value), scriptPubKey(std::move(scriptPubKey)){}


std::string Output::getStringRepr() const {
    return scriptPubKey.getAddress();
}

uint64_t Output::getValue() const {
    return value;
}

ScriptPubKey Output::getScriptPubKey() const {
    return scriptPubKey;
}


/*
 * Transaction
 */
Transaction::Transaction(std::vector<Input> inputs, std::vector<Output> outputs, uint32_t lockTime, int32_t version)
                         : inputs(std::move(inputs)), outputs(std::move(outputs)), lockTime(lockTime), version(version) {
    nInputs = inputs.size();
    nOutputs = outputs.size();
    hash = cryptography::doubleSha256(getStringRepr());
}


Sha256Hash Transaction::getHash() const {
    return hash;
}


std::string Transaction::getStringRepr() const {
    std::stringstream s;
    s << version << nInputs << nOutputs << lockTime;

    for (const auto &i : inputs)
        s << i.getStringRepr();

    for (const auto &o: outputs)
        s << o.getStringRepr();

    return s.str();
}


Output Transaction::getOutput(int index) const {
    try {
        Output output = outputs.at(index);
        return output;
    } catch (const std::out_of_range &error) {
        throw std::invalid_argument("Output index out of range!");
    }
}


Transaction Transaction::generateCoinBase(uint64_t nSatoshis, const std::string &minerAddress) {

    // Generate Coinbase transaction - supply specific miner
    ScriptPubKey scriptPubKey(minerAddress);
    Output output{nSatoshis, scriptPubKey};

    // Generate fake input - doesn't matter for coinbase transaction
    auto [privateKey, publicKey] = cryptography::generateKeys();
    Sha256Hash prevHash = cryptography::sha256(0);
    cryptography::Signature signature = cryptography::sign(privateKey, prevHash);
    Input fakeInput{prevHash, 0, ScriptSig{signature, publicKey}};

    return {{fakeInput}, {output}, COINBASE_LOCK_TIME, 0};
}


Output Input::getUsedOutput(const UtxoSet &utxoSet) const {

    // TODO try statement on UtxoSet site! remove from here!
    try {
        Transaction previousTransaction = utxoSet.getTransactionByHash(cryptography::sha256HashToStr(prevOutputHash));
        return previousTransaction.getOutput(outputIndex);
    } catch (const std::out_of_range &error) {
        throw std::invalid_argument("Output index out of range!");
    }

}


bool Input::isSpendable(const UtxoSet &utxoSet) const {
    try {
        Transaction previousTransaction = utxoSet.getTransactionByHash(cryptography::sha256HashToStr(prevOutputHash));
        Output output = previousTransaction.getOutput(outputIndex);
        return output.getScriptPubKey().execute(scriptSig, prevOutputHash);
    } catch (const std::out_of_range &error) {
        std::cout << "Transaction " << cryptography::sha256HashToStr(prevOutputHash) << " not found in UTXO set!";
        return false;
    }
}


bool Transaction::verify(int currentBlockHeight, const UtxoSet &utxoSet) const {

    // 1. If transaction is locked until some point in time.
    if (lockTime > currentBlockHeight)
        return false;

    // 2. If there is lack of input or output
    if (inputs.empty() || outputs.empty())
        return false;

    // 3. If any scriptSig in inputs does not executes with assiociated output.
    // 4. If total amount of inputs satoshis is less than outputs to spend.

    uint64_t totalInputsSatoshis = 0;
    uint64_t totalOutputsSatoshis = 0;

    for (auto &i : inputs) {
        // TODO Simplify this!
        if (!i.isSpendable(utxoSet))
            return false;

        // TODO std::forward rvalue reference
        Output output = i.getUsedOutput(utxoSet);
        totalInputsSatoshis += output.getValue();
    }

    for (auto &o : outputs)
        totalOutputsSatoshis += o.getValue();

    return totalInputsSatoshis >= totalOutputsSatoshis;
}


UtxoSet::UtxoSet()
: container(std::map<std::string, Transaction>()) {
}

Transaction UtxoSet::getTransactionByHash(const std::string &hash) const {
    return container.at(hash);
}

bool UtxoSet::insertTransaction(const Transaction &transaction) {
    std::string hashStrRepr = cryptography::sha256HashToStr(transaction.getHash());
    auto [it, result] = container.try_emplace(hashStrRepr, transaction);

    return result == 1;
}

bool UtxoSet::removeTransaction(const std::string &hash) {
    auto it = container.find(hash);
    if (it != container.end()) {
        container.erase(it);
        return true;
    }
    return false;
}

int UtxoSet::getSize() const {
    return container.size();
}






