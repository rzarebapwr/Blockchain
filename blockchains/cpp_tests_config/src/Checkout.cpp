//
// Created by KQ794TB on 10/09/2019.
//

#include "Checkout.h"

void Checkout::addItemPrice(const std::string& item, float price) {
    this->pricesMap[item] = price;
}

void Checkout::addItem(const std::string& item) {
    auto it = this->pricesMap.find(item);
    if (it == this->pricesMap.end()) {
        throw std::invalid_argument("Item has no price specified!");
    }

    this->itemsCountsMap[item]++;
}

float Checkout::calculateItem(const std::string &item, int itemCount) {
    /*
     * Calculates total for particular item, based on counts and applied discount
     */

    float totalItem = 0;
    auto iter = this->discountsMap.find(item);

    if (iter != this->discountsMap.end()) {
        Discount discount = iter->second;

        if (itemCount >= discount.minItemCount) {
            totalItem += discount.priceAfterDiscount * float(itemCount);
        }
        else totalItem += this->pricesMap[item];
    }
    else totalItem += this->pricesMap[item];

    return totalItem;
}

float Checkout::calculateTotal() {

    for (const auto &mapPair : this->itemsCountsMap) {
        std::string item = mapPair.first;
        int itemCount = mapPair.second;

        this->total += this->calculateItem(item, itemCount);
    }
    return this->total;

}

void Checkout::addDiscount(const std::string& item, int itemCount, float priceAfterDiscount) {
    Discount discount{};
    discount.minItemCount = itemCount;
    discount.priceAfterDiscount = priceAfterDiscount;
    this->discountsMap[item] = discount;
}


