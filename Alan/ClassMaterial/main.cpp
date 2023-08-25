#include "HelloWorld.h"

int main(int argc, char* argv[ ]) {
   HelloWorld* hello1 = new HelloWorld("Sam");
   HelloWorld* hello2 = new HelloWorld("Mary");
   HelloWorld helloObj("Sanjay");
   
   hello1->sayHello();
   hello2->sayHello();
   helloObj.sayHello();

   delete hello1;
   hello1 = hello2;
   hello1->sayHello();
   
   delete hello1;
}
