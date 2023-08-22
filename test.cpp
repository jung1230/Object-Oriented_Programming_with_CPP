#include <iostream>
//C++ system header files typically do not have .h extension
int main(void){
double n; // floating-point variable
int i;
// std refers to std namespace
std::cout << "Enter a float: "; // prompt for a number
std::cin >> n;
std::cout << "Enter an integer: "; // prompt for a number
std::cin >> i;
std::cout << " n == " << n
<< "\n n+1 == " << n+1
<< "\n half of n == " << n/2
<< "\n i == " << i
}
// A simple program with input and output
// Use cout and cin (C++) instead of
// printf and scanf (C)
// double, int: Built in “types” similar to C.
