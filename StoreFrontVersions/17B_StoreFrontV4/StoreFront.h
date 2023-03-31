/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   StoreFront.h
 * Author: Josh Carlito
 *
 * Created on March 28, 2023, 4:17 PM
 */

#ifndef STOREFRONT_H
#define STOREFRONT_H
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <fstream>

using namespace std;

const int USERNAME_LENGTH = 12;
const int PASSWORD_LENGTH = 12;
const int SIZE = 5;

struct UserInfo {
    string username;
    string password;
    bool adminFlag;
};



struct Inventory {
    string name; // Name of the item
    float cost; // Cost of the item
    int count; // Number of items in inventory
    bool status; // Active or not active
};

struct CartItem {
    string itemName; // Name of an item
    int quantity; // The quantity of the specific item
    float cost; // Total cost of the item * quantity
};

struct ShoppingCart {
    vector<CartItem> items; // CartItems in the shopping cart
    float totalCost; // Total Cost of all the items in the cart
    int totalItems; // The total number of unique items.
    int totalQuantity; // The total quantity of items
};

struct Customer {
    string username;
    ShoppingCart cart;
};

#endif /* STOREFRONT_H */

