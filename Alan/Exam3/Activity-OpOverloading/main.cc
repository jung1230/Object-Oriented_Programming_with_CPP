#include <iostream>
#include "mytime.h"

int main() {
// Overload the + operator as a member function of the Time class.
// • Write test code in main.cpp to prove it’s working.
// • Make sure you handle hours overflow.
// • Make sure the original object is not modified
    Time t1(2, 18);  
    Time t2(3, 8);   
    Time result = t1 + t2;
    std::cout << "Result: " << result.GetDays() << " days, " << result.GetHours() << " hours\n";


// Add a function to allow you to multiply a Time object by a constant value.
// • e.g. Time t2 = t1 * 3;
    result = t1 *3;
    std::cout << "Result: " << result.GetDays() << " days, " << result.GetHours() << " hours\n";

// Add a function to allow you to multiply a constant value with a Time object in the opposite
// order.
// • e.g. Time t2 = 3 * t1;
// • What type of function should this be and why?
    result = 3 * t1;
    std::cout << "Result: " << result.GetDays() << " days, " << result.GetHours() << " hours\n";


// Overload the << operator to allow printing a Time object.
    std::cout << t1 << t2 << std::endl;


// Overload the * operator to support multiplication of two Time objects and test as before.
// • For simplicity, multiply the days and hours components separately.
// • If time permits, come back and do this by converting to hours, taking product and remapping to days/hours    
    result = t1 * t2;
    std::cout << result << std::endl;
    
    
    
    return 0;
}