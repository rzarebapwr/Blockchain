//
// Created by KQ794TB on 28/10/2019.
//

#include "Transactions.h"

/*
 * ScriptPubKey
 */
ScriptPubKey::ScriptPubKey(std::string address)
: address(std::move(address)){}


bool ScriptPubKey::execute(const ScriptSig &scriptSig, const Sha256Hash &transactionHash) {
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


std::string Transaction::getStringRepr() {
    std::stringstream s;
    s << version << nInputs << nOutputs << lockTime;

    for (const auto &i : inputs)
        s << i.getStringRepr();

    for (const auto &o: outputs)
        s << o.getStringRepr();

    return s.str();
}



