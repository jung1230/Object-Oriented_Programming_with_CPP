#ifndef CIRCLE_H_
#define CIRCLE_H_
#include "Shape.h"

class Circle : public Shape {
public:
   Circle(float);
   ~Circle( );
   double area( );
   double circumference();
   float length();
private:
   float radius;
};
#endif 