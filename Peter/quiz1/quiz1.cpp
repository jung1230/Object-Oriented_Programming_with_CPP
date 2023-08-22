#include <iostream>


void A(){
  int *ptr= new int[3];

  ptr[0]=1;
  ptr[1]=2;
  ptr[2]=3;

  delete [] ptr; 
}

void B(){
  int *ptr= new int;
  *ptr=5;
  delete ptr; 
}

void C(){
  int *ptr= new int[3];

  ptr[0]=1;
  ptr[1]=2;
  ptr[2]=3;
  delete [] ptr;
}

void D(){
  int *ptr= new int;
  int *q=ptr;

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
  
