//
// Created by KQ794TB on 20/09/2019.
//

#ifndef CPP_BLOCKCHAIN_CRYPTOGRAPHY_H
#define CPP_BLOCKCHAIN_CRYPTOGRAPHY_H

#include <string>
#include <vector>

#include "../lib/sha256/sha256.h"


namespace cryptography {

    template <typename ... Ts>
    std::string hash(const Ts& ... args) {

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

        return sha256(s);
    }

}


#endif //CPP_BLOCKCHAIN_CRYPTOGRAPHY_H
