/* 
 * File:   main.cpp
 * Author: Josh Carlito
 *
 * Created on April 5, 2023, 9:00 PM
 * Purpose: Create a simple interface with no files and completely procedural
 * Version: 8, Add customer functionality. i,e adding things to their cart
 *             viewing things in there cart, removing items from their cart, etc
 */

#include "StoreFront.h"
#include "SignIn.h"

void displayInventory(const vector<Inventory>& inventory);
void emptyInventory(vector<Inventory>& inventory, int item);
void displayCart(const ShoppingCart cart, const string username);
void setUsername(Customer& customer, string username);
void setCart(Customer& customer, ShoppingCart cart);
int findCartItem(const ShoppingCart& cart, const CartItem& newItem);
int findInventoryItem(const vector<Inventory>& items, string name);
void displayStore(const vector<Inventory>& items);
void displayStoreMenu();
void displayAdminMenu();
void displayInventoryOptions();
void changeStock(vector<Inventory>& items, string name, int newStock);
void addStock(vector<Inventory>& items, string name, int newStock);
void changeItemName(vector<Inventory>& items, string name, string newName);
void changePrice(vector<Inventory>& items, string name, float newPrice);
void writeInventory(vector<Inventory>& items);
void readInventory(vector<Inventory>& items);
bool comparePriceLowToHigh(const Inventory& item1, const Inventory& item2);
void addToCart(ShoppingCart& cart, vector<Inventory>& inventory, string itemName, int quantity);
void removeFromCart(ShoppingCart& cart, vector<Inventory>& inventory, string itemName, int quantity);

int main(int argc, char** argv) {
    // Set random number seed
    srand(static_cast<unsigned int> (time(0)));
    // Declare Variables
    int customerInput;
    int adminInput;
    char adminMenuInput;

    Customer customer;
    vector<Inventory> items;
    ShoppingCart cart;

    readInventory(items);
    //    sort(items.begin(), items.end(), comparePriceLowToHigh);
    //    displayAdminMenu();
    //    cin.get(adminMenuInput);
    //    while (adminMenuInput != 'x' && adminMenuInput != 'X') {
    //        if (adminMenuInput == 'a') {
    //            displayInventoryOptions();
    //            cin >> adminInput;
    //            cin.ignore();
    //            if (adminInput == 1) {
    //                int newStock;
    //                string itemName;
    //                cout << "Enter the item name: ";
    //                getline(cin, itemName);
    //                cout << "Enter the new stock amount: ";
    //                cin >> newStock;
    //                cin.ignore();
    //                changeStock(items, itemName, newStock);
    //            } else if (adminInput == 2) {
    //                int newStock;
    //                string itemName;
    //                cout << "Enter the item name: ";
    //                getline(cin, itemName);
    //                cout << "Enter the stock amount you'd like to add: ";
    //                cin >> newStock;
    //                cin.ignore();
    //                addStock(items, itemName, newStock);
    //            } else if (adminInput == 3) {
    //                string newItemName;
    //                string itemName;
    //                cout << "Enter the item name: ";
    //                getline(cin, itemName);
    //                cout << "Enter the new item name: ";
    //                getline(cin, newItemName);
    //                changeItemName(items, itemName, newItemName);
    //            } else if (adminInput == 4) {
    //                float newPrice;
    //                string itemName;
    //                cout << "Enter the item name: ";
    //                getline(cin, itemName);
    //                cout << "Enter the new price: ";
    //                cin >> newPrice;
    //                cin.ignore();
    //                changePrice(items, itemName, newPrice);
    //            } else if (adminInput == 5) {
    //                Inventory temporaryItem;
    //                cout << "Enter the new item's name: ";
    //                getline(cin, temporaryItem.itemName);
    //                cout << "Enter the new item's price: ";
    //                cin >> temporaryItem.cost;
    //                cin.ignore();
    //                cout << "Enter the new item's stock: ";
    //                cin >> temporaryItem.stock;
    //                cin.ignore();
    //                temporaryItem.status = true;
    //                items.push_back(temporaryItem);
    //            } else if (adminInput == 6) {
    //                displayStore(items);
    //            } else if (adminInput == -1) break;
    //            cout << endl;
    //            cout << "Enter input: ";
    //            cin >> adminInput;
    //            cin.ignore();
    //        }
    //        displayAdminMenu();
    //        cin.get(adminMenuInput);
    //    }
    //    writeInventory(items);

    displayStore(items);
    displayStoreMenu();
    cin >> customerInput;
    while (customerInput != -1) {
        cin.ignore();
        cout << endl;
        setUsername(customer, "Josh");
        if (customerInput == 1) {
            displayStore(items);
        } else if (customerInput == 2) {
            string itemName;
            int quantity;
            cout << "Enter the item name you wish to purchase: ";
            getline(cin, itemName);
            cout << "Enter how many you'd like to purchase: ";
            cin >> quantity;
            cin.ignore();
            addToCart(cart, items, itemName, quantity);
        } else if (customerInput == 3) {
            setCart(customer, cart);
            displayCart(customer.cart, customer.username);
        } else if (customerInput == 4) {
            string itemName;
            int quantity;
            cout << "Enter the item name you wish to remove: ";
            getline(cin, itemName);
            cout << "Enter how many you'd like to remove: ";
            cin >> quantity;
            cin.ignore();
            removeFromCart(cart, items, itemName, quantity);
        }
        cout << "Enter next input: ";
        cin >> customerInput;
    }
    return 0;
}

void writeInventory(vector<Inventory>& items) {
    fstream binaryInventoryFile;
    char tempItemNameLength = 0;
    binaryInventoryFile.open("Inventory.bin", ios::out | ios::binary);
    if (!binaryInventoryFile.is_open()) {
        cout << "Error opening file!" << endl;
        return;
    }

    binaryInventoryFile.seekp(0, ios::beg);
    for (auto& item : items) {
        tempItemNameLength = item.itemName.size();
        binaryInventoryFile.write(&tempItemNameLength, sizeof (char));
        binaryInventoryFile.write(&item.itemName[0], tempItemNameLength);
        binaryInventoryFile.write(reinterpret_cast<char*> (&item.cost), sizeof (float));
        binaryInventoryFile.write(reinterpret_cast<char*> (&item.stock), sizeof (int));
        binaryInventoryFile.write(reinterpret_cast<char*> (&item.status), sizeof (bool));
    }
    binaryInventoryFile.close();
}

void readInventory(vector<Inventory>& items) {
    fstream binaryInventoryFile;
    char tempItemNameLength = 0;
    Inventory temporaryInventory;
    binaryInventoryFile.open("Inventory.bin", ios::in | ios::binary);
    if (!binaryInventoryFile.is_open()) {
        cout << "Error opening file!" << endl;
        return;
    }

    binaryInventoryFile.seekg(0, ios::beg);
    while (binaryInventoryFile.read(&tempItemNameLength, sizeof (char))) {
        temporaryInventory.itemName.resize(tempItemNameLength);
        binaryInventoryFile.read(&temporaryInventory.itemName[0], tempItemNameLength);
        binaryInventoryFile.read(reinterpret_cast<char*> (&temporaryInventory.cost), sizeof (float));
        binaryInventoryFile.read(reinterpret_cast<char*> (&temporaryInventory.stock), sizeof (int));
        binaryInventoryFile.read(reinterpret_cast<char*> (&temporaryInventory.status), sizeof (bool));
        items.push_back(temporaryInventory);
    }
    binaryInventoryFile.close();
}

void displayAdminMenu() {
    cout << "-----------------------------------";
    cout << "ADMIN MENU";
    cout << "-----------------------------------" << endl << endl;
    cout << "INVENTORY OPTIONS (a)" << endl;
    cout << "SALES INFORMATION (b)" << endl;
    cout << "CUSTOMER INFORMATION OPTIONS (c)" << endl;
    cout << "TO EXIT (x)" << endl;
    cout << "Enter input: ";
}

void displayInventoryOptions() {
    cout << endl;
    cout << "INVENTORY OPTIONS" << endl;
    cout << "To change stock, press (1)" << endl;
    cout << "To add more stock, press (2)" << endl;
    cout << "To change an item name, press (3)" << endl;
    cout << "To change an item's price, press (4)" << endl;
    cout << "To add a new item to the inventory, press (5)" << endl;
    cout << "To display current inventory, press (6)" << endl;
    cout << "To go back to the previous menu, press (-1)" << endl;
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
    cout << "To remove an item from your cart, press (4):" << endl;
    cout << "To checkout, press (5)" << endl;
    cout << "To exit the application press (-1)" << endl;
    cout << "Enter input: ";
}

void setUsername(Customer& customer, string username) {
    customer.username = username;
}

void setCart(Customer& customer, ShoppingCart cart) {
    customer.cart = cart;
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

void addToCart(ShoppingCart& cart, vector<Inventory>& inventory,
        string itemName, int quantity) {
    int inventoryIndex = findInventoryItem(inventory, itemName);
    int cartIndex;
    CartItem tempCartItem;
    cart.totalItems = 0;
    cart.totalCost = 0.0f;
    cart.totalQuantity = 0;

    emptyInventory(inventory, inventoryIndex);
    if (inventory[inventoryIndex].status) {
        tempCartItem.itemName = inventory[inventoryIndex].itemName;
        cartIndex = findCartItem(cart, tempCartItem);
        if (cartIndex != -1) {
            quantity = inventory[inventoryIndex].stock - quantity < 0 ?
                    inventory[inventoryIndex].stock : quantity;
            inventory[inventoryIndex].stock -= quantity;
            cart.items[cartIndex].quantity += quantity;
            cart.items[cartIndex].cost += inventory[inventoryIndex].cost * quantity;
            emptyInventory(inventory, inventoryIndex);
        } else {
            quantity = inventory[inventoryIndex].stock - quantity < 0 ?
                    inventory[inventoryIndex].stock : quantity;
            inventory[inventoryIndex].stock -= quantity;
            tempCartItem.quantity = quantity;
            tempCartItem.cost = inventory[inventoryIndex].cost * quantity;
            cart.items.push_back(tempCartItem);
            emptyInventory(inventory, inventoryIndex);
        }
    } else {
        cout << endl;
        cout << inventory[inventoryIndex].itemName << " is OUT OF STOCK";
        cout << endl << endl;
    }

    cart.totalItems = cart.items.size();
    for (int i = 0; i < cart.totalItems; i++) {
        cart.totalCost += cart.items[i].cost;
        cart.totalQuantity += cart.items[i].quantity;
    }
}

void removeFromCart(ShoppingCart& cart, vector<Inventory>& inventory,
        string itemName, int quantity) {
    int inventoryIndex = findInventoryItem(inventory, itemName);
    int cartIndex;
    CartItem tempCartItem;

    tempCartItem.itemName = inventory[inventoryIndex].itemName;
    cartIndex = findCartItem(cart, tempCartItem);
    // If item is in the cart
    if (cartIndex != -1) {
        // Add the stock back to the inventory
        inventory[inventoryIndex].stock += quantity;
        // subtract the stock from the cart
        cart.items[cartIndex].quantity -= quantity;
        // if the items quantity equals zero
        if (cart.items[cartIndex].quantity == 0) {
            // Subtract from total cost and quantity
            cart.totalCost -= inventory[inventoryIndex].cost * quantity;
            cart.totalQuantity -= quantity;
            cart.totalItems -= 1;
            // Erase the item from the cart
            cart.items.erase(cart.items.begin() + cartIndex);
        } else {
            // Subtract the cost from those items
            cart.items[cartIndex].cost -= inventory[inventoryIndex].cost * quantity;
            // Subtract from total cost and quantity
            cart.totalCost -= inventory[inventoryIndex].cost * quantity;
            cart.totalQuantity -= quantity;
        }
        // If the user made the item out of stock previously make it back 
        // in stock
        if (inventory[inventoryIndex].status == false) {
            inventory[inventoryIndex].status = true;
        }
        // Else the item was not found in the cart
    } else {
        cout << endl << "The Item is not in your cart!" << endl;
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

bool comparePriceLowToHigh(const Inventory& item1, const Inventory& item2) {
    return item1.cost < item2.cost;
}
