/* 
 * File:   main.cpp
 * Author: Josh Carlito
 *
 * Created on March 27, 2023, 1:21 PM
 * Purpose: Create a Store Front program
 * Version: 1, create a simple interface with no files.
 */

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

const int SIZE = 5;

struct Item {
    string name; // Name of the item
    float cost; // Cost of the item
    int inventory; // Number of items in inventory
    bool status; // Active or not active
};

struct ShoppingCart {
    vector<string> items;
    float totalCost;
    int totalItems;
};

void fillInventory(vector<Item>& items) {
    Item newItem;
    for (int i = 0; i < SIZE; i++) {
        newItem.name = "Item " + to_string(i + 1);
        newItem.cost = (rand() % 100) + 1;
        newItem.inventory = (rand() % 100) + 1.0;
        newItem.status = true;
        items.push_back(newItem);
    }
}

void display(const vector<Item>& items) {
    cout << fixed << setprecision(2);
    cout << "INVENTORY" << endl;
    for (int i = 0; i < SIZE; i++) {
        cout << "Item Name: " << items[i].name << endl;
        cout << "Item Cost: $" << items[i].cost << endl;
        cout << "Item Inventory: " << items[i].inventory << endl;
        cout << "Item Status: " << (items[i].status == 1 ? "True" : "False");
        cout << endl << endl;
    }
}

void fillShoppingCart(ShoppingCart& cart, vector<Item>& items) {
    int randomItem = rand() % 5;
    int randomAmount = (rand() % 3) + 1;
    cart.totalItems = 0;
    for (int i = 0; i < 3; i++) {
        cart.items.push_back(items[randomItem].name);
        items[randomItem].inventory -= randomAmount;
        cart.totalItems += randomAmount;
        cart.totalCost += items[randomItem].cost * randomAmount;
        randomItem = rand() % 5;
        randomAmount = (rand() % 3) + 1;
    }
}

void displayCart(const ShoppingCart cart) {
    cout << "SHOPPING CART" << endl;
    cout << "Cart Item: ";
    for (int i = 0; i < cart.items.size(); i++)
        cout << cart.items[i] << " ";
    cout << endl;
    cout << "Cart Total Items: " << cart.totalItems << endl;
    cout << "Cart Total Cost: $" << cart.totalCost << endl;
    cout << endl;
}

void emptyInventory(const vector<Item>& items, int item) {
    if (items[item].inventory == 0) {
        items[item].status = false;
    }
}

int main(int argc, char** argv) {
    srand(static_cast<unsigned int> (time(0)));

    vector<Item> items;
    ShoppingCart cart;
    fillInventory(items);
    display(items);
    fillShoppingCart(cart, items);
    displayCart(cart);
    display(items);

    return 0;
}

