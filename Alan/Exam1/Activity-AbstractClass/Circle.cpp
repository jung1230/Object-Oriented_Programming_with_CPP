#include "Circle.h"

Circle::Circle(float s) :  radius(s) { };
Circle::~Circle( ) { }
double Circle::area( ) {return 3.14*radius*radius;}
double Circle::circumference() {return 2*3.14*radius;}
float Circle::length() {return radius;}
