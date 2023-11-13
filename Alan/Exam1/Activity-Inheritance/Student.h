#ifndef STUDENT_H_
#define STUDENT_H_

#include <string>
#include "Person.h"

class Student : public Person {

private:
    float gpa;

public:
   Student(float _gpa, std::string name);
   float getGPA( );
   void Print();
};

#endif /* STUDENT_H_ */
