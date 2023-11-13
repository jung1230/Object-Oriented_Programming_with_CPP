#include <iostream>
#include <chrono>
#include <optional>
#include <vector>

#include "poly.h"

// std::optional<double> poly_test(polynomial& p1,
//                                 polynomial& p2,
//                                 std::vector<std::pair<power, coeff>> solution)

// {
//     std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

//     polynomial p3 = p1 * p2;

//     auto p3_can_form = p3.canonical_form();

//     std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

//     p3.print();

//     if (p3_can_form != solution)
//     {
//         return std::nullopt;
//     }

//     return std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();
// }


void bulky_Alan() {
    // polynomial p1;
    // std::cout << "Polynomial 1: ";
    // p1.print();
    // std::cout << "Degree of Polynomial 1: " << p1.find_degree_of() << std::endl;
    // std::cout << std::endl;
    
    std::vector<std::pair<power, coeff>> terms = {{200, 3}, {100, -1}, {300, 2}};
    polynomial p2(terms.begin(), terms.end());
    std::cout << "Polynomial 2: ";
    p2.print();
    std::cout << "Degree of Polynomial 2: " << p2.find_degree_of() << std::endl;
    std::cout << std::endl;

    polynomial p44(terms.begin(), terms.end());
    polynomial p3 = p44 + p2;
    std::cout << "Polynomial 3 (p44 + p2): ";
    p3.print();
    std::cout << "Degree of Polynomial 3: " << p3.find_degree_of() << std::endl;
    std::cout << std::endl;

    std::vector<std::pair<power, coeff>> terms1 = {{2, 3}, {1, 1}, {1, -1}, {0, 2}};
    polynomial p88(terms1.begin(), terms1.end());
    polynomial p33 = p88 + p2;
    std::cout << "Polynomial 33 (p88 + p2): ";
    p33.print();
    std::cout << "Degree of Polynomial 33: " << p33.find_degree_of() << std::endl;
    std::cout << std::endl;

    // int constant = 5;
    // polynomial p4 = p2 + constant;
    // std::cout << "Polynomial 4 (p2 + " << constant << "): ";
    // p4.print();
    // std::cout << "Degree of Polynomial 4: " << p4.find_degree_of() << std::endl;
    // std::cout << std::endl;

    // polynomial p5 = constant + p2;
    // std::cout << "Polynomial 5 (" << constant << " + p2): ";
    // p5.print();
    // std::cout << "Degree of Polynomial 5: " << p5.find_degree_of() << std::endl;
    // std::cout << std::endl;
}

int main()
{

    bulky_Alan();

    // /** We're doing (x+1)^2, so solution is x^2 + 2x + 1*/
    // std::vector<std::pair<power, coeff>> solution = {{2,1}, {1,2}, {0,1}};

    // /** This holds (x+1), which we'll pass to each polynomial */
    // std::vector<std::pair<power, coeff>> poly_input = {{1,1}, {0,1}};

    // polynomial p1(poly_input.begin(), poly_input.end());
    // polynomial p2(poly_input.begin(), poly_input.end());

    // std::optional<double> result = poly_test(p1, p2, solution);

    // if (result.has_value())
    // {
    //     std::cout << "Passed test, took " << result.value()/1000 << " seconds" << std::endl;
    // } 
    // else 
    // {
    //     std::cout << "Failed test" << std::endl;
    // }

}