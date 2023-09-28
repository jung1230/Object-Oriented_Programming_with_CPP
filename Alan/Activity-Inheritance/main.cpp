#include "TeachingAssistant.h"
#include <iostream>

int main(int argc, char* argv[ ]) {
   // part 1
   Student s = Student(2.9, "Sam");
   Person p = Person("Peter");
   s.Print();
   p.Print();
   std::cout << "Name = " << s.getName() << " GPA = " << s.getGPA() << std::endl;

   // part 2
    // std::cout << "part 2" << std::endl;
   // Person *personPtr;
   // Student *studentPtr;
   // studentPtr = &p; // compiler will complain about this (person is a base class)
   // personPtr = &s;

   // part 3
   std::cout << "part 3" << std::endl;
   Person *personPtr;
   Student *studentPtr;

   studentPtr = &s; 
   personPtr = &s;
   personPtr -> Print();
   studentPtr -> Print();

   // part 4
   std::cout << "part 4" << std::endl;
   TeachingAssistant ta1 = TeachingAssistant(4, "Alan", "oo programing");

}
