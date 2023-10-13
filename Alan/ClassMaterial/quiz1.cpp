#include <iostream>


void A(){
  int *ptr= new int[3];

  ptr[0]=1;
  ptr[1]=2;
  ptr[2]=3;

  // delete ptr;
  delete[] ptr; // Corrected memory deallocation for arrays 

  // Always use delete[] to deallocate memory for arrays allocated with new[], 
  // and use delete to deallocate memory allocated with new (for single objects). 
  // This helps prevent memory leaks and other memory-related issues.
}

void B(){
  int *ptr= new int;
  *ptr=5;

  // delete ptr[];
  delete ptr; 
}

void C(){
  int *ptr= new int[3];

  ptr[0]=1;
  ptr[1]=2;
  ptr[2]=3;

  delete[] ptr;



}

void D(){
  int *ptr= new int;
  int *q=ptr; 

  // delete ptr;
  delete q;
}

void E(){
  int *ptr= new int[3];
  int *ptr1 = new int;

  ptr[0]=1;
  ptr[1]=2;
  ptr[2]=3;

  *ptr1=5;

  delete ptr1;
  delete [] ptr;
}



int main(void){
  A();
  B();
  C();
  D();
  E();
}
  