/* 
 * File:   main.cpp
 * Author: Josh Carlito
 *
 * Created on April 10, 2023, 2:06 PM
 * Purpose: Convert the previous procedural structs/functions into classes
 * Version: 12, Get the Admin interface working.
 */

#include "StoreFront.h"
#include "SignIn.h"
#include "Inventory.h"
#include "ShoppingCart.h"
#include "Customer.h"
#include "SalesRecord.h"
#include "Admin.h"

void signInInterface(SignIn& interface);
void purchaseItem(CustomerClass& customer);
void displayCart(CustomerClass& customer);
void removeItem(CustomerClass& customer);
void checkout(CustomerClass& customer, SalesRecord& salesInfo);
void changeStock(Admin& admin);
void addRemoveStock(Admin& admin);
void changeItemName(Admin& admin);
void changePrice(Admin& admin);
void addNewItem(Admin& admin);
void displayCustomerPurchaseHistory(Admin& admin);
void displayUserInformation(Admin& admin);
void changePassword(Admin& admin);
void changeStatus(Admin& admin);

/*
 * ADMIN ACCOUNT INFORMATION:
 * USERNAME: mlehr
 * PASSWORD: mlehr
 */

int main(int argc, char** argv) {
    SignIn interface;
    SalesRecord salesInfo;

    signInInterface(interface);
    if (interface.getAdminStatus()) {
        Admin admin(interface.getUsername());
        int adminInput;
        char adminMenuInput;
        admin.displayAdminMenu();
        cin.get(adminMenuInput);
        while (adminMenuInput != 'x' && adminMenuInput != 'X') {
            if (adminMenuInput == 'a' || adminMenuInput == 'A') {
                admin.readInventory();
                admin.displayInventoryOptions();
                cout << "Enter input: ";
                cin >> adminInput;
                cin.ignore();
                while (adminInput != -1) {
                    if (adminInput == 1) {
                        changeStock(admin);
                    } else if (adminInput == 2) {
                        addRemoveStock(admin);
                    } else if (adminInput == 3) {
                        changeItemName(admin);
                    } else if (adminInput == 4) {
                        changePrice(admin);
                    } else if (adminInput == 5) {
                        addNewItem(admin);
                    } else if (adminInput == 6) {
                        admin.displayInventory();
                    } else if (adminInput == 7) {
                        admin.displayInventoryOptions();
                    } else {
                        admin.writeInventoryChanges();
                        cout << "Changes have been written" << endl;
                    }
                    cout << endl;
                    cout << "Enter input: ";
                    cin >> adminInput;
                    cin.ignore();
                }
            } else if (adminMenuInput == 'b' || adminMenuInput == 'B') {
                admin.readCustomerInformation();
                admin.displaySalesHistoryOptions();
                cout << "Enter input: ";
                cin >> adminInput;
                cin.ignore();
                while (adminInput != -1) {
                    if (adminInput == 1) {
                        admin.displayAllSales();
                    } else {
                        displayCustomerPurchaseHistory(admin);
                    }
                    cout << endl;
                    cout << "Enter input: ";
                    cin >> adminInput;
                    cin.ignore();
                }
            } else {
                admin.readUserInfo();
                admin.displayUserInfoMenu();
                cout << "Enter input: ";
                cin >> adminInput;
                cin.ignore();
                while (adminInput != -1) {
                    if (adminInput == 1) {
                        admin.printAllUserInfo();
                    } else if (adminInput == 2) {
                        displayUserInformation(admin);
                    } else if (adminInput == 3) {
                        changePassword(admin);
                    } else if (adminInput == 4) {
                        changeStatus(admin);
                    } else {
                        admin.writeUserInfoChanges();
                        cout << "Changes have been written" << endl;
                    }
                    cout << endl;
                    cout << "Enter input: ";
                    cin >> adminInput;
                    cin.ignore();
                }
            }
            admin.displayAdminMenu();
            cin.get(adminMenuInput);
        }
    } else {
        int customerInput;
        CustomerClass customer(interface.getUsername());
        customer.displayStore();
        customer.displayStoreMenu();
        cin >> customerInput;
        while (customerInput != -1) {
            cin.ignore();
            cout << endl;
            if (customerInput == 1) {
                customer.displayStore();
            } else if (customerInput == 2) {
                purchaseItem(customer);
            } else if (customerInput == 3) {
                displayCart(customer);
            } else if (customerInput == 4) {
                removeItem(customer);
            } else if (customerInput == 5) {
                checkout(customer, salesInfo);
            }
            cout << "Enter next input: ";
            cin >> customerInput;
        }
    }
    return 0;
}

void signInInterface(SignIn& interface) {
    interface.displayMenu();
    while (!interface.getExitSignIn()) {
        if (interface.getUserInput() == 'u') {
            // Create a normal user account
            cout << "Register for a Normal User account" << endl << endl;
            interface.setUsername();
            interface.setPassword();
            interface.setStatus();
            // Store information to file
            interface.writeBinary();
            interface.setExitSignIn(true);
        } else if (interface.getUserInput() == 'a') {
            // Create an admin account
            cout << "Register for Admin account" << endl << endl;
            interface.validateAdminKey();
            interface.setUsername();
            interface.setPassword();
            interface.setStatus();
            // Store information to file
            interface.writeBinary();
            interface.setExitSignIn(true);
        } else {
            // Sign-in to an existing account
            cout << "Sign-In" << endl << endl;
            interface.setUsername();
            interface.setPassword();
            interface.validateUser();
            // If no account is found display an error and prompt user
            // to create an account or try again
            if (!interface.getExitSignIn()) {
                // The user only gets 5 attempts
                interface.displayError();
            }
        }
    }
}

void purchaseItem(CustomerClass& customer) {
    string itemName;
    int quantity;
    cout << "Enter the item name you wish to purchase: ";
    getline(cin, itemName);
    cout << "Enter how many you'd like to purchase: ";
    cin >> quantity;
    cin.ignore();
    customer.addToCart(itemName, quantity);
}

void displayCart(CustomerClass& customer) {
    customer.setShoppingCart();
    customer.displayCart();
}

void removeItem(CustomerClass& customer) {
    string itemName;
    int quantity;
    cout << "Enter the item name you wish to remove: ";
    getline(cin, itemName);
    cout << "Enter how many you'd like to remove: ";
    cin >> quantity;
    cin.ignore();
    customer.removeFromCart(itemName, quantity);
}

void checkout(CustomerClass& customer, SalesRecord& salesInfo) {
    customer.setShoppingCart();
    Customer tempCustomer = customer.getCustomer();
    salesInfo.writeCustomerInformation(tempCustomer);
    customer.updateInventory();
    cout << "Congratulations on your purchase!" << endl;
}

void changeStock(Admin& admin) {
    int newStock;
    string itemName;
    cout << "Enter the item name: ";
    getline(cin, itemName);
    cout << "Enter the new stock amount: ";
    cin >> newStock;
    cin.ignore();
    admin.changeStock(itemName, newStock);
}

void addRemoveStock(Admin& admin) {
    int newStock;
    string itemName;
    cout << "Enter the item name: ";
    getline(cin, itemName);
    cout << "Enter the stock amount you'd like to add (+) or remove (-): ";
    cin >> newStock;
    cin.ignore();
    admin.addStock(itemName, newStock);
}

void changeItemName(Admin& admin) {
    string newItemName;
    string itemName;
    cout << "Enter the item name: ";
    getline(cin, itemName);
    cout << "Enter the new item name: ";
    getline(cin, newItemName);
    admin.changeItemName(itemName, newItemName);
}

void changePrice(Admin& admin) {
    float newPrice;
    string itemName;
    cout << "Enter the item name: ";
    getline(cin, itemName);
    cout << "Enter the new price: ";
    cin >> newPrice;
    cin.ignore();
    admin.changePrice(itemName, newPrice);
}

void addNewItem(Admin& admin) {
    string itemName;
    float cost;
    int stock;
    cout << "Enter the new item's name: ";
    getline(cin, itemName);
    cout << "Enter the new item's price: ";
    cin >> cost;
    cin.ignore();
    cout << "Enter the new item's stock: ";
    cin >> stock;
    cin.ignore();
    bool status = stock > 0 ? true : false;
    admin.addNewItem(itemName, cost, stock, status);
}

void displayCustomerPurchaseHistory(Admin& admin) {
    string customerUsername;
    cout << "Enter the customer's username: ";
    getline(cin, customerUsername);
    admin.displayCustomerPurchaseHistory(customerUsername);
}

void displayUserInformation(Admin& admin) {
    string tempUsername;
    cout << "Enter the username of the user you'd like to see: ";
    cin >> tempUsername;
    admin.displayUsersInfo(tempUsername);
}

void changePassword(Admin& admin) {
    string tempUsername;
    string tempPassword;
    cout << "Enter the username of the user's password you'd like";
    cout << " to change: ";
    cin >> tempUsername;
    cout << "Enter the new password: ";
    cin >> tempPassword;
    admin.changeUserPassword(tempUsername, tempPassword);
}

void changeStatus(Admin& admin) {
    string tempUsername;
    bool tempStatus;
    cout << "Enter the username of the user's status you'd like to change: ";
    cin >> tempUsername;
    cout << "Press (1) to activate or (0) to deactivate: ";
    cin >> tempStatus;
    admin.changeUserStatus(tempUsername, tempStatus);
}