#include <iostream>
//#include <utility>
#include <utility>
#include <vector>
#include <sstream>
#include <algorithm>
#include <type_traits>
#include <map>

//#include "Block.h"

#include "cryptography.h"
//#include "Transactions.h"



#include <ctime>


class TestClass {
public:
    TestClass(int x, int y) : x(x), y(y) {};
//    TestClass() = default;

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

    // Simulation of transactions

//    std::map<std::string, Transaction> utxoMap;

    std::map<std::string, int> myMap;


    auto [minerPrivateKey, minerPublicKey] = cryptography::generateKeys();

    auto [privateKey2, publiKey2] = cryptography::generateKeys();
    auto [privateKey3, publiKey3] = cryptography::generateKeys();

    std::string minerAddress = cryptography::generateAddress(minerPublicKey);
    std::string address2 = cryptography::generateAddress(publiKey2);
    std::string address3 = cryptography::generateAddress(publiKey3);

//    Transaction coinBaseTransaction = Transaction::generateCoinBase(100, minerAddress);
//    std::string coinbaseHashStr = cryptography::sha256HashToStr(coinBaseTransaction.getHash());
//
////    transactions[coinbaseHashStr] = coinBaseTransaction;
//    utxoMap.try_emplace(coinbaseHashStr, coinBaseTransaction);
//
//
////     Transaction needs to have default constructor !
//
//
////     Miner Creates Output to user2 - sends 50 satoshis
//    ScriptPubKey scriptPubKey{address2};
//    Output output{100, scriptPubKey};
//
//    Sha256Hash prevHash = coinBaseTransaction.getHash();
//    cryptography::Signature sig = cryptography::sign(minerPrivateKey, prevHash);
//    ScriptSig scriptSig{sig, minerPublicKey};
//    Input input{prevHash, 0, scriptSig};
//    Transaction transaction{{input}, {output}, 0, 0};


//     Check if miner is able to spend that output
//    bool isSpendable = transaction.verify(0, utxoMap);
//    std::cout << "Is spendable: " << isSpendable;


    myMap.try_emplace("Hello", 2);
    int x = myMap.at("Hello2");











//    cryptography::Signature coinBaseSig = cryptography::sign(minerPrivateKey, coinBaseTransaction.getHash());
//    cryptography::Signature sig2 = cryptography::sign(privateKey, cryptography::sha256(0));
//    ScriptSig s{sig, publicKey};
//    ScriptSig s2{sig2, publicKey};
//
//    bool isSpendable = coinBaseTransaction.scriptPubKeyExecute(0, s);



//    std::cout << COINBASE_LOCK_TIME;


    // Verify transactions - move to Transaction class





    return 0;
}