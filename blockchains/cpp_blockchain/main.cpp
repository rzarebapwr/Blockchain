#include <iostream>
//#include <utility>
#include <vector>
#include <sstream>
#include <type_traits>
#include <algorithm>
//
//#include "Block.h"
#include "cryptography.h"

#include "lib/cryptoLib/Sha256.hpp"
#include "lib/cryptoLib/Sha256Hash.hpp"
#include "lib/cryptoLib/Uint256.hpp"
#include "lib/cryptoLib/Ecdsa.hpp"
#include "lib/cryptoLib/CurvePoint.hpp"

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



template <typename ... Ts>
std::vector<std::string> toString(const Ts& ... args) {

  const auto toStringImpl = [](const auto &p){
      std::stringstream ss;
      ss << p;
      return ss.str();
  };

  return {toStringImpl(args)...};
}


template <typename ... Ts>
std::string hash(const Ts& ... args) {

  const auto toString = [](const auto &p){
      std::stringstream ss;
      ss << p;
      return ss.str();
  };

  std::vector<std::string> v {toString(args)...};
  std::sort(v.begin(), v.end());

  std::string s;
  for (const auto &i : v)
      s += i;

  return s;
}


uint32_t changeEndianness(uint32_t value)
{
    uint32_t result = 0;
    result |= (value & 0x000000FF) << 24;
    result |= (value & 0x0000FF00) << 8;
    result |= (value & 0x00FF0000) >> 8;
    result |= (value & 0xFF000000) >> 24;
    return result;
}


bool checkPrivateKeyStr(const std::string &privateKey) {

    const uint8_t desiredLength = 64;
    std::string maxF(32, 'f');

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

Uint256 generatePrivateKey(const std::string &privateKeyStr) {
    if (!checkPrivateKeyStr(privateKeyStr))
        throw std::invalid_argument("Received string is not correct for private key");

    return Uint256(privateKeyStr.data());
}

CurvePoint generatePublicKey(const Uint256 &privateKey) {
    return CurvePoint::privateExponentToPublicPoint(privateKey);
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

    std::string s = "Hello ASASDASD";

    const Sha256Hash hash = cryptography::sha256(s);
    std::string stringifiedHash = cryptography::sha256HashToString(hash);
    std::cout << "\nHash of " << s << " ---> " << stringifiedHash << '\n';


    std::string privateKeyStr = generatePrivateKeyStr();
    std::cout << "Private key: " << privateKeyStr;


    // Signing data
    const Sha256Hash dataHash = cryptography::sha256("Some Data", 1, 2, 3);

    Uint256 privateKey = generatePrivateKey();
    CurvePoint publicKey = generatePublicKey(privateKey);








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