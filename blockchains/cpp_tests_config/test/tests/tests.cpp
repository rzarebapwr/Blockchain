//
// Created by KQ794TB on 11/09/2019.
//

#include <iostream>
#include "gtest/gtest.h"
//#include "gmock/gmock.h"
#include "Checkout.h"

class CheckoutTests : public testing::Test{
protected:
    Checkout checkout;
};


TEST_F(CheckoutTests, CanAddItemPrice) {
checkout.addItemPrice("milk", 2.00);
}

TEST_F(CheckoutTests, CanAddItem) {
checkout.addItem("milk");
}

TEST_F(CheckoutTests, ApplyDiscountRule) {
checkout.addDiscount("milk", 3, 1.50);

}

TEST_F(CheckoutTests, GetTotal) {
checkout.addDiscount("milk", 3, 1.50);
checkout.addItemPrice("milk", 2.00);
checkout.addItemPrice("beer", 3.00);

checkout.addItem("milk");
checkout.addItem("milk");
checkout.addItem("beer");
checkout.addItem("milk");

float total = checkout.calculateTotal();
ASSERT_EQ(total, 7.50);

}

TEST_F(CheckoutTests, ItemWithNoPriceThrowsException) {
ASSERT_THROW(checkout.addItem("Milk"), std::invalid_argument);
}


