//
// Created by KQ794TB on 16/09/2019.
//

#ifndef CPP_BLOCKCHAIN_BLOCK_H
#define CPP_BLOCKCHAIN_BLOCK_H

#include <string>
#include <utility>
#include <vector>


#include "Transactions.h"


//class Block {
//public:
//    Block(const std::string &prevBlockHash, const std::vector<Transaction> &transactions, uint32_t difficulty);
//    std::string mineBlock();
//
//    static Block getGenesisBlock();
//    static bool validateBlock(Block& block);
//
//private:
//    // Block Header
//    int32_t version_ = 1;
//    const std::string prevBlockHash_;
//    const std::string merkleRootHash_;
//    uint32_t timestamp_;
//    uint32_t difficulty_; //TODO make binary (?)
//    uint32_t nonce_;
//
//    uint32_t blockSize;
//    std::vector<Transaction> transactions_;
//    uint32_t nTransactions_;
//
//    std::string generateMerkleRoot();
//
//};


#endif //CPP_BLOCKCHAIN_BLOCK_H
