/* 
 * File:   main.cpp
 * Author: Josh Carlito
 *
 * Created on April 10, 2023, 2:06 PM
 * Purpose: Convert the previous procedural structs/functions into classes
 * Version: 11, Put everything into classes and get customer UI working
 */

#include "StoreFront.h"
#include "SignIn.h"
#include "Inventory.h"
#include "ShoppingCart.h"
#include "Customer.h"
#include "SalesRecord.h"
#include "Admin.h"
#include "StoreInterface.h"

void signInInterface(SignIn& interface);
void purchaseItem(CustomerClass& customer);
void displayCart(CustomerClass& customer);
void removeItem(CustomerClass& customer);
void checkout(CustomerClass& customer, SalesRecord& salesInfo);

int main(int argc, char** argv) {
    int customerInput;

    SignIn interface;
    SalesRecord salesInfo;

    signInInterface(interface);
    if (interface.getAdminStatus()) {
        cout << "Admin User" << endl;
        Admin admin(interface.getUsername());
    } else {
        CustomerClass customer(interface.getUsername());
        string itemName;
        int quantity;
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
}