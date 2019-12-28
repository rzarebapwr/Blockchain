//
// Created by KQ794TB on 28/10/2019.
//
#include <iostream>

#include "Transactions.h"
#include "UtxoSet.h"



/*
 * ScriptSig
 */
ScriptSig::ScriptSig(const Uint256 &privateKey, const Sha256Hash &txid)
: publicKey(cryptography::generatePublicKey(privateKey)), signature(cryptography::sign(privateKey, txid)) {}



/*
 * Input
 */
Input::Input(const Sha256Hash &prevOutputHash, uint16_t outputIndex)
: prevOutputHash(prevOutputHash), outputIndex(outputIndex),
scriptSig(ScriptSig{cryptography::generateRandomUint256(), cryptography::sha256(0)}) {}


std::string Input::getStringRepr() const {
    std::stringstream ss;
    ss << cryptography::sha256HashToStr(prevOutputHash);
    ss << outputIndex;
//    ss << cryptography::Uint256ToStr(scriptSig.signature.r);
//    ss << cryptography::Uint256ToStr(scriptSig.signature.s);
//    ss << cryptography::Uint256ToStr(Uint256{scriptSig.publicKey.x});
//    ss << cryptography::Uint256ToStr(Uint256{scriptSig.publicKey.y});

    return ss.str();
}


Sha256Hash Input::getPrevHash() const {
    return prevOutputHash;
}


uint16_t Input::getIndex() const {
    return outputIndex;
}


ScriptSig Input::getScriptSig() const {
    return scriptSig;
}

void Input::setScriptSig(ScriptSig s) {
    scriptSig = s;
}


/*
 * Output
 */
Output::Output(uint64_t value, std::string address)
        : value(value), address(std::move(address)){}


bool Output::executeScriptPubKey(const ScriptSig &scriptSig, const Sha256Hash &transactionHash) const {
    /*
     * Pseudo Bitcoin Script stack execution
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
}


void Transaction::sign(const Uint256 &privateKey) {
    for (size_t i=0; i<inputs.size(); ++i) {
        Sha256Hash txid = getTxidToSign(i);
        inputs[i].setScriptSig(ScriptSig{privateKey, txid});
    }
    hash = cryptography::doubleSha256(getStringRepr());
}


bool Transaction::verify(int currentBlockHeight, const UtxoSet &utxoSet) const {

    // 1. If transaction is locked until some point in time.
    if (lockTime > currentBlockHeight)
        return false;

    // 2. If there is lack of input or output
    if (inputs.empty() || outputs.empty())
        return false;

    // 3. If any scriptSig (witness) does not match to assiosiated scriptPubKey
    // 4. If total amount of inputs satoshis is less than outputs to spend.
    uint64_t totalInputsSatoshis = 0;
    uint64_t totalOutputsSatoshis = 0;

    for (size_t i=0; i<inputs.size(); ++i) {
        if (!utxoSet.contains(inputs[i]))
            return false;

        Output usedOutput = utxoSet.getUsedOutput(inputs[i]);
        if (!usedOutput.executeScriptPubKey(inputs[i].getScriptSig(), getTxidToSign(i)))
            return false;
        totalInputsSatoshis += usedOutput.getValue();
    }
    for (auto &o : outputs)
        totalOutputsSatoshis += o.getValue();

    return totalInputsSatoshis >= totalOutputsSatoshis;
}


Sha256Hash Transaction::getHash() const {
    return hash;
}


std::vector<Input> Transaction::getInputs() const {
    return inputs;
}


std::vector<Output> Transaction::getOutputs() const {
    return outputs;
}


Transaction Transaction::generateCoinBase(uint64_t nSatoshis, const std::string &minerAddress) {

    // TODO to fix
    // Generate Coinbase transaction - supply specific miner
    Output output{nSatoshis, minerAddress};

    // Generate fake input - doesn't matter for coinbase transaction
    auto [privateKey, publicKey] = cryptography::generateKeys();
    Sha256Hash txid = cryptography::sha256(0);
    cryptography::Signature signature = cryptography::sign(privateKey, txid);
    Input fakeInput{txid, 0};

    return {{fakeInput}, {output}, COINBASE_LOCK_TIME, 0};
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


Sha256Hash Transaction::getTxidToSign(size_t inputIndex) const {
    // TODO consider zero out some information of the rest of inputs while signing
    Transaction t = *this; // copy of transaction
    Input signedInput = t.getInputs()[inputIndex];
    return cryptography::doubleSha256(t.getStringRepr());
}














