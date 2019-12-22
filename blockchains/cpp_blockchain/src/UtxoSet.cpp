//
// Created by KQ794TB on 22/12/2019.
//

#include "UtxoSet.h"

UtxoSet::UtxoSet()
        : container(std::map<std::string, Output>()) {
}


void UtxoSet::update(const Transaction &transaction) {
    std::string txHash = cryptography::sha256HashToStr(transaction.getHash());

    for (const auto &usedInput: transaction.getInputs())
        removeUsedUtxo(usedInput);

    std::vector<Output> outputs = transaction.getOutputs();
    for (size_t i=0; i<outputs.size(); ++i) {
        insertUtxo(txHash, outputs[i], i);
    }
}

bool UtxoSet::contains(const Input &input) const {
    auto it = container.find(getKey(input));
    return (it != container.end());
}


Output UtxoSet::getUsedOutput(const Input &input) const {
    std::string key = getKey(input);
    return container.at(key);
}


size_t UtxoSet::getSize() const {
    return container.size();
}


uint64_t UtxoSet::getTotal() const {
    uint64_t total = 0;

    for (const auto &[key, val]: container)
        total += val.getValue();
    return total;
}


std::string UtxoSet::getKey(const Input &input) const {
    std::string hash = cryptography::sha256HashToStr(input.getPrevHash());
    uint16_t index = input.getIndex();

    std::stringstream s;
    s << hash << '_' << index;
    return s.str();
}


void UtxoSet::insertUtxo(const std::string &txHash, const Output &output, uint16_t index) {
    std::stringstream s;
    s << txHash << '_' << index;
    std::string UtxoKey = s.str();

    container.try_emplace(UtxoKey, output);
//    auto [it, result] = container.try_emplace(UtxoKey, utxo);
}


void UtxoSet::removeUsedUtxo(const Input &usedInput) {
    std::string utxoKey = getKey(usedInput);

    auto it = container.find(utxoKey);
    if (it != container.end())
        container.erase(utxoKey);
}
