//
// Created by KQ794TB on 16/09/2019.
//

#ifndef CPP_BLOCKCHAIN_BLOCK_H
#define CPP_BLOCKCHAIN_BLOCK_H

#include <string>
#include <utility>


class Block {
public:
    Block(std::string timestamp, std::string lastHash, std::string hash, std::string data);
    std::string getTimestamp() const;
    [[nodiscard]] std::string getLastHash() const;
    std::string getHash() const;
    std::string getData() const;

    static Block getGenesisBlock();

private:
    std::string timestamp;
    std::string lastHash;
    std::string hash;
    std::string data;

};


#endif //CPP_BLOCKCHAIN_BLOCK_H
