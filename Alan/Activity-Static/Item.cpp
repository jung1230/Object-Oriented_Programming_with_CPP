#include "Item.h"
#include <iostream>

int Item::getNumberOfItems( ) {
  //std::cout << itemNum << std::endl;
  return numberOfItems;
}

Item::Item(int i, float p) : itemNum(i), price(p) {
   numberOfItems++;
}


Item::Item(const Item& item){
   this->itemNum = item.itemNum;
   this->price = item.price;
   numberOfItems++;
}


Item::Item( ) {
  numberOfItems++;
 }

Item::~Item( ) {
  numberOfItems--;
}

void Item::print( ) {
   std::cout << "number of items: " << numberOfItems;
   std::cout << ", item number: " << itemNum;
   std::cout << ", price: " << price << std::endl;
}

int Item::numberOfItems = 0; // initialize statics like this

