//
// Created by KQ794TB on 22/12/2019.
//

#include "UtxoSet.h"

UtxoSet::UtxoSet()
        : container(std::map<std::string, Utxo>()) {
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
    std::stringstream s;
    s << cryptography::sha256HashToStr(input.getPrevHash()) << '_' << input.getIndex();
    auto it = container.find(s.str());
    return (it != container.end());
}


size_t UtxoSet::getSize() const {
    return container.size();
}


uint64_t UtxoSet::getTotal() const {
    uint64_t total = 0;

    for (const auto &[key, val]: container)
        total += val.value;
    return total;
}


void UtxoSet::insertUtxo(const std::string &txHash, const Output &output, uint16_t index) {
    std::stringstream s;
    s << txHash << '_' << index;
    std::string UtxoKey = s.str();

    Utxo utxo{output.getAddress(), output.getValue()};
    container.try_emplace(UtxoKey, utxo);
//    auto [it, result] = container.try_emplace(UtxoKey, utxo);
}


void UtxoSet::removeUsedUtxo(const Input &usedInput) {
    std::string hash = cryptography::sha256HashToStr(usedInput.getPrevHash());
    uint16_t index = usedInput.getIndex();

    std::stringstream s;
    s << hash << '_' << index;
    std::string utxoKey = s.str();

    auto it = container.find(utxoKey);
    if (it != container.end())
        container.erase(utxoKey);
}
