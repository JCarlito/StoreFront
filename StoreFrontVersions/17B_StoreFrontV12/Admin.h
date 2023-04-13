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
    static bool comparePriceLowToHigh(const Inventory& item1, const Inventory & item2) {
        return item1.cost < item2.cost;
    }
public:

    Admin(string u) {
        username = u;
    }
    void displayAdminMenu();
    void displayInventoryOptions();
    void changeStock(string name, int newStock);
    void addStock(string name, int newStock);
    void changeItemName(string name, string newName);
    void changePrice(string name, float newPrice);
    void displayAllSales();
    void readCustomerInformation();
    void readUserInfo();
    void printAllUserInfo();
    void changeUserStatus(string username, bool status);
    void changeUserPassword(string username, string password);
    void writeUserInfoChanges();
    void displayUsersInfo(string usernameSearch);
    void readInventory();
    void findUsername(string usernameSearch);
    void displayInventory();
    void addNewItem(string itemName, float cost, int stock, bool status);
    void writeInventoryChanges();
    int findInventoryItem(string name);
    int findCustomer(string customerUsername);
    void displaySalesHistoryOptions();
    void displayCustomerPurchaseHistory(string customerUsername);
    void displayUserInfoMenu();
};

#endif /* ADMIN_H */

