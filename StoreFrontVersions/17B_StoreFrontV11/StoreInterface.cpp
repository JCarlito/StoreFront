#include "StoreInterface.h"

void StoreInterface::displayStore() {
    store.displayStore();
}

void StoreInterface::displayStoreMenu() {
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