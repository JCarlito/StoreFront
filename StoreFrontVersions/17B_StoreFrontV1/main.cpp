/* 
 * File:   main.cpp
 * Author: Josh Carlito
 *
 * Created on March 27, 2023, 1:21 PM
 * Purpose: Create a simple interface with no files and completely procedural
 * Version: 1, Rename item struct to inventory for better readability. Don't
 *              allow negative inventory values and mark status to false
 *              when inventory == 0;
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

struct Inventory {
    string name; // Name of the item
    float cost; // Cost of the item
    int count; // Number of items in inventory
    bool status; // Active or not active
};

struct ShoppingCart {
    vector<string> items;
    float totalCost;
    int totalItems;
};

void fillInventory(vector<Inventory>& items);
void displayInventory(const vector<Inventory>& items);
void emptyInventory(vector<Inventory>& items, int item);
void fillShoppingCart(ShoppingCart& cart, vector<Inventory>& items);
void displayCart(const ShoppingCart cart);

int main(int argc, char** argv) {
    srand(static_cast<unsigned int> (time(0)));

    vector<Inventory> items;
    ShoppingCart cart;
    fillInventory(items);
    displayInventory(items);
    fillShoppingCart(cart, items);
    displayCart(cart);
    displayInventory(items);

    return 0;
}

void fillInventory(vector<Inventory>& items) {
    Inventory newInventory;
    for (int i = 0; i < SIZE; i++) {
        newInventory.name = "Inventory " + to_string(i + 1);
        newInventory.cost = (rand() % 100) + 1;
        newInventory.count = (rand() % 100) + 1.0;
        newInventory.status = true;
        items.push_back(newInventory);
    }
}

void displayInventory(const vector<Inventory>& items) {
    cout << fixed << setprecision(2);
    cout << "INVENTORY" << endl;
    for (int i = 0; i < SIZE; i++) {
        cout << "Item Name: " << items[i].name << endl;
        cout << "Item Cost: $" << items[i].cost << endl;
        cout << "Item Inventory: " << items[i].count << endl;
        cout << "Item Status: " << (items[i].status == 1 ? "True" : "False");
        cout << endl << endl;
    }
}

void emptyInventory(vector<Inventory>& items, int item) {
    if (items[item].count == 0) {
        items[item].status = false;
    }
}

void fillShoppingCart(ShoppingCart& cart, vector<Inventory>& items) {
    int randomItem = rand() % 5;
    int randomAmount = (rand() % 1000) + 1;
    cart.totalItems = 0;
    cart.totalCost = 0.0f;
    for (int i = 0; i < 3; i++) {
        emptyInventory(items, i);
        if (items[i].status) {
            cart.items.push_back(items[randomItem].name);
            randomAmount = items[randomItem].count - randomAmount < 0 ?
                    items[randomItem].count : randomAmount;
            items[randomItem].count -= randomAmount;
            cart.totalItems += randomAmount;
            cart.totalCost += items[randomItem].cost * randomAmount;
        } else {
            cout << endl << endl;
            cout << "ITEM OUT OF STOCK" << endl << endl;
        }
        randomItem = rand() % 5;
        randomAmount = (rand() % 3) + 1;
    }
}

void displayCart(const ShoppingCart cart) {
    cout << "SHOPPING CART" << endl;
    cout << "Cart Inventory: ";
    for (int i = 0; i < cart.items.size(); i++)
        cout << cart.items[i] << " ";
    cout << endl;
    cout << "Cart Total Items: " << cart.totalItems << endl;
    cout << "Cart Total Cost: $" << cart.totalCost << endl;
    cout << endl;
}

