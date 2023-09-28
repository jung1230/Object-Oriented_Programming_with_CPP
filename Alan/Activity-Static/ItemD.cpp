#include "ItemD.h"
#include <iostream>

int ItemD::getNumberOfItems( ) {
  //std::cout << itemNum << std::endl;
  return derivednumberOfItems;
}

ItemD::ItemD(int i, float p) : Item(i,p) {
   derivednumberOfItems++;
}


ItemD::ItemD(const ItemD& itemD) :Item(itemD){
   derivednumberOfItems++;

}


ItemD::ItemD( ) {
  derivednumberOfItems++;
 }

ItemD::~ItemD( ) {
  derivednumberOfItems--;
}

void ItemD::print( ) {
   std::cout << "number of items: " << derivednumberOfItems;
   std::cout << ", item number: " << itemNum;
   std::cout << ", price: " << price << std::endl;
}

int ItemD::derivednumberOfItems = 0; // initialize statics like this

