#include "ShoppingCart.h"

void ShoppingCart::addToCart(string itemName, int quantity) {
    int inventoryIndex = inventory.findInventoryItem(itemName);
    int cartIndex;
    CartItem tempCartItem;
    customerCart.totalItems = 0;
    customerCart.totalCost = 0.0f;
    customerCart.totalQuantity = 0;

    inventory.emptyInventory(inventoryIndex);
    if (inventory.getStatus(inventoryIndex)) {
        tempCartItem.itemName = inventory.getItemName(inventoryIndex);
        cartIndex = findCartItem(tempCartItem);
        if (cartIndex != -1) {
            quantity = inventory.getStock(inventoryIndex) - quantity < 0 ?
                    inventory.getStock(inventoryIndex) : quantity;
            inventory.updateStockFromCart(quantity, inventoryIndex, 1);
            customerCart.items[cartIndex].quantity += quantity;
            customerCart.items[cartIndex].cost += inventory.getCost(inventoryIndex) * quantity;
            inventory.emptyInventory(inventoryIndex);
        } else {
            quantity = inventory.getStock(inventoryIndex) - quantity < 0 ?
                    inventory.getStock(inventoryIndex) : quantity;
            inventory.updateStockFromCart(quantity, inventoryIndex, 1);
            tempCartItem.quantity = quantity;
            tempCartItem.cost = inventory.getCost(inventoryIndex) * quantity;
            customerCart.items.push_back(tempCartItem);
            inventory.emptyInventory(inventoryIndex);
        }
    } else {
        cout << endl;
        cout << inventory.getItemName(inventoryIndex) << " is OUT OF STOCK";
        cout << endl << endl;
    }

    customerCart.totalItems = customerCart.items.size();
    for (int i = 0; i < customerCart.totalItems; i++) {
        customerCart.totalCost += customerCart.items[i].cost;
        customerCart.totalQuantity += customerCart.items[i].quantity;
    }
}

void ShoppingCart::removeFromCart(string itemName, int quantity) {
    int inventoryIndex = inventory.findInventoryItem(itemName);
    int cartIndex;
    CartItem tempCartItem;

    tempCartItem.itemName = inventory.getItemName(inventoryIndex);
    cartIndex = findCartItem(tempCartItem);
    // If item is in the cart
    if (cartIndex != -1) {
        // Add the stock back to the inventory
        inventory.updateStockFromCart(quantity, inventoryIndex, 0);
        // subtract the stock from the cart
        customerCart.items[cartIndex].quantity -= quantity;
        // if the items quantity equals zero
        if (customerCart.items[cartIndex].quantity == 0) {
            // Subtract from total cost and quantity
            customerCart.totalCost -= inventory.getCost(inventoryIndex) * quantity;
            customerCart.totalQuantity -= quantity;
            customerCart.totalItems -= 1;
            // Erase the item from the cart
            customerCart.items.erase(customerCart.items.begin() + cartIndex);
        } else {
            // Subtract the cost from those items
            customerCart.items[cartIndex].cost -= inventory.getCost(inventoryIndex) * quantity;
            // Subtract from total cost and quantity
            customerCart.totalCost -= inventory.getCost(inventoryIndex) * quantity;
            customerCart.totalQuantity -= quantity;
        }
        // If the user made the item out of stock previously make it back 
        // in stock
        if (inventory.getStatus(inventoryIndex) == false) {
            inventory.updateStatusFromCart(inventoryIndex, 1);
        }
        // Else the item was not found in the cart
    } else {
        cout << endl << "The Item is not in your cart!" << endl;
    }
}

int ShoppingCart::findCartItem(const CartItem & newItem) {
    int index = 0;
    for (const auto& item : customerCart.items) {
        if (item.itemName == newItem.itemName) {
            return index;
        }
        index++;
    }
    return -1;
}