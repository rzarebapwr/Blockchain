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


int main() {

    auto [privateKey, publiKey] = cryptography::generateKeys();
    auto [privateKey2, publiKey2] = cryptography::generateKeys();

    Sha256Hash someHash = cryptography::doubleSha256("asd", "123");

























    return 0;
}