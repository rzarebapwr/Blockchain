//
// Created by KQ794TB on 20/09/2019.
//

#include "gtest/gtest.h"
#include "cryptography.h"


TEST(Sha256, Hashes_Properly) {
    std::string fooHash = "2c26b46b68ffc68ff99b453c1d30413413422d706483bfa0f98a5e886266e7ae";
    std::string hashedFoo = cryptography::hash("foo");

    ASSERT_STREQ(fooHash.c_str(), hashedFoo.c_str());
}

TEST(Sha256, Generates_Same_Hash_For_Same_Components) {

    std::string hash1 = cryptography::hash("Hello1", "Hello2", 1, 2);
    std::string hash2 = cryptography::hash("Hello2", 2, 1, "Hello1");

    ASSERT_STREQ(hash1.c_str(), hash2.c_str());
}