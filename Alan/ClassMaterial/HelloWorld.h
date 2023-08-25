#ifndef HelloWorld_H_
#define HelloWorld_H_

#include <string>

class HelloWorld {

private:
   std::string name;

public:
   HelloWorld(std::string _name);

   void sayHello( );
};

#endif /* HELLOWORLD_H_ */