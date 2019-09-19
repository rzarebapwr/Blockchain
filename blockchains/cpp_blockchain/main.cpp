#include <iostream>
#include <utility>

#include "Block.h"
#include "sha256.h"


int main() {

    std::string input = "grape";
    std::string output1 = sha256(input);

    std::cout << "sha256('"<< input << "'):" << output1 << std::endl;


    return 0;
}