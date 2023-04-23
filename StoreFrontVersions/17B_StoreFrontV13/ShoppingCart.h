/* 
 * File:   ShoppingCart.h
 * Author: Josh Carlito
 *
 * Created on April 11, 2023, 7:16 PM
 */

#ifndef SHOPPINGCART_H
#define SHOPPINGCART_H
#include "StoreFront.h"
#include "Inventory.h"

class ShoppingCart {
private:
    Cart customerCart;
    InventoryClass inventory;
    int findCartItem(const CartItem & newItem);
public:

    ShoppingCart() {
        inventory.readInventory();
    }
    void addToCart(string itemName, int quantity);
    void removeFromCart(string itemName, int quantity);

    string getItemName(int index) {
        return customerCart.items[index].itemName;
    }

    int getQuantity(int index) {
        return customerCart.items[index].quantity;
    }

    float getCost(int index) {
        return customerCart.items[index].cost;
    }

    float getTotalCost() {
        return customerCart.totalCost;
    }

    int getTotalItems() {
        return customerCart.totalItems;
    }

    int getTotalQuantity() {
        return customerCart.totalQuantity;
    }

    Cart getShoppingCart() {
        return customerCart;
    }

    void updateInventory() {
        inventory.writeInventory();
    }

    void displayCart(string username) {
        cout << username << "'s SHOPPING CART" << endl << endl;
        cout << left << setw(25);
        cout << "ITEMS";
        cout << setw(25) << "QUANTITY";
        cout << setw(25) << "COST" << endl;
        cout << fixed << setprecision(2);
        for (const auto& item : customerCart.items) {
            cout << setw(25) << item.itemName;
            cout << setw(25) << item.quantity;
            cout << "$" << item.cost << endl;
        }

        cout << endl;
        cout << "TOTAL ITEMS: " << customerCart.totalItems << endl;
        cout << "TOTAL QUANTITY: " << customerCart.totalQuantity << endl;
        cout << "TOTAL COST: $" << customerCart.totalCost << endl;
        cout << endl;
    }
    
    void displayStore(){
        inventory.displayStore();
    }
};

#endif /* SHOPPINGCART_H */

