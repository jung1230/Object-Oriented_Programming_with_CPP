#include <string>
#include <iostream>
#include "Person.h"

Person::Person(std::string _name) {
   name = _name;
}

std::string Person::getName( ) {
   return name;
}

void Person::Print(){
    std::cout << name << std::endl;

}
   
