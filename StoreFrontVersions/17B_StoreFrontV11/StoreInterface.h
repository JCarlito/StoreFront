/* 
 * File:   StoreInterface.h
 * Author: Josh Carlito
 *
 * Created on April 11, 2023, 10:17 PM
 */

#ifndef STOREINTERFACE_H
#define STOREINTERFACE_H
#include "StoreFront.h"
#include "Inventory.h"

class StoreInterface {
private:
    InventoryClass store;
    vector<Inventory> inventory;
public:
    StoreInterface(){
        store.readInventory();
    }
    void displayStore();
    void displayStoreMenu();
};

#endif /* STOREINTERFACE_H */

