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
#include <type_traits>

#include "../lib/cryptoLib/Sha256.hpp"
#include "../lib/cryptoLib/Uint256.hpp"
#include "../lib/cryptoLib/CurvePoint.hpp"
#include "../lib/cryptoLib/Ecdsa.hpp"
#include "../lib/cryptoLib/Ripemd160.hpp"
#include "../lib/cryptoLib/FieldInt.hpp"
#include "../lib/cryptoLib/Base58Check.hpp"


namespace cryptography {

    struct Signature {
        Uint256 r;
        Uint256 s;
    };


    template <typename ... Args>
    inline std::vector<uint8_t> serializeArgs(Args &&... args) {
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


    template <typename ... Args>
    inline Sha256Hash sha256(Args&& ... args) {
        std::vector<uint8_t> bytes = serializeArgs(std::forward<Args>(args)...);
        return Sha256::getHash(bytes.data(), bytes.size());
    }


    template <typename ... Args>
    inline Sha256Hash doubleSha256(Args&& ... args) {
        std::vector<uint8_t> bytes = serializeArgs(std::forward<Args>(args)...);
        return Sha256::getDoubleHash(bytes.data(), bytes.size());
    }


    inline std::string Uint256ToStr(const Uint256 &x) {
        std::stringstream ss;
        int size = std::size(x.value);

        for (int i=size - 1; i>=0; --i)
            ss << std::setfill('0') << std::hex << std::setw(8) << x.value[i];
//        for (int i=0; i<size; ++i)
//            ss << std::setfill('0') << std::hex << std::setw(8) << x.value[i];
        return ss.str();
    }


    inline std::string sha256HashToStr(const Sha256Hash &hash) {
        return Uint256ToStr(Uint256{hash.value});
    }


    inline bool checkHashStr(const std::string &hashStr) {
        const uint8_t desiredLength = 64;
        std::string maxF(32, 'f');

        return !(hashStr.length() != desiredLength || hashStr.rfind(maxF, 0) == 0);
    }


    inline std::string generateRandomHashStr() {
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

    inline Uint256 generateRandomUint256() {
        const std::string randomHashStr = generateRandomHashStr();
        return Uint256(randomHashStr.data());
    }


    inline Uint256 generateRandomUint256(const std::string &randomHashStr) {
        if (!checkHashStr(randomHashStr))
            throw std::invalid_argument("Received string is not correct for random 256 bit number!");

        return Uint256(randomHashStr.data());
    }


    inline CurvePoint generatePublicKey(const Uint256 &privateKey) {
        return CurvePoint::privateExponentToPublicPoint(privateKey);
    }


    inline std::tuple<Uint256, CurvePoint> generateKeys() {
        const Uint256 privateKey = generateRandomUint256();
        const CurvePoint publicKey = generatePublicKey(privateKey);

        return {privateKey, publicKey};
    }


    inline Signature sign(const Uint256 &privateKey, const Sha256Hash &messageHash) {
        const Uint256 nonce = generateRandomUint256();
        Uint256 r, s;

        bool signedProperly = Ecdsa::sign(privateKey, messageHash, nonce, r, s);

        if (!signedProperly)
            throw std::invalid_argument("Could not sign received message !");
        return {r, s};
    }


    inline bool verifySignature(const CurvePoint &publicKey, const Sha256Hash &messageHash, const Signature &signature) {
        return Ecdsa::verify(publicKey, messageHash, signature.r, signature.s);
    }


    inline void generatePubKeyRipemd160(const CurvePoint &publicKey, uint8_t pubKeyRipemd160[Ripemd160::HASH_LEN]) {
        uint8_t compressedPublicKey[33];
        publicKey.toCompressedPoint(compressedPublicKey);
        Sha256Hash publicKeyHash = Sha256::getHash(compressedPublicKey, 33);
        Ripemd160::getHash(publicKeyHash.value, std::size(publicKeyHash.value), pubKeyRipemd160);
    }


    inline std::string getAddressFromRipemd160(const uint8_t *pubKeyRipemd160) {
        char address[36];
        Base58Check::pubkeyHashToBase58Check(pubKeyRipemd160, 0x00, address);
        return {address};
    }


    inline std::string generateAddress(const CurvePoint &publicKey) {
        uint8_t pubKeyRipemd160[Ripemd160::HASH_LEN];
        generatePubKeyRipemd160(publicKey, pubKeyRipemd160);
        return getAddressFromRipemd160(pubKeyRipemd160);
    }

}




#endif //CPP_BLOCKCHAIN_CRYPTOGRAPHY_H
