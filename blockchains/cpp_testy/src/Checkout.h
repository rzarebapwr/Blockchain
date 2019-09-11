//
// Created by KQ794TB on 10/09/2019.
//
#include <string>
#include <map>


#ifndef CPP_TESTY_CHECKOUT_H
#define CPP_TESTY_CHECKOUT_H


class Checkout {
public:
    void addItemPrice(const std::string& item, float price);
    void addItem(const std::string& item);
    float calculateTotal();
    void addDiscount(const std::string& item, int itemCount, float priceAfterDiscount);

private:
    struct Discount {
        int minItemCount;
        float priceAfterDiscount;
    };
    std::map<std::string, float> pricesMap;
    std::map<std::string, Discount> discountsMap;
    std::map<std::string, int> itemsCountsMap;
    float total = 0.0;
    float calculateItem(const std::string& item, int itemCount);

};


#endif //CPP_TESTY_CHECKOUT_H
