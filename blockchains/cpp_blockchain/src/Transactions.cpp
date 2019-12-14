//
// Created by KQ794TB on 28/10/2019.
//
#include <iostream>

#include "Transactions.h"


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


Output Input::getUsedOutput(const UtxoSet &utxoSet) const {
    Transaction previousTransaction = utxoSet.getTransactionByHash(cryptography::sha256HashToStr(prevOutputHash));
    return previousTransaction.getOutput(outputIndex);
}


bool Input::isSpendable(const UtxoSet &utxoSet) const {
    Transaction previousTransaction = utxoSet.getTransactionByHash(cryptography::sha256HashToStr(prevOutputHash));
    Output output = previousTransaction.getOutput(outputIndex);

}


/*
 * Output
 */
Output::Output(uint64_t value, std::string address)
: value(value), address(std::move(address)){}


bool Output::executeScriptPubKey(const ScriptSig &scriptSig, const Sha256Hash &transactionHash) const {
    /*
     * Pseudo Bitcoin Script executing
     */
    CurvePoint publicKey = scriptSig.publicKey; // OP DUP
    std::string generatedAddress = cryptography::generateAddress(scriptSig.publicKey); // OP_HASH160
    bool opEqualVerify = (address == generatedAddress); // OP_EQUALVERIFY
    bool opCheckSig = cryptography::verifySignature(publicKey, transactionHash, scriptSig.signature); // OP_CHECKSIG
    return opEqualVerify && opCheckSig;
}


uint64_t Output::getValue() const {
    return value;
}


std::string Output::getAddress() const {
    return address;
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

Sha256Hash Transaction::getHash() const {
    return hash;
}


Output Transaction::getOutput(int index) const {
    try {
        Output output = outputs.at(index);
        return output;
    } catch (const std::out_of_range &error) {
        throw std::invalid_argument("Output index out of range!");
    }
}

std::vector<Output> Transaction::getOutputs() const {
    return outputs;
}


std::string Transaction::getStringRepr() const {
    std::stringstream s;
    s << version << nInputs << nOutputs << lockTime;

    for (const auto &i : inputs)
        s << i.getStringRepr();

    for (const auto &o: outputs)
        s << o.getAddress();

    return s.str();
}





Transaction Transaction::generateCoinBase(uint64_t nSatoshis, const std::string &minerAddress) {

    // Generate Coinbase transaction - supply specific miner
    Output output{nSatoshis, minerAddress};

    // Generate fake input - doesn't matter for coinbase transaction
    auto [privateKey, publicKey] = cryptography::generateKeys();
    Sha256Hash prevHash = cryptography::sha256(0);
    cryptography::Signature signature = cryptography::sign(privateKey, prevHash);
    Input fakeInput{prevHash, 0, ScriptSig{signature, publicKey}};

    return {{fakeInput}, {output}, COINBASE_LOCK_TIME, 0};
}



/*
 * UtxoSet
 */
UtxoSet::UtxoSet()
: container(std::vector<Output>()) {
}


std::vector<Output> UtxoSet::getUtxosForAddress(const std::string &address) const {
    std::vector<Output> outputs;

    for (auto const& o: container) {
        if (o.getAddress() == address)
            outputs.emplace_back(o);
    }
    return outputs;
}


void UtxoSet::update(const Transaction &transaction) {





    std::vector<Output> outputs = transaction.getOutputs();
    container.insert(container.end(), outputs.begin(), outputs.end());
}

//bool UtxoSet::insertOutput(const Output &output) {
//    auto [it, result] = container.try_emplace(output.getAddress(), output);
//    return result == 1;
//}
//
//
//bool UtxoSet::removeTransaction(const std::string &hash) {
//    auto it = container.find(hash);
//    if (it != container.end()) {
//        container.erase(it);
//        return true;
//    }
//    return false;
//}

int UtxoSet::getSize() const {
    return container.size();
}






