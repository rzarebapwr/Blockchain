//
// Created by KQ794TB on 20/09/2019.
//

#include "gtest/gtest.h"
#include "cryptography.h"


TEST(Sha256, Hashes_Properly) {
    std::string properFooHash = "2c26b46b68ffc68ff99b453c1d30413413422d706483bfa0f98a5e886266e7ae";

    Sha256Hash fooHash = cryptography::sha256("foo");
    std::string fooHashed = cryptography::sha256HashToString(fooHash);

    ASSERT_STREQ(properFooHash.c_str(), fooHashed.c_str());
}

TEST(Sha256, Generates_Same_Hash_For_Different_Order) {

    Sha256Hash hash1 = cryptography::sha256("Hello1", "Hello2", 1, 2);
    Sha256Hash hash2 = cryptography::sha256("Hello2", 2, 1, "Hello1");

    std::string hash1str = cryptography::sha256HashToString(hash1);
    std::string hash2str = cryptography::sha256HashToString(hash2);

    ASSERT_STREQ(hash1str.c_str(), hash2str.c_str());
}

TEST(PrivateKey, Generates_Proper_PrivateKey) {

    std::string privateKey = cryptography::generatePrivateKeyString();

    EXPECT_EQ(privateKey.length(), 64);

}