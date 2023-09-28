#include "Square.h"
#include "Circle.h"
#include <iostream>

using std::cout;
using std::endl;


void CompoundShapes(){
  Square square(4);

  Shape *shape[10]; // Allowed
  shape[0] = new Square(7); //Allowed: upcasting: a square is a shape.
  cout << "Square with length 4" << endl;
  cout << "Length = " << square.length()
       << " Area = " << square.area() 
       << " Circumference = " << square.circumference() 
       << endl;

  //  cout << "Length = " << shape->length() // Not Allowed; shape is a base class.
  cout << "Square with length 7" << endl;
  cout << "Area = " << shape[0]->area() 
       << " Circumference = " << shape[0]->circumference() 
       << endl;

  shape[1] = new Circle(3);
  cout << "circle with radius 3" << endl;
  cout << "Area = " << shape[1]->area() 
       << " Circumference = " << shape[1]->circumference() 
       << endl;
  shape[2] = new Circle(4);
  cout << "circle with radius 4" << endl;
  cout << "Area = " << shape[2]->area() 
       << " Circumference = " << shape[2]->circumference() 
       << endl;
  shape[3] = new Square(2);
  cout << "Square with length 2" << endl;
  cout << "Area = " << shape[3]->area() 
       << " Circumference = " << shape[3]->circumference() 
       << endl;

}

int main() {
  cout << "Enter CompoundShapes" << endl;
  CompoundShapes();
}
