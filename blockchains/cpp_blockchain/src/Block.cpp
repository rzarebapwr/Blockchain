//
// Created by KQ794TB on 16/09/2019.
//

#include "Block.h"
#include <utility>


Block::Block(std::string timestamp, std::string lastHash, std::string hash, std::string data)
             :
             timestamp(std::move(timestamp)),
             lastHash(std::move(lastHash)),
             hash(std::move(hash)),
             data(std::move(data))
             {

             }

Block Block::getGenesisBlock() {
    return Block("1", "1", "1", "1");
}

std::string Block::getTimestamp() const {
    return this->timestamp;
}

std::string Block::getLastHash() const {
    return this->lastHash;
}

std::string Block::getHash() const {
    return this->hash;
}

std::string Block::getData() const {
    return this->data;
}


