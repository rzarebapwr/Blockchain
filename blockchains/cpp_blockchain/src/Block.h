//
// Created by KQ794TB on 16/09/2019.
//

#ifndef CPP_BLOCKCHAIN_BLOCK_H
#define CPP_BLOCKCHAIN_BLOCK_H

#include <string>
#include <utility>


struct BlockData {
    std::string data;
};


class Block {
public:
    Block(std::string timestamp, std::string lastHash, std::string hash, BlockData data);
    std::string getTimestamp() const;
    std::string getLastHash() const;
    std::string getHash() const;
    BlockData getData() const;

    static Block getGenesisBlock();

private:
    std::string timestamp;
    std::string lastHash;
    std::string hash;
    BlockData data;

};


#endif //CPP_BLOCKCHAIN_BLOCK_H
