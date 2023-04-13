/* 
 * File:   Customer.h
 * Author: Josh Carlito
 *
 * Created on April 11, 2023, 7:14 PM
 */

#ifndef CUSTOMER_H
#define CUSTOMER_H
#include "StoreFront.h"
#include "ShoppingCart.h"

class CustomerClass {
private:
    Customer customer;
    ShoppingCart cart;
public:

    CustomerClass(string name) {
        customer.username = name;
    }

    void setShoppingCart() {
        customer.cart = cart.getShoppingCart();
    }

    Customer getCustomer() {
        return customer;
    }
    void displayCart();
    void displayStore(){
        cart.displayStore();
    }
    void displayStoreMenu();

    void addToCart(const string& itemName, int quantity) {
        cart.addToCart(itemName, quantity);
    }

    void updateInventory() {
        cart.updateInventory();
    }
    
    void removeFromCart(const string& itemName, int quantity) {
        cart.removeFromCart(itemName, quantity);
    }
};

#endif /* CUSTOMER_H */

