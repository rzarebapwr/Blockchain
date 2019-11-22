#include <iostream>
//#include <utility>
#include <vector>
#include <sstream>
#include <algorithm>

//#include "Block.h"

#include "Transactions.h"
#include "cryptography.h"

#include "../lib/cryptoLib/Sha256.hpp"


#include <ctime>


class TestClass {
public:
    TestClass(std::string s1, std::string s2)
    :s1(std::move(s1)), s2(std::move(s2)){

    }

private:
    std::string s1;
    std::string s2;
};


std::string func() {
    return {"Hello"};
}


int main() {

    TestClass c(func(), func());
    // TODO make perfect forwarding in cryptography!
//    auto [privateKey, publiKey] = cryptography::generateKeys();
//    auto [privateKey2, publiKey2] = cryptography::generateKeys();
//
//    std::string address = cryptography::generateAddress(publiKey);
//    std::cout << address;




































    return 0;
}