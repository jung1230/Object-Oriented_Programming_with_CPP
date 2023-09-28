#include "Item.h"
#include "ItemD.h"

#include <iostream>


void ExampleTests(){

  int numItems = Item::getNumberOfItems();
  std::cout << "numItems = " << numItems << std::endl;


  Item *iP1 = new Item(4, 6.50);
  Item *iP2 = new Item(5, 7.50);
  numItems = Item::getNumberOfItems();
  std::cout << "numItems of Item = " << numItems << std::endl;
  numItems = ItemD::getNumberOfItems();
  std::cout << "numItems of ItemD = " << numItems << std::endl;
  ItemD *iP3 = new ItemD(4, 6.50);
  ItemD *iP4 = new ItemD(5, 7.50);
  numItems = Item::getNumberOfItems();
  std::cout << "numItems of Item = " << numItems << std::endl;
  numItems = ItemD::getNumberOfItems();
  std::cout << "numItems of ItemD = " << numItems << std::endl;

}


int main (int argc, char *argv[]) { 
  std::cout << "Started Example Tests " << std::endl;
  ExampleTests();
  std::cout << "Completed Example Tests " << std::endl << std::endl;
}
