/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Admin.h
 * Author: Josh Carlito
 *
 * Created on April 11, 2023, 8:35 PM
 */

#ifndef ADMIN_H
#define ADMIN_H
#include "StoreFront.h"

class Admin {
private:
    string username;
    int userInfoIndex;
    vector<Customer> salesInfo;
    vector<UserInfo> userInfo;
    vector<Inventory> inventory;
public:

    Admin(string u) {
        username = u;
        readInventory();
        readUserInfo();
        readCustomerInformation();
    }
    void displayAdminMenu();
    void displayInventoryOptions();
    void changeStock(string name, int newStock);
    void addStock(string name, int newStock);
    void changeItemName(string name, string newName);
    void changePrice(string name, float newPrice);
    void displayAllCustomers();
    void readCustomerInformation();
    void readUserInfo();
    void printAllUserInfo();
    void changeUserStatus(string username, bool status);
    void changeUserPassword(string username, string password);
    void writeUserInfoChanges();
    void displayUsersInfo(string usernameSearch);
    void readInventory();
    int findInventoryItem(string name);
    void findUsername(string usernameSearch);
    void displayInventory() const;
};


#endif /* ADMIN_H */

