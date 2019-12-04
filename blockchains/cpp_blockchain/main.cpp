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

    [[nodiscard]] int getX() const {
        return x;
    }

    [[nodiscard]] int getY() const {
        return y;
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

    Transaction coinBaseTransaction = Transaction::generateCoinBase(100, minerAddress);

    Sha256Hash transactionHash = coinBaseTransaction.getHash();
    std::cout << '\n' << cryptography::sha256HashToStr(transactionHash);




    cryptography::Signature sig = cryptography::sign(privateKey, coinBaseTransaction.getHash());
    cryptography::Signature sig2 = cryptography::sign(privateKey, cryptography::sha256(0));
    ScriptSig s{sig, publicKey};
    ScriptSig s2{sig2, publicKey};

    bool isSpendable = coinBaseTransaction.scriptPubKeyExecute(0, s);

    std::cout << "Is spendable: " << isSpendable;

    std::cout << COINBASE_LOCK_TIME;




    return 0;
}