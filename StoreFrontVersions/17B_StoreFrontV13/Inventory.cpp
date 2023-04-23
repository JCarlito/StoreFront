#include "Inventory.h"

void InventoryClass::emptyInventory(int item) {
    if (inventory[item].stock <= 0) {
        inventory[item].status = false;
    }
}

int InventoryClass::findInventoryItem(string name) {
    int index = 0;
    for (const auto& item : inventory) {
        if (item.itemName == name) {
            return index;
        }
        index++;
    }
    return -1;
}

void InventoryClass::readInventory() {
    inventory.clear();
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
    sort(inventory.begin(), inventory.end(), comparePriceLowToHigh);
}

void InventoryClass::writeInventory() {
    fstream binaryInventoryFile;
    char tempItemNameLength = 0;
    binaryInventoryFile.open("Inventory.bin", ios::out | ios::binary);
    if (!binaryInventoryFile.is_open()) {
        cout << "Error opening file!" << endl;
        return;
    }

    binaryInventoryFile.seekp(0, ios::beg);
    for (auto& item : inventory) {
        tempItemNameLength = item.itemName.size();
        binaryInventoryFile.write(&tempItemNameLength, sizeof (char));
        binaryInventoryFile.write(&item.itemName[0], tempItemNameLength);
        binaryInventoryFile.write(reinterpret_cast<char*> (&item.cost), sizeof (float));
        binaryInventoryFile.write(reinterpret_cast<char*> (&item.stock), sizeof (int));
        binaryInventoryFile.write(reinterpret_cast<char*> (&item.status), sizeof (bool));
    }
    binaryInventoryFile.close();
}

void InventoryClass::displayStore() {
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
    for (const auto& item : inventory) {
        if (item.status) {
            cout << setw(38) << item.itemName;
            cout << " $" << setw(36) << item.cost;
            cout << setw(37) << item.stock << endl;
        }
    }
    cout << endl;
}

vector<Inventory> InventoryClass::inventory;