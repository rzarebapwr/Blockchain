//
// Created by KQ794TB on 16/09/2019.
//

#include <iostream>
#include "gtest/gtest.h"
//#include "gmock/gmock.h"
#include "Block.h"


class BlockTests : public testing::Test {
protected:
    std::string timestamp = "1";
    std::string lastHash = "1";
    std::string hash = "1";
    std::string data = "Some data";
    Block block = Block(timestamp, lastHash, hash, data);
};

TEST_F(BlockTests, ReturnsProperGenesisBlock) {
    Block genesisBlock = Block::getGenesisBlock();
    std::string timestamp = genesisBlock.getTimestamp();

    ASSERT_STREQ("1", timestamp.c_str());
}