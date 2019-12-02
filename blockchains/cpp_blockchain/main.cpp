#include <iostream>
//#include <utility>
#include <utility>
#include <vector>
#include <sstream>
#include <algorithm>
#include <type_traits>

//#include "Block.h"

#include "cryptography.h"
#include "Transactions.h"



#include <ctime>


class TestClass {
public:
    TestClass(int x, int y) : x(x), y(y) {};

    int getX() {
        return x;
    }

private:
    int x;
    int y;
    void someFunc(int x) {
        this->x += x;
    }

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

    Transaction coinBaseTransaction({fakeInput}, {output1}, lockTime, 0);






















































    return 0;
}