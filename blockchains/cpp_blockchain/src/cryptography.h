//
// Created by KQ794TB on 20/09/2019.
//

#ifndef CPP_BLOCKCHAIN_CRYPTOGRAPHY_H
#define CPP_BLOCKCHAIN_CRYPTOGRAPHY_H

#include <string>
#include <sstream>
#include <vector>
#include <iomanip>
#include <random>
#include <tuple>
#include <stdexcept>

#include "../lib/cryptoLib/Sha256.hpp"
#include "../lib/cryptoLib/Uint256.hpp"
#include "../lib/cryptoLib/CurvePoint.hpp"
#include "../lib/cryptoLib/Ecdsa.hpp"
#include "../lib/cryptoLib/Ripemd160.hpp"
#include "../lib/cryptoLib/FieldInt.hpp"
#include "../lib/cryptoLib/Base58Check.hpp"


namespace cryptography {

//    uint32_t changeEndianness(uint32_t value) {
//        uint32_t result = 0;
//        result |= (value & 0x000000FF) << 24;
//        result |= (value & 0x0000FF00) << 8;
//        result |= (value & 0x00FF0000) >> 8;
//        result |= (value & 0xFF000000) >> 24;
//        return result;
//    }


    struct Signature {
        Uint256 r;
        Uint256 s;
    };


    template <typename ... Ts>
    std::vector<uint8_t> vectorizeArgs(const Ts& ... args) {

        // TODO Consider refactor
        const auto toString = [](const auto &p) {
            std::stringstream ss;
            ss << p;
            return ss.str();
        };

        std::vector<std::string> v{toString(args)...};
        std::sort(v.begin(), v.end());

        std::string s;
        for (const auto &i : v)
            s += i;

        const char* dataToHash = s.data();
        std::vector<uint8_t> bytes(dataToHash, dataToHash + std::strlen(dataToHash));

        return bytes;
    }


    template <typename ... Ts>
    Sha256Hash sha256(const Ts& ... args) {

        std::vector<uint8_t> bytes = vectorizeArgs(args...);
        return Sha256::getHash(bytes.data(), bytes.size());
    }


    template <typename ... Ts>
    Sha256Hash doubleSha256(const Ts& ... args) {

        std::vector<uint8_t> bytes = vectorizeArgs(args...);
        return Sha256::getDoubleHash(bytes.data(), bytes.size());
    }




    std::string sha256HashToString(const Sha256Hash &hash) {

        Uint256 hashValue(hash.value);
        std::stringstream ss;

        int size = std::size(hashValue.value);

        for (int i=size - 1; i>=0; --i)
            ss << std::setfill('0') << std::hex << std::setw(8) << hashValue.value[i];

        return ss.str();
    }


    bool checkHashStr(const std::string &hashStr) {

        const uint8_t desiredLength = 64;
        std::string maxF(32, 'f');

        return !(hashStr.length() != desiredLength || hashStr.rfind(maxF, 0) == 0);
    }


    std::string generateRandomHashStr() {

        const uint8_t desiredLength = 64;
        const std::string availableChars = "0123456789abcdef";

        std::random_device random_device;
        std::mt19937 generator(random_device());
        std::uniform_int_distribution<> distribution(0, availableChars.size() - 1);

        while(true) {
            std::string hashString;

            for (std::size_t i = 0; i < desiredLength; ++i)
                hashString += availableChars[distribution(generator)];

            if (checkHashStr(hashString))
                return hashString;
        }
    }


    Uint256 generateRandomUint256() {
        const std::string randomHashStr = generateRandomHashStr();
        return Uint256(randomHashStr.data());
    }


    Uint256 generateRandomUint256(const std::string &randomHashStr) {
        if (!checkHashStr(randomHashStr))
            throw std::invalid_argument("Received string is not correct for random 256 bit number!");

        return Uint256(randomHashStr.data());
    }


    CurvePoint generatePublicKey(const Uint256 &privateKey) {
        return CurvePoint::privateExponentToPublicPoint(privateKey);
    }


    std::tuple<Uint256, CurvePoint> generateKeys() {
        const Uint256 privateKey = generateRandomUint256();
        const CurvePoint publicKey = generatePublicKey(privateKey);

        return {privateKey, publicKey};

    }


    Signature sign(const Uint256 &privateKey, const Sha256Hash &messageHash) {
        const Uint256 nonce = cryptography::generateRandomUint256();
        Uint256 r, s;

        bool signedProperly = Ecdsa::sign(privateKey, messageHash, nonce, r, s);

        if (!signedProperly)
            throw std::invalid_argument("Could not sign received message !");

        return {r, s};
    }


    bool verify(const CurvePoint &publicKey, const Sha256Hash &messageHash, const Signature &signature) {
        return Ecdsa::verify(publicKey, messageHash, signature.r, signature.s);
    }


    void generatePubKeyRipemd160(const CurvePoint &publicKey, uint8_t pubKeyRipemd160[Ripemd160::HASH_LEN]) {
        uint8_t compressedPublicKey[33];
        publicKey.toCompressedPoint(compressedPublicKey);
        Sha256Hash publicKeyHash = Sha256::getHash(compressedPublicKey, 33);
        Ripemd160::getHash(publicKeyHash.value, std::size(publicKeyHash.value), pubKeyRipemd160);
    }


    std::string getAddress(const uint8_t pubKeyRipemd160[Ripemd160::HASH_LEN]) {
        char address[36];
        Base58Check::pubkeyHashToBase58Check(pubKeyRipemd160, 0x00, address);
        return {address};
    }


    std::string generateAddress(const CurvePoint &publicKey) {
        uint8_t pubKeyRipemd160[Ripemd160::HASH_LEN];
        generatePubKeyRipemd160(publicKey, pubKeyRipemd160);
        return getAddress(pubKeyRipemd160);
    }


}


#endif //CPP_BLOCKCHAIN_CRYPTOGRAPHY_H
