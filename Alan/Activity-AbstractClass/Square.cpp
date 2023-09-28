#include "Square.h"

Square::Square(float s) : side(s) { };
Square::~Square( ) { }
double Square::area( ) {return side*side;}
double Square::circumference() {return 4.0*side;}
float Square::length() {return side;}
