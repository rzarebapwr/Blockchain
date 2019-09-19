//
// Created by KQ794TB on 19/09/2019.
//

#include "gtest/gtest.h"
//#include "gmock/gmock.h"
#include "sha256.h"


TEST(SHA256, HashesProperly) {
    std::string fooHash = "2c26b46b68ffc68ff99b453c1d30413413422d706483bfa0f98a5e886266e7ae";
    std::string hashedFoo = sha256("foo");

    ASSERT_STREQ(fooHash.c_str(), hashedFoo.c_str());
}