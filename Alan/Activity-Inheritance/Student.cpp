#include <string>
#include <iostream>
#include "Student.h"

Student::Student(float _gpa, std::string name): Person(name)  {
   gpa = _gpa;
}

float Student::getGPA( ) {
   return gpa;
}

void Student::Print(){

   std::cout << this -> getName() << gpa << std::endl;

}
