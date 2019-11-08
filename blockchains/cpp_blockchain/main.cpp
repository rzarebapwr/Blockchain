#include <iostream>
//#include <utility>
#include <vector>
#include <sstream>
#include <type_traits>
#include <algorithm>
#include <tuple>

//#include "Block.h"
#include "cryptography.h"

#include "../lib/cryptoLib/Sha256.hpp"
#include "../lib/cryptoLib/Uint256.hpp"
#include "../lib/cryptoLib/CurvePoint.hpp"
#include "../lib/cryptoLib/Ecdsa.hpp"
#include "../lib/cryptoLib/Ripemd160.hpp"
#include "../lib/cryptoLib/FieldInt.hpp"
#include "../lib/cryptoLib/Base58Check.hpp"
#include "../lib/cryptoLib/ExtendedPrivateKey.hpp"




#include <ctime>




//#include "lib/secp256k1/secp256k1.h"
//#include "lib/secp256k1/secp256k1_preallocated.h"


//std::tuple<int, std::string, float> getTuple() {
//    return std::make_tuple(1, "Hello", 4.32);
//
//}

//void printMe(int x) {
//    x += 2;
//    std::cout << x;
//}


uint32_t changeEndianness(uint32_t value)
{
    uint32_t result = 0;
    result |= (value & 0x000000FF) << 24;
    result |= (value & 0x0000FF00) << 8;
    result |= (value & 0x00FF0000) >> 8;
    result |= (value & 0xFF000000) >> 24;
    return result;
}







//foo_x(x, x, y, d, z);    // OK
//foo_x(x, x, y, d, z, d); // error




//template<typename... Ts>
//using AllStrings = typename std::enable_if<std::conjunction<std::is_convertible<Ts, std::string>...>::value>::type;
//
//template<typename... Ts, typename = AllStrings<Ts...>>
//void f(Ts ... t) {
//    std::cout << "all types in pack are strings";
//}


// func is enabled if all Ts... have the same type as T



int main() {



//    std::vector<std::string> sortedToHash = {"foo1", "foo2", "foo3"};
//    std::vector<std::string> unsortedToHash = {"foo2", "foo3", "foo1"};
//
//    std::string s;
//
//    std::sort(unsortedToHash.begin(), unsortedToHash.end());
//
//    for (auto &&i : unsortedToHash) {
//        std::cout << i << std::endl;
//        s += i;
//    }
//
//    std::cout << s << "Hello";

//    auto [num1, name, num2] = getTuple();
//    std::cout << num1 << " " << name << " " << num2;


//    std::vector<int> vec{1, 2, 3, 4, 5};
//
//    for(const auto& i : vec) {
//        std::cout << i;
//    }




//    const auto vec = toString("hello", "hello2", 1, 2, 3, 4.0);
//
//    for(const auto& i : vec)
//        std::cout << i << ' ';
//
//    const auto vec2 = toString();
//
//    for(const auto& i : vec2)
//        std::cout << i << ' ';

//    avg(1.0, 1, 2.0, 2);
//    std::cout << func1(s);
//    f("1", "2", 1);
//    func("Hello");


//    std::string s = hash(1, 3, "Hello", "Hello3", "Hello2", "Hello223");
//    std::cout << s << '\n';
//

    std::string someData = "Hello ASASDASD";

    const Sha256Hash hash = cryptography::sha256(someData);
    std::string stringifiedHash = cryptography::sha256HashToString(hash);
    std::cout << "\nHash of " << someData << " ---> " << stringifiedHash << '\n';


    std::string privateKeyStr = cryptography::generateRandomHashStr();
    std::cout << "Private key: " << privateKeyStr;


    // Signing data
    const Sha256Hash dataHash = cryptography::sha256("Some Data", 1, 2, 3);

    const Uint256 privateKey = cryptography::generateRandomUint256();
    const CurvePoint publicKey = cryptography::generatePublicKey(privateKey);
    const Uint256 nonce = cryptography::generateRandomUint256();
    Uint256 r, s;


    bool dataSigned = Ecdsa::sign(privateKey, dataHash, nonce, r, s);
    std::cout << "\nData Signed: " << std::boolalpha << dataSigned;

    // Verify signature
    const Sha256Hash fakeHash = cryptography::sha256("Some Data", 2, 2, 3);
    bool verified = Ecdsa::verify(publicKey, fakeHash, r, s);

    std::cout << "\nSignature Verification: " << std::boolalpha << verified;


    // Generating Base58 adress from PublicKey
    uint8_t compressedPublicKey[33];
    publicKey.toCompressedPoint(compressedPublicKey);

    Sha256Hash publicKeyHash = Sha256::getHash(compressedPublicKey, 33);

    uint8_t publicKey160Hash[Ripemd160::HASH_LEN];
    Ripemd160::getHash(publicKeyHash.value, std::size(publicKeyHash.value), publicKey160Hash);

    char address[36];
    Base58Check::pubkeyHashToBase58Check(publicKey160Hash, 0x00, address);











     // Generating Adress














//    std::cout << siz;

//    std::string test = "55FF1897";
//    unsigned int x = std::stoul(test, nullptr, 16);
//
//    std::cout << '\n' << std::hex << x;
//    std::cout << '\n' << std::dec << x;
//
//    std::cout << "\nAfter changing Endianness:";
//
//    auto x2 = changeEndianness(x);
//
//    std::cout << '\n' << std::hex << x2;
//    std::cout << '\n' << std::dec << x2;









//    for(const auto &i : v) {
//        std::cout << i << '\n';
//    }
//
//    std::sort(v.begin(), v.end());
//
//    for(const auto &i : v) {
//        std::cout << i << '\n';
//    }

//      unsigned int now = std::time(nullptr);
//
//      std::cout << now;
//

//    uint8_t x;
//
//    std::cout << sizeof(x);



    return 0;
}