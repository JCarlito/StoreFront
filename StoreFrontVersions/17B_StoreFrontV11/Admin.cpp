#include "Admin.h"

void Admin::displayInventory() const {
    cout << "-----------------------------";
    cout << "INVENTORY";
    cout << "-----------------------------";
    cout << endl << endl;
    cout << left << setw(39);
    cout << "ITEM NAME";
    cout << setw(37) << "COST";
    cout << setw(37) << "STOCK";
    cout << endl;
    cout << fixed << setprecision(2);
    for (const auto& item : inventory) {
        if (item.status) {
            cout << setw(38) << item.itemName;
            cout << " $" << setw(36) << item.cost;
            cout << setw(37) << item.stock << endl;
        }
    }
    cout << endl;
}

void Admin::displayAllCustomers() {
    cout << "ALL CUSTOMERS" << endl << endl;

    for (const auto& customer : salesInfo) {
        cout << customer.username << "'s SALES HISTORY" << endl << endl;
        cout << left << setw(25);
        cout << "ITEMS";
        cout << setw(25) << "QUANTITY";
        cout << setw(25) << "COST" << endl;
        cout << fixed << setprecision(2);

        for (int i = 0; i < customer.cart.totalItems; i++) {
            cout << setw(25) << customer.cart.items[i].itemName;
            cout << setw(25) << customer.cart.items[i].quantity;
            cout << "$" << customer.cart.items[i].cost << endl;
        }

        cout << endl;
        cout << "TOTAL ITEMS: " << customer.cart.totalItems << endl;
        cout << "TOTAL QUANTITY: " << customer.cart.totalQuantity << endl;
        cout << "TOTAL COST: $" << customer.cart.totalCost << endl;
        cout << "------------------------" << endl << endl;
    }
}

void Admin::displayAdminMenu() {
    cout << "-----------------------------------";
    cout << "ADMIN MENU";
    cout << "-----------------------------------" << endl << endl;
    cout << "INVENTORY OPTIONS (a)" << endl;
    cout << "SALES INFORMATION (b)" << endl;
    cout << "CUSTOMER INFORMATION OPTIONS (c)" << endl;
    cout << "TO EXIT (x)" << endl;
    cout << "Enter input: ";
}

void Admin::displayInventoryOptions() {
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

void Admin::changePrice(string name, float newPrice) {
    int index = findInventoryItem(name);
    inventory[index].cost = newPrice;
}

void Admin::changeStock(string name, int newStock) {
    int index = findInventoryItem(name);
    inventory[index].stock = newStock;
}

void Admin::addStock(string name, int newStock) {
    int index = findInventoryItem(name);
    inventory[index].stock += newStock;
}

void Admin::changeItemName(string name, string newName) {
    int index = findInventoryItem(name);
    inventory[index].itemName = newName;
}

void Admin::readCustomerInformation() {
    fstream binaryCustomerInfoFile;
    Customer tempCustomer;
    char tempUsernameLength = 0;
    char tempItemNameLength = 0;


    binaryCustomerInfoFile.open("CustomerInfo.bin", ios::in | ios::binary);
    if (!binaryCustomerInfoFile.is_open()) {
        cout << "Error opening file!" << endl;
        return;
    }

    binaryCustomerInfoFile.seekg(0, ios::beg);
    while (binaryCustomerInfoFile.read(&tempUsernameLength, sizeof (char))) {
        tempCustomer.username.resize(tempUsernameLength);
        binaryCustomerInfoFile.read(&tempCustomer.username[0], tempUsernameLength);
        binaryCustomerInfoFile.read(reinterpret_cast<char*> (&tempCustomer.cart.totalCost), sizeof (float));
        binaryCustomerInfoFile.read(reinterpret_cast<char*> (&tempCustomer.cart.totalItems), sizeof (int));
        binaryCustomerInfoFile.read(reinterpret_cast<char*> (&tempCustomer.cart.totalQuantity), sizeof (int));
        tempCustomer.cart.items.resize(tempCustomer.cart.totalItems);
        for (auto& item : tempCustomer.cart.items) {
            binaryCustomerInfoFile.read(&tempItemNameLength, sizeof (char));
            item.itemName.resize(tempItemNameLength);
            binaryCustomerInfoFile.read(&item.itemName[0], tempItemNameLength);
            binaryCustomerInfoFile.read(
                    reinterpret_cast<char*> (&item.quantity), sizeof (int));
            binaryCustomerInfoFile.read(
                    reinterpret_cast<char*> (&item.cost), sizeof (float));
        }
        salesInfo.push_back(tempCustomer);
    }
    binaryCustomerInfoFile.close();
}

void Admin::readUserInfo() {
    fstream information;
    char tempUsernameLength = 0; // User's username length 
    char tempPasswordLength = 0; // User's password length
    UserInfo temp;

    information.open("UserInfo.bin", ios::in | ios::binary);

    information.seekg(0, ios::beg);

    while (information.read(&tempUsernameLength, sizeof (char))) {
        temp.username.resize(tempUsernameLength);
        information.read(&temp.username[0], tempUsernameLength);

        information.read(&tempPasswordLength, sizeof (char));
        temp.password.resize(tempPasswordLength);
        information.read(&temp.password[0], tempPasswordLength);
        information.read(reinterpret_cast<char*>
                (&temp.adminFlag), sizeof (bool));
        information.read(reinterpret_cast<char*>
                (&temp.status), sizeof (bool));
        userInfo.push_back(temp);
    }
    information.close();
}

void Admin::printAllUserInfo() {
    cout << endl << "USER INFORMATION" << endl << endl;
    cout << left << setw(25);
    cout << "USERNAME";
    cout << setw(25) << "PASSWORD";
    cout << setw(25) << "ADMIN STATUS";
    cout << setw(25) << "ACCOUNT STATUS" << endl;
    for (int i = 0; i < userInfo.size(); i++) {
        cout << setw(25) << userInfo[i].username;
        cout << setw(25) << userInfo[i].password;
        cout << setw(25) << (userInfo[i].adminFlag ? "True" : "False");
        cout << setw(25) << (userInfo[i].status ? "Active" : "Inactive");
        cout << endl;
    }
}

void Admin::changeUserStatus(string username, bool status) {
    bool found = false;
    for (auto& user : userInfo) {
        if (user.username == username) {
            // User found
            found = true;
            user.status = status;
            break;
        }
    }

    if (!found) {
        cout << "User " << username << " not found" << endl;
    }
}

void Admin::changeUserPassword(string username, string password) {
    bool found = false;
    for (auto& user : userInfo) {
        if (user.username == username) {
            // User found
            found = true;
            user.password = password;
            break;
        }
    }

    if (!found) {
        cout << "User " << username << " not found" << endl;
    }
}

void Admin::writeUserInfoChanges() {
    char tempUsernameLength = 0;
    char tempPasswordLength = 0;
    fstream binarySignInFile;

    binarySignInFile.open("UserInfo.bin", ios::out | ios::binary);
    if (!binarySignInFile.is_open()) {
        // Handle the error here
        cout << "Failed to open UserInfo.bin in \"writeUserInfoChanges\" ";
        cout << endl;
        exit(1);
    }

    binarySignInFile.seekp(0, ios::beg);

    for (int i = 0; i < userInfo.size(); i++) {
        tempUsernameLength = userInfo[i].username.size();
        tempPasswordLength = userInfo[i].password.size();

        binarySignInFile.write(&tempUsernameLength, sizeof (char));
        binarySignInFile.write(&userInfo[i].username[0], tempUsernameLength);
        binarySignInFile.write(&tempPasswordLength, sizeof (char));
        binarySignInFile.write(&userInfo[i].password[0], tempPasswordLength);
        binarySignInFile.write(reinterpret_cast<char*> (&userInfo[i].adminFlag),
                sizeof (bool));
        binarySignInFile.write(reinterpret_cast<char*> (&userInfo[i].status),
                sizeof (bool));
    }
    userInfo.clear();
    binarySignInFile.close();
}

void Admin::displayUsersInfo(string usernameSearch) {
    findUsername(usernameSearch);
    cout << endl << "USER INFORMATION" << endl << endl;
    cout << left << setw(25);
    cout << "USERNAME";
    cout << setw(25) << "PASSWORD";
    cout << setw(25) << "ADMIN STATUS";
    cout << setw(25) << "ACCOUNT STATUS" << endl;
    cout << setw(25) << userInfo[userInfoIndex].username;
    cout << setw(25) << userInfo[userInfoIndex].password;
    cout << setw(25) << (userInfo[userInfoIndex].adminFlag ? "True" : "False");
    cout << setw(25) << (userInfo[userInfoIndex].status ? "Active" : "Inactive");
    cout << endl;
}

void Admin::readInventory() {
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
        inventory.push_back(temporaryInventory);
    }
    binaryInventoryFile.close();
}

int Admin::findInventoryItem(string name) {
    int index = 0;
    for (const auto& item : inventory) {
        if (item.itemName == name) {
            return index;
        }
        index++;
    }
    return -1;
}

void Admin::findUsername(string usernameSearch) {
    bool found = false;
    int index = 0;
    for (const auto& user : userInfo) {
        if (user.username == usernameSearch) {
            // User found
            found = true;
            userInfoIndex = index;
            break;
        }
        index++;
    }


    if (!found) {
        cout << "User " << usernameSearch << " not found" << endl;
    }
}