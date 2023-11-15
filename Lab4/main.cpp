#include <iostream>
#include <chrono>
#include <optional>
#include <vector>

#include "poly.h"



std::optional<double> poly_test(polynomial& p1,
                                polynomial& p2,
                                std::vector<std::pair<power, coeff>> solution)

{
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    polynomial p3 = p1 * p2;

    auto p3_can_form = p3.canonical_form();

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    p3.print();

    if (p3_can_form != solution)
    {
        return std::nullopt;
    }

    return std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();
}

void bulky_Alan() {
    polynomial p1;
    std::cout << "Polynomial 1: ";
    p1.print();
    std::cout << "Degree of Polynomial 1: " << p1.find_degree_of() << std::endl;
    std::cout << std::endl;
    
    std::vector<std::pair<power, coeff>> terms = {{200, 3}, {100, -1},{32,0}, {300, 2}};
    polynomial p2(terms.begin(), terms.end());
    std::cout << "Polynomial 2: ";
    p2.print();
    std::cout << "Degree of Polynomial 2: " << p2.find_degree_of() << std::endl;
    std::cout << std::endl;

}




void test_mod(){
    // Example 1
    std::vector<std::pair<power, coeff>> terms1 = {{4, 1}, {2, 2}, {0, -3}};
    polynomial p1(terms1.begin(), terms1.end());
    p1.print();
    std::vector<std::pair<power, coeff>> terms2 = {{2, 1}, {0, 1}};
    polynomial p2(terms2.begin(), terms2.end());
    p2.print();

    polynomial remainder1 = p1 % p2;
    std::cout << "Remainder after division (Example 1): ";
    remainder1.print();

    // Example 2
    std::vector<std::pair<power, coeff>> terms3 = {{5, 2}, {3, -3}, {2, 4}, {1, 1}, {0, -1}};
    polynomial p3(terms3.begin(), terms3.end());
    p3.print();

    std::vector<std::pair<power, coeff>> terms4 = {{2, 1}, {0, 1}};
    polynomial p4(terms4.begin(), terms4.end());
    p4.print();

    polynomial remainder2 = p3 % p4;
    std::cout << "Remainder after division (Example 2): ";
    remainder2.print();

    // Example 3
    std::vector<std::pair<power, coeff>> terms5 = {{3, 2}, {2, 3}, {1, -4}, {0, 1}};
    polynomial p5(terms5.begin(), terms5.end());

    std::vector<std::pair<power, coeff>> terms6 = {{1, 1}, {0, -1}};
    polynomial p6(terms6.begin(), terms6.end());
    p6.print();
    p5.print();

    polynomial remainder3 = p5 % p6;
    std::cout << "Remainder after division (Example 3): ";
    remainder3.print();
}

void test_multi(){

    // Example 1
    std::vector<std::pair<power, coeff>> terms1 = {{2, 3}, {1, -1}, {3, 2}};
    polynomial p1(terms1.begin(), terms1.end());
    p1.print();

    std::vector<std::pair<power, coeff>> terms2 = {{1, 2}, {0, -1}};
    polynomial p2(terms2.begin(), terms2.end());
    p2.print();

    polynomial result1 = p1 * p2;
    std::cout << "Result of p1 * p2: ";
    result1.print();
    std::cout << "Degree of Result: " << result1.find_degree_of() << std::endl;
    std::cout << std::endl;

    // Example 2
    std::vector<std::pair<power, coeff>> terms3 = {{1, 2}, {0, 1}};
    polynomial p3(terms3.begin(), terms3.end());
    p3.print();

    std::vector<std::pair<power, coeff>> terms4 = {{0, -1}};
    polynomial p4(terms4.begin(), terms4.end());
    p4.print();

    polynomial result2 = p3 * p4;
    std::cout << "Result of p3 * p4: ";
    result2.print();
    std::cout << "Degree of Result: " << result2.find_degree_of() << std::endl;
    std::cout << std::endl;

    // Example 3
    std::vector<std::pair<power, coeff>> terms5 = {{3, 2}, {2, 3}, {1, -4}, {0, 1}};
    polynomial p5(terms5.begin(), terms5.end());
    p5.print();

    int constant = 0;
    std::cout << "Constant: " << constant << std::endl;

    polynomial result3 = p5 * constant;
    std::cout << "Result of p5 * constant: ";
    result3.print();
    std::cout << "Degree of Result: " << result3.find_degree_of() << std::endl;

    polynomial result4 =  constant * p5;
    std::cout << "Result of constant * p5: ";
    result4.print();
}


int main()
{
    //bulky_Alan();
    test_multi();



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




    // test_mod();
}