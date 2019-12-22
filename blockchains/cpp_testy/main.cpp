#include <iostream>
#include "Checkout.h"

#include <vector>
#include <set>
#include <string>
#include <sstream>




int main() {

//    Checkout checkout{};
//    checkout.addItemPrice("Beer", 5.00);
//    checkout.addItemPrice("Milk", 2.50);
//
//    checkout.addItem("Milk");
//    checkout.addItem("Milk");
//    checkout.addItem("Milk");
//
//    std::cout << checkout.calculateTotal();

    std::vector<int> v1{1, 2, 3};
//    std::vector<int> v2{1, 2, 3};
//
//    auto x = v1.insert(v1.end(), v2.begin(), v2.end());
//
//    for (const auto &i: v1) {
//        if (i == 3)
//            v1.erase(v1.begin() + i-1);
//
//    }
//
//    for (const auto &i: v1) {
//        std::cout << i;
//
//    }

    std::map<std::string, int> map;
    auto [it, result] = map.try_emplace("Hello", 2);
    if (!result)
        std::cout << "Fuck you";

    for (const auto &[key, val]: map) {
        std::cout << key << " --> " << val;

    }







}
