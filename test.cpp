#include <iostream>  // Including the necessary header for input/output operations

int main(void) {
    double n;  // Declaration of a double (floating-point) variable
    int i;     // Declaration of an integer variable

    // Prompt the user to enter a float and read the input into 'n'
    std::cout << "Enter a float: ";
    std::cin >> n;

    // Prompt the user to enter an integer and read the input into 'i'
    std::cout << "Enter an integer: ";
    std::cin >> i;

    // Output various computations and input values using 'cout'
    std::cout << "n == " << n
              << "\nn+1 == " << n + 1
              << "\nhalf of n == " << n / 2
              << "\ni == " << i << "\n\n";

    return 0;  // Return 0 to indicate successful program execution
}
