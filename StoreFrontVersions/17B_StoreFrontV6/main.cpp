/* 
 * File:   main.cpp
 * Author: Josh Carlito
 *
 * Created on April 5, 2023, 6:00 PM
 * Purpose: Create a simple interface with no files and completely procedural
 * Version: 6, Extend the UI to add Admin some functionality. i.e. change stock 
 *             add new items. (basically editing inventory)
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
int findCartItem(const ShoppingCart& cart, const CartItem& newItem);
int findInventoryItem(const vector<Inventory>& items, string name);
void displayStore(const vector<Inventory>& items);
void displayStoreMenu();
void displayAdminMenu();
void changeStock(vector<Inventory>& items, string name, int newStock);
void addStock(vector<Inventory>& items, string name, int newStock);
void changeItemName(vector<Inventory>& items, string name, string newName);
void changePrice(vector<Inventory>& items, string name, float newPrice);

int main(int argc, char** argv) {
    // Set random number seed
    srand(static_cast<unsigned int> (time(0)));
    // Declare Variables
    int customerInput;
    int adminInput;
    Customer customer;

    vector<Inventory> items;
    ShoppingCart cart;

    fillInventory(items);
    displayStore(items);
    //    displayStoreMenu();
    displayAdminMenu();
    cin >> adminInput;
    cin.ignore();
    if (adminInput == 1) {
        int newStock;
        string itemName;
        cout << "Enter the item name: ";
        getline(cin, itemName);
        cout << "Enter the new stock amount: ";
        cin >> newStock;
        cin.ignore();
        changeStock(items, itemName, newStock);
    } else if (adminInput == 2) {
        int newStock;
        string itemName;
        cout << "Enter the item name: ";
        getline(cin, itemName);
        cout << "Enter the stock amount you'd like to add: ";
        cin >> newStock;
        cin.ignore();
        addStock(items, itemName, newStock);
    } else if (adminInput == 3) {
        string newItemName;
        string itemName;
        cout << "Enter the item name: ";
        getline(cin, itemName);
        cout << "Enter the new item name: ";
        getline(cin, newItemName);
        changeItemName(items, itemName, newItemName);
    } else if (adminInput == 4) {
        float newPrice;
        string itemName;
        cout << "Enter the item name: ";
        getline(cin, itemName);
        cout << "Enter the new price: ";
        cin >> newPrice;
        cin.ignore();
        changePrice(items, itemName, newPrice);
    }


    displayStore(items);


    //    cin >> customerInput;
    //    while (customerInput != -1) {
    //        cin.ignore();
    //        cout << endl;
    //        setUsername(customer, "Josh");
    //        if (customerInput == 1) {
    //            displayStore(items);
    //        } else if (customerInput == 2) {
    //            cout << "THIS NEEDS TO BE MADE" << endl;
    //        } else if (customerInput == 3) {
    //            fillShoppingCart(cart, items);
    //            setCart(customer, cart);
    //            displayCart(customer.cart, customer.username);
    //        }
    //        cout << "Enter next input: ";
    //        cin >> customerInput;
    //    }
    return 0;
}

void displayAdminMenu() {
    cout << "-----------------------------------";
    cout << "ADMIN MENU";
    cout << "-----------------------------------" << endl << endl;
    cout << "To change stock, press (1)" << endl;
    cout << "To add more stock, press (2)" << endl;
    cout << "To change an item name, press (3)" << endl;
    cout << "To change an item's price, press (4)" << endl;
    cout << "Enter input: ";
}

void changePrice(vector<Inventory>& items, string name, float newPrice) {
    int index = findInventoryItem(items, name);
    items[index].cost = newPrice;
}

void changeStock(vector<Inventory>& items, string name, int newStock) {
    int index = findInventoryItem(items, name);
    items[index].stock = newStock;
}

void addStock(vector<Inventory>& items, string name, int newStock) {
    int index = findInventoryItem(items, name);
    items[index].stock += newStock;
}

void changeItemName(vector<Inventory>& items, string name, string newName) {
    int index = findInventoryItem(items, name);
    items[index].itemName = newName;
}

int findInventoryItem(const vector<Inventory>& items, string name) {
    int index = 0;
    for (const auto& item : items) {
        if (item.itemName == name) {
            return index;
        }
        index++;
    }
    return -1;
}

void displayStore(const vector<Inventory>& items) {
    cout << "-----------------------------";
    cout << "WELCOME TO SHOE ODYSSEY";
    cout << "-----------------------------";
    cout << endl << endl;
    cout << left << setw(39);
    cout << "ITEM NAME";
    cout << setw(37) << "COST";
    cout << setw(37) << "STOCK";
    cout << endl;
    cout << fixed << setprecision(2);
    for (const auto& item : items) {
        if (item.status) {
            cout << setw(38) << item.itemName;
            cout << " $" << setw(36) << item.cost;
            cout << setw(37) << item.stock << endl;
        }
    }
    cout << endl;
}

void displayStoreMenu() {
    cout << "-----------------------------------";
    cout << "STORE MENU";
    cout << "-----------------------------------" << endl << endl;
    cout << "To display store inventory again, press (1):" << endl;
    cout << "To add an item to your shopping cart, press (2):" << endl;
    cout << "To view shopping cart, press (3):" << endl;
    cout << "To exit the application press (-1)" << endl;
    cout << "Enter input: ";
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
        newInventory.itemName = "Shoe " + to_string(i + 1);
        newInventory.cost = ((rand() % 220) + 79) + 0.99f;
        newInventory.stock = (rand() % 40) + 11;
        newInventory.status = true;
        inventory.push_back(newInventory);
    }
}

void displayInventory(const vector<Inventory>& inventory) {
    cout << fixed << setprecision(2);
    cout << "INVENTORY" << endl;
    for (int i = 0; i < SIZE; i++) {
        cout << "Item Name: " << inventory[i].itemName << endl;
        cout << "Item Cost: $" << inventory[i].cost << endl;
        cout << "Item Inventory: " << inventory[i].stock << endl;
        cout << "Item Status: " << (inventory[i].status == true ? "True" : "False");
        cout << endl << endl;
    }
}

void emptyInventory(vector<Inventory>& inventory, int item) {
    if (inventory[item].stock <= 0) {
        inventory[item].status = false;
    }
}

void fillShoppingCart(ShoppingCart& cart, vector<Inventory>& inventory) {
    int randomItem = rand() % 3;
    int randomAmount = (rand() % 10) + 1;
    int index;
    CartItem tempCartItem;
    cart.totalItems = 0;
    cart.totalCost = 0.0f;
    cart.totalQuantity = 0;


    emptyInventory(inventory, randomItem);
    if (inventory[randomItem].status) {
        tempCartItem.itemName = inventory[randomItem].itemName;
        index = findCartItem(cart, tempCartItem);
        if (index >= 0) {
            randomAmount = inventory[randomItem].stock - randomAmount < 0 ?
                    inventory[randomItem].stock : randomAmount;
            inventory[randomItem].stock -= randomAmount;
            cart.items[index].quantity += randomAmount;
            cart.items[index].cost += inventory[randomItem].cost * randomAmount;
            emptyInventory(inventory, randomItem);
        } else {
            randomAmount = inventory[randomItem].stock - randomAmount < 0 ?
                    inventory[randomItem].stock : randomAmount;
            inventory[randomItem].stock -= randomAmount;
            tempCartItem.quantity = randomAmount;
            tempCartItem.cost = inventory[randomItem].cost * randomAmount;
            cart.items.push_back(tempCartItem);
            emptyInventory(inventory, randomItem);
        }
    } else {
        cout << endl;
        cout << inventory[randomItem].itemName << " is OUT OF STOCK";
        cout << endl << endl;
    }

    cart.totalItems = cart.items.size();
    for (int i = 0; i < cart.totalItems; i++) {
        cart.totalCost += cart.items[i].cost;
        cart.totalQuantity += cart.items[i].quantity;
    }
}

int findCartItem(const ShoppingCart& cart, const CartItem& newItem) {
    int index = 0;
    for (const auto& item : cart.items) {
        if (item.itemName == newItem.itemName) {
            return index;
        }
        index++;
    }
    return -1;
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