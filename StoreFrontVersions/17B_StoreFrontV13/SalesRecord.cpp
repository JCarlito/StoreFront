#include "SalesRecord.h"

void SalesRecord::writeCustomerInformation(Customer& customer) {
    fstream binaryCustomerInfoFile;
    char tempUsernameLength = 0;
    char tempItemNameLength = 0;
    bool fileExists;

    // Try opening a file to see if it exists
    binaryCustomerInfoFile.open("CustomerInfo.bin", ios::in | ios::binary);
    fileExists = binaryCustomerInfoFile.is_open();

    // Check to see if file exists, if not create it.
    if (!fileExists) {
        binaryCustomerInfoFile.open("CustomerInfo.bin", ios::out | ios::binary);
        binaryCustomerInfoFile.close();
    }
    binaryCustomerInfoFile.open("CustomerInfo.bin", ios::in | ios::out | ios::binary);

    binaryCustomerInfoFile.seekp(0, ios::beg);
    //if file is empty, write the first record.
    if (binaryCustomerInfoFile.tellp() == 0) {
        tempUsernameLength = customer.username.size();
        binaryCustomerInfoFile.write(&tempUsernameLength, sizeof (char));
        binaryCustomerInfoFile.write(&customer.username[0], tempUsernameLength);
        binaryCustomerInfoFile.write(
                reinterpret_cast<char*> (&customer.cart.totalCost), sizeof (float));
        binaryCustomerInfoFile.write(
                reinterpret_cast<char*> (&customer.cart.totalItems), sizeof (int));
        binaryCustomerInfoFile.write(
                reinterpret_cast<char*> (&customer.cart.totalQuantity), sizeof (int));
        for (auto& item : customer.cart.items) {
            tempItemNameLength = item.itemName.size();
            binaryCustomerInfoFile.write(&tempItemNameLength, sizeof (char));
            binaryCustomerInfoFile.write(&item.itemName[0], tempItemNameLength);
            binaryCustomerInfoFile.write(
                    reinterpret_cast<char*> (&item.quantity), sizeof (int));
            binaryCustomerInfoFile.write(
                    reinterpret_cast<char*> (&item.cost), sizeof (float));
        }
    } else {
        readCustomerInformation();
        int index = findCustomer(customer);
        if (index != -1) {
            salesInfo[index].cart.totalCost += customer.cart.totalCost;
            salesInfo[index].cart.totalQuantity += customer.cart.totalQuantity;
            accumulateSalesInfo(customer, index);
        } else {
            salesInfo.push_back(customer);
        }
        binaryCustomerInfoFile.close(); // Close the file here

        // Clear the contents of the file and close it
        binaryCustomerInfoFile.open("CustomerInfo.bin", ios::out);
        binaryCustomerInfoFile.close();

        // Reopen the file in the desired mode and write the updated info
        binaryCustomerInfoFile.open("CustomerInfo.bin", ios::in | ios::out | ios::binary);
        writeCustomerInfoVec(binaryCustomerInfoFile);
    }
    binaryCustomerInfoFile.close();
}

void SalesRecord::writeCustomerInfoVec(fstream& binaryCustomerInfoFile) {
    char tempUsernameLength = 0;
    char tempItemNameLength = 0;

    for (const auto& customer : salesInfo) {
        tempUsernameLength = customer.username.size();
        binaryCustomerInfoFile.write(&tempUsernameLength, sizeof (char));
        binaryCustomerInfoFile.write(&customer.username[0], tempUsernameLength);
        binaryCustomerInfoFile.write(reinterpret_cast<const char*> (&customer.cart.totalCost), sizeof (float));
        binaryCustomerInfoFile.write(reinterpret_cast<const char*> (&customer.cart.totalItems), sizeof (int));
        binaryCustomerInfoFile.write(reinterpret_cast<const char*> (&customer.cart.totalQuantity), sizeof (int));

        for (const auto& item : customer.cart.items) {
            tempItemNameLength = item.itemName.size();
            binaryCustomerInfoFile.write(&tempItemNameLength, sizeof (char));
            binaryCustomerInfoFile.write(&item.itemName[0], tempItemNameLength);
            binaryCustomerInfoFile.write(reinterpret_cast<const char*> (&item.quantity), sizeof (int));
            binaryCustomerInfoFile.write(reinterpret_cast<const char*> (&item.cost), sizeof (float));
        }
    }
}

void SalesRecord::accumulateSalesInfo(Customer& customer, int index) {
    for (const auto& newItem : customer.cart.items) {
        int itemIndex = findCartItem(newItem, index);

        if (itemIndex != -1) {
            // Item exists in the info cart, update quantity and cost
            salesInfo[index].cart.items[itemIndex].quantity += newItem.quantity;
            salesInfo[index].cart.items[itemIndex].cost += newItem.cost;
        } else {
            // New item, add it to the info cart
            salesInfo[index].cart.items.push_back(newItem);
            salesInfo[index].cart.totalItems++; // Update total number of unique items in the cart
        }
    }
}

int SalesRecord::findCustomer(Customer& customer) {
    int index = 0;
    for (const auto& info : salesInfo) {
        if (info.username == customer.username) {
            return index;
        }
        index++;
    }
    return -1;
}

void SalesRecord::readCustomerInformation() {
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

int SalesRecord::findCartItem(const CartItem & newItem, int index) {
    int itemIndex = 0;
    for (const auto& item : salesInfo[index].cart.items) {
        if (item.itemName == newItem.itemName) {
            return itemIndex;
        }
        itemIndex++;
    }
    return -1;
}