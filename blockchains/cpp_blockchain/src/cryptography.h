//
// Created by KQ794TB on 20/09/2019.
//

#ifndef CPP_BLOCKCHAIN_CRYPTOGRAPHY_H
#define CPP_BLOCKCHAIN_CRYPTOGRAPHY_H

#include <string>
#include <vector>
#include <iomanip>
#include <random>

#include "../lib/cryptoLib/Sha256.hpp"
#include "../lib/cryptoLib/Uint256.hpp"
#include "../lib/cryptoLib/CurvePoint.hpp"
#include "../lib/cryptoLib/Ecdsa.hpp"


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

    bool checkPrivateKeyStr(const std::string &privateKey) {

        const uint8_t desiredLength = 64;
        const std::string maxF(32, 'f');

        return !(privateKey.length() != desiredLength || privateKey.rfind(maxF, 0) == 0);
    }


    std::string generatePrivateKeyStr() {

        const uint8_t desiredLendth = 64;
        const std::string availableChars = "0123456789abcdef";

        std::random_device random_device;
        std::mt19937 generator(random_device());
        std::uniform_int_distribution<> distribution(0, availableChars.size() - 1);

        while(true) {
            std::string privateKey;

            for (std::size_t i = 0; i < desiredLendth; ++i)
                privateKey += availableChars[distribution(generator)];

            if (checkPrivateKeyStr(privateKey))
                return privateKey;
        }
    }

    Uint256 generatePrivateKey() {
        const std::string privateKeyStr = generatePrivateKeyStr();
        return Uint256(privateKeyStr.data());
    }

//    CurvePoint generatePublicKey(const Uint256 &privateKey) {
//        return CurvePoint::privateExponentToPublicPoint(privateKey);
//    }



}


#endif //CPP_BLOCKCHAIN_CRYPTOGRAPHY_H
