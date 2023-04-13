/* 
 * File:   Inventory.h
 * Author: Josh Carlito
 *
 * Created on April 11, 2023, 7:00 PM
 */

#ifndef INVENTORY_H
#define INVENTORY_H

#include "StoreFront.h"

class InventoryClass {
private:
    static vector<Inventory> inventory;

    static bool comparePriceLowToHigh(const Inventory& item1, const Inventory & item2) {
        return item1.cost < item2.cost;
    }
public:
    void emptyInventory(int item);
    int findInventoryItem(string name);
    void writeInventory();
    void readInventory();
    void displayStore();

    void updateStockFromCart(int quantity, int index, bool option) {
        if (option)
            inventory[index].stock -= quantity;
        else inventory[index].stock += quantity;
    }

    void updateStatusFromCart(int index, bool newStatus) {
        inventory[index].status = newStatus;
    }

    bool getStatus(int index) {
        return inventory[index].status;
    }

    string getItemName(int index) {
        return inventory[index].itemName;
    }

    float getCost(int index) {
        return inventory[index].cost;
    }

    int getStock(int index) {
        return inventory[index].stock;
    }
};

#endif /* INVENTORY_H */

