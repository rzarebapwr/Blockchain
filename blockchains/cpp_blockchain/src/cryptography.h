//
// Created by KQ794TB on 20/09/2019.
//

#ifndef CPP_BLOCKCHAIN_CRYPTOGRAPHY_H
#define CPP_BLOCKCHAIN_CRYPTOGRAPHY_H

#include <string>
#include <vector>
#include <iomanip>
#include <random>
#include <tuple>

#include "../lib/cryptoLib/Sha256.hpp"
#include "../lib/cryptoLib/Uint256.hpp"
#include "../lib/cryptoLib/CurvePoint.hpp"
#include "../lib/cryptoLib/Ecdsa.hpp"
#include "../lib/cryptoLib/Ripemd160.hpp"
#include "../lib/cryptoLib/FieldInt.hpp"
#include "../lib/cryptoLib/Base58Check.hpp"


namespace cryptography {

//    template <typename ... Ts>
//    std::string hash(const Ts& ... args) {
//
//        const auto toString = [](const auto &p) {
//            std::stringstream ss;
//            ss << p;
//            return ss.str();
//            };
//
//        std::vector<std::string> v {toString(args)...};
//        std::sort(v.begin(), v.end());
//
//        std::string s;
//        for (const auto &i : v)
//            s += i;
//
//        return sha256(s);
//    }


    template <typename ... Ts>
    Sha256Hash sha256(const Ts& ... args) {

        // TODO Consider refactor
        const auto toString = [](const auto &p) {
            std::stringstream ss;
            ss << p;
            return ss.str();
        };

        std::vector<std::string> v {toString(args)...};
        std::sort(v.begin(), v.end());

        std::string s;
        for (const auto &i : v)
            s += i;

        const char* dataToHash = s.data();
        std::vector<uint8_t> bytes(dataToHash, dataToHash + std::strlen(dataToHash));

        return Sha256::getHash(bytes.data(), bytes.size());
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









}


#endif //CPP_BLOCKCHAIN_CRYPTOGRAPHY_H
