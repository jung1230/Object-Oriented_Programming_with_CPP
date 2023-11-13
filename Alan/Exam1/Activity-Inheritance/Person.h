#ifndef PERSON_H_
#define PERSON_H_
#include <string>

class Person {

private: 
   std::string name;

public:
   Person(std::string _name);
   std::string getName( );
   virtual void Print();
};

#endif /* PERSON_H_ */
   
