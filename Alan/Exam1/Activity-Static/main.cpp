#include "Item.h"
#include "ItemD.h"
#include <iostream>

int main() {
    Item item1(1, 10.0);
    Item item2;
    Item item3(item1);
    std::cout << "Number of Items: " << Item::getNumberOfItems() << std::endl;
    std::cout << "Number of ItemD: " << ItemD::getNumberOfItemsD() << std::endl;

    ItemD itemD1(2, 20.0);
    ItemD itemD2;
    ItemD itemD3(itemD1);
    std::cout << "Number of Items: " << Item::getNumberOfItems() << std::endl;
    std::cout << "Number of ItemD: " << ItemD::getNumberOfItemsD() << std::endl;

    item1.print();
    item2.print();
    item3.print();

    itemD1.print();
    itemD2.print();
    itemD3.print();

    std::cout << "Number of Items: " << Item::getNumberOfItems() << std::endl;
    std::cout << "Number of ItemD: " << ItemD::getNumberOfItemsD() << std::endl;

    return 0;
}
