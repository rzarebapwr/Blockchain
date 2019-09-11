#include <iostream>
#include "Checkout.h"


int main() {

    Checkout checkout{};
    checkout.addItemPrice("Beer", 5.00);
    checkout.addItemPrice("Milk", 2.50);

    checkout.addItem("Milk");
    checkout.addItem("Milk");
    checkout.addItem("Milk");

    std::cout << checkout.calculateTotal();

}
