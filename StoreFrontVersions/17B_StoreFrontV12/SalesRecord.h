/* 
 * File:   SalesRecord.h
 * Author: Josh Carlito
 *
 * Created on April 11, 2023, 8:15 PM
 */

#ifndef SALESRECORD_H
#define SALESRECORD_H
#include "StoreFront.h"

class SalesRecord {
private:
    vector<Customer> salesInfo;
    int findCustomer(Customer& customer);
    void writeCustomerInfoVec(fstream& binaryCustomerInfoFile);
    void accumulateSalesInfo(Customer& customer, int index);
    int findCartItem(const CartItem & newItem, int index);
public:
    void writeCustomerInformation(Customer& customer);
    void readCustomerInformation();
};

#endif /* SALESRECORD_H */

