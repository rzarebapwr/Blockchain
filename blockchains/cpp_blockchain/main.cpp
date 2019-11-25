#include <iostream>
//#include <utility>
#include <utility>
#include <vector>
#include <sstream>
#include <algorithm>

//#include "Block.h"

#include "Transactions.h"
#include "cryptography.h"

#include "../lib/cryptoLib/Sha256.hpp"


#include <ctime>


struct ScriptSig {
    // Used to unlock previous output
    cryptography::Signature signature;
    CurvePoint publicKey;
};


class ScriptPubKey {
    // Used to lock output
public:
    explicit ScriptPubKey(std::string address)
    :address(std::move(address)){
    }
    bool execute(const ScriptSig &scriptSig) {
        std::string generatedAddress = cryptography::generateAddress(scriptSig.publicKey);
        return address == generatedAddress;
    }

private:
    const std::string address;
};

struct Input {
    Sha256Hash prevOutputHash;
    uint16_t outputIndex;
    ScriptSig scriptSig;
};


struct Output {
    uint64_t value{};
    ScriptPubKey scriptPubKey;
};


class Transaction {
public:
    Transaction(const std::vector<Input> &inputs, const std::vector<Output> &outputs, uint32_t lockTime, int32_t version);


private:
    Sha256Hash hash;
    int32_t version;
    uint16_t nInputs;
    uint16_t nOutputs;
    uint32_t lockTime;
    uint32_t size;
    std::vector<Input> inputs;
    std::vector<Output> outputs;

//    std::string getData() {
//        std::string s;
//
//        s += static_cast<char>(version);
//    }

};

int main() {


    auto [privateKey, publicKey] = cryptography::generateKeys();

//    auto [privateKey2, publiKey2] = cryptography::generateKeys();
//
    std::string minerAddress = cryptography::generateAddress(publicKey);
    std::cout << "Miner Address : " << minerAddress;

    // Generate Coinbase transaction - supply specific miner
    ScriptPubKey scriptPubKey1(minerAddress);
    Output output1{50, scriptPubKey1};

    // Generate fake input - doesn't matter for coinbase transaction
    auto [fakePrivateKey, fakePublicKey] = cryptography::generateKeys();
    Sha256Hash fakeHash = cryptography::sha256(0);
    cryptography::Signature signature = cryptography::sign(fakePrivateKey, fakeHash);
    Input fakeInput{cryptography::sha256(0), 0, ScriptSig{signature, fakePublicKey}};

    uint32_t lockTime = 100;

    std::string s;
    s += static_cast<char>(2);
    std::cout << '\n' << s;













































    return 0;
}