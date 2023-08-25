#include <string>
#include <iostream>
#include "HelloWorld.h"

HelloWorld::HelloWorld(std::string _name) {
   name = _name;
}

void HelloWorld::sayHello( ) {
   std::cout << "Hello world and Hello "+name+"!" << std::endl;
}
