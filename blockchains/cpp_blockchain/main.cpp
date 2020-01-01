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
#include "Transactions.h"
#include "UtxoSet.h"
#include "Wallet.h"


int main() {


    // Simulation of transactions flow
    UtxoSet utxoSet;

    Wallet wallet1, wallet2, wallet3;
    std::string address1 = wallet1.getAddress(),
                address2 = wallet2.getAddress(),
                address3 = wallet3.getAddress();
    Transaction coinBaseTransaction = Transaction::generateCoinBase(100, address1);

    utxoSet.update(coinBaseTransaction);
    utxoSet.printState();

    std::map<std::string, uint64_t> paymentMap1{ {address2, 50} };
    Transaction transaction1 = wallet1.createTransaction(utxoSet, paymentMap1, 2);

    if (transaction1.verify(0, utxoSet))
        utxoSet.update(transaction1);

    utxoSet.printState();

    std::map<std::string, uint64_t> paymentMap2{ {address3, 20} };
    Transaction transaction2 = wallet2.createTransaction(utxoSet, paymentMap2, 2);

    if (transaction2.verify(0, utxoSet))
        utxoSet.update(transaction2);

    utxoSet.printState();


    return 0;
}