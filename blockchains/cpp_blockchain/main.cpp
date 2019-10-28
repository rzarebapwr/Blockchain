#include <iostream>
//#include <utility>
#include <vector>
#include <sstream>
#include <type_traits>
#include <algorithm>
//
//#include "Block.h"
#include "cryptography.h"


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


template<typename... Ts>
std::enable_if<std::conjunction_v<std::is_convertible<Ts, std::string>...>>
func(const Ts& ...) {
    std::cout << "all types in pack are strings\n";
}

template <typename T, typename ... Ts, typename = std::enable_if_t<(... && std::is_convertible_v<Ts, std::string>)>>
std::string foo_x(const T& head, const Ts& ... args) {

    return "Hello";


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
    std::string s = hash(1, 3, 5, "Hello", "Hello3", "Hello2", "Hello223");
    std::cout << s;

//    for(const auto &i : v) {
//        std::cout << i << '\n';
//    }
//
//    std::sort(v.begin(), v.end());
//
//    for(const auto &i : v) {
//        std::cout << i << '\n';
//    }



    return 0;
}