#include "ItemD.h"

int ItemD::numberOfItemsD = 0;

int ItemD::getNumberOfItemsD() {
    return numberOfItemsD;
}

ItemD::ItemD(int i, float p) : Item(i, p) {
    numberOfItemsD++;
}

ItemD::ItemD() : Item() {
    numberOfItemsD++;
}

ItemD::ItemD(const ItemD& item) : Item(item) { //use the copy constructor in item.cpp
    numberOfItemsD++;
}

ItemD::~ItemD() {
    numberOfItemsD--;
}
