//
// Created by KQ794TB on 20/09/2019.
//

#include "gtest/gtest.h"
#include "cryptography.h"


TEST(Sha256, Hashes_Properly) {

    std::string properFooHash = "2c26b46b68ffc68ff99b453c1d30413413422d706483bfa0f98a5e886266e7ae";

    const Sha256Hash fooHash = cryptography::sha256("foo");
    std::string fooHashed = cryptography::sha256HashToString(fooHash);

    ASSERT_STREQ(properFooHash.c_str(), fooHashed.c_str());
}

TEST(Sha256, Generates_Same_Hash_For_Different_Order) {

    const Sha256Hash hash1 = cryptography::sha256("Hello1", "Hello2", 1, 2, 0x22, 'a');
    const Sha256Hash hash2 = cryptography::sha256("Hello2", 2, 0x22, 1, 'a', "Hello1");

    std::string hash1str = cryptography::sha256HashToString(hash1);
    std::string hash2str = cryptography::sha256HashToString(hash2);

    ASSERT_STREQ(hash1str.c_str(), hash2str.c_str());
}

TEST(Ecdsa, Sign_And_Verify_Message) {

    const Sha256Hash messageHash = cryptography::sha256("Hello", 1);
    const auto [privateKey, publicKey] = cryptography::generateKeys();

    const auto signature = cryptography::sign(privateKey, messageHash);
    bool verified = cryptography::verify(publicKey, messageHash, signature);

    const Sha256Hash fakeHash = cryptography::sha256("Hello2", 2);
    bool fakeDataVerified = cryptography::verify(publicKey, fakeHash, signature);

    const auto [privateKey2, publicKey2] = cryptography::generateKeys();
    bool fakePubKeyVerified = cryptography::verify(publicKey2, messageHash, signature);

    EXPECT_EQ(verified, true);
    EXPECT_EQ(fakeDataVerified, false);
    EXPECT_EQ(fakePubKeyVerified, false);
}

TEST(Ecdsa, Generates_Address) {

    const auto [privateKey, publicKey] = cryptography::generateKeys();

    uint8_t publicKeyRipemd160[Ripemd160::HASH_LEN];
    cryptography::generatePubKeyRipemd160(publicKey, publicKeyRipemd160);
    std::string address = cryptography::getAddress(publicKeyRipemd160);

    bool inheritedProperly = Base58Check::pubkeyHashFromBase58Check(address.data(),
            publicKeyRipemd160, nullptr);

    ASSERT_EQ(inheritedProperly, true);
}


