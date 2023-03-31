/* 
 * File:   main.cpp
 * Author: Josh Carlito
 *
 * Created on March 31, 2023, 1:30 PM
 * Purpose: Create a simple interface with no files and completely procedural
 * Version: 5, Create UI
 */

#include "StoreFront.h"
#include "SignIn.h"

void fillInventory(vector<Inventory>& items);
void displayInventory(const vector<Inventory>& inventory);
void emptyInventory(vector<Inventory>& inventory, int item);
void fillShoppingCart(ShoppingCart& cart, vector<Inventory>& inventory);
void displayCart(const ShoppingCart cart, const string username);
void setUsername(Customer& customer, string username);
void setCart(Customer& customer, ShoppingCart cart);

int main(int argc, char** argv) {
    srand(static_cast<unsigned int> (time(0)));
    Customer customer;
    vector<Inventory> items;
    ShoppingCart cart;

    setUsername(customer, "test");
    fillInventory(items);
    fillShoppingCart(cart, items);
    setCart(customer, cart);
    displayCart(customer.cart, customer.username);




    return 0;
}

void setUsername(Customer& customer, string username) {
    customer.username = username;
}

void setCart(Customer& customer, ShoppingCart cart) {
    customer.cart = cart;
}

void fillInventory(vector<Inventory>& inventory) {
    Inventory newInventory;
    for (int i = 0; i < SIZE; i++) {
        newInventory.name = "Inventory " + to_string(i + 1);
        newInventory.cost = (rand() % 100) + 1;
        newInventory.count = (rand() % 100) + 1.0;
        newInventory.status = true;
        inventory.push_back(newInventory);
    }
}

void displayInventory(const vector<Inventory>& inventory) {
    cout << fixed << setprecision(2);
    cout << "INVENTORY" << endl;
    for (int i = 0; i < SIZE; i++) {
        cout << "Item Name: " << inventory[i].name << endl;
        cout << "Item Cost: $" << inventory[i].cost << endl;
        cout << "Item Inventory: " << inventory[i].count << endl;
        cout << "Item Status: " << (inventory[i].status == true ? "True" : "False");
        cout << endl << endl;
    }
}

void emptyInventory(vector<Inventory>& inventory, int item) {
    if (inventory[item].count == 0) {
        inventory[item].status = false;
    }
}

void fillShoppingCart(ShoppingCart& cart, vector<Inventory>& inventory) {
    int randomItem = rand() % 5;
    int randomAmount = (rand() % 10000) + 1;
    CartItem tempCartItem;
    cart.totalItems = 0;
    cart.totalCost = 0.0f;
    cart.totalQuantity = 0;

    for (int i = 0; i < 3; i++) {
        emptyInventory(inventory, randomItem);
        if (inventory[randomItem].status) {
            tempCartItem.itemName = inventory[randomItem].name;
            randomAmount = inventory[randomItem].count - randomAmount < 0 ?
                    inventory[randomItem].count : randomAmount;
            inventory[randomItem].count -= randomAmount;
            tempCartItem.quantity = randomAmount;
            tempCartItem.cost = inventory[randomItem].cost * randomAmount;
            cart.items.push_back(tempCartItem);
            emptyInventory(inventory, randomItem);
        } else {
            cout << endl;
            cout << "ITEM OUT OF STOCK" << endl << endl;
        }
        randomItem = rand() % 5;
        randomAmount = (rand() % 3) + 1;
    }
    cart.totalItems = cart.items.size();
    for (int i = 0; i < cart.totalItems; i++) {
        cart.totalCost += cart.items[i].cost;
        cart.totalQuantity += cart.items[i].quantity;
    }
}

void displayCart(const ShoppingCart cart, const string username) {
    cout << username << "'s SHOPPING CART" << endl << endl;
    cout << left << setw(25);
    cout << "ITEMS";
    cout << setw(25) << "QUANTITY";
    cout << setw(25) << "COST" << endl;
    cout << fixed << setprecision(2);
    for (int i = 0; i < cart.totalItems; i++) {
        cout << setw(25) << cart.items[i].itemName;
        cout << setw(25) << cart.items[i].quantity;
        cout << "$" << cart.items[i].cost << endl;
    }

    cout << endl;
    cout << "TOTAL ITEMS: " << cart.totalItems << endl;
    cout << "TOTAL QUANTITY: " << cart.totalQuantity << endl;
    cout << "TOTAL COST: $" << cart.totalCost << endl;
    cout << endl;
}

