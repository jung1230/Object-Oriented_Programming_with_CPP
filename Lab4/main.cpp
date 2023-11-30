#include <iostream>
#include <chrono>
#include <optional>
#include <vector>
#include <chrono>
#include <fstream>
#include <sstream>
#include <cassert>
#include "poly.h"

std::optional<double> poly_test(polynomial &p1,
                                polynomial &p2,
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

void bulky_Alan()
{
    polynomial p1;
    std::cout << "Polynomial 1: ";
    p1.print();
    std::cout << "Degree of Polynomial 1: " << p1.find_degree_of() << std::endl;
    std::cout << std::endl;

    std::vector<std::pair<power, coeff>> terms = {{200, 3}, {100, -1}, {32, 0}, {300, 2}};
    polynomial p2(terms.begin(), terms.end());
    std::cout << "Polynomial 2: ";
    p2.print();
    std::cout << "Degree of Polynomial 2: " << p2.find_degree_of() << std::endl;
    std::cout << std::endl;
}

void test_mod()
{
    // Example 1
    std::vector<std::pair<power, coeff>> terms1 = {{0, -3}, {4, 1}, {2, 2}};
    polynomial p1(terms1.begin(), terms1.end());
    p1.print();
    std::vector<std::pair<power, coeff>> terms2 = {{0, 1}, {2, 1}};
    polynomial p2(terms2.begin(), terms2.end());
    p2.print();

    polynomial remainder1 = p1 % p2;
    std::cout << "Remainder after division (Example 1): ";
    remainder1.print();
    std::cout << "\n";

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
    std::cout << "\n";

    // Example 3
    std::vector<std::pair<power, coeff>> terms5 = {{3, 2}, {2, 3}, {1, -4}, {0, 1}};
    polynomial p5(terms5.begin(), terms5.end());
    std::vector<std::pair<power, coeff>> terms6 = {{1, 1}, {0, -1}};
    polynomial p6(terms6.begin(), terms6.end());
    p5.print();
    p6.print();
    polynomial remainder3 = p5 % p6;
    std::cout << "Remainder after division (Example 3): ";
    remainder3.print();
    std::cout << "\n";

    p6.print();
    p5.print();
    polynomial remainder4 = p6 % p5;
    std::cout << "Remainder after division (Example 4): ";
    remainder4.print();
    std::cout << "\n";

    // Example4
    std::vector<std::pair<power, coeff>> terms7 = {{10, 5}, {5, -3}, {2, 2}, {1, 1}};
    polynomial p7(terms7.begin(), terms7.end());

    std::vector<std::pair<power, coeff>> terms8 = {{8, 4}, {4, 2}, {2, -1}};
    polynomial p8(terms8.begin(), terms8.end());
    p7.print();
    p8.print();
    polynomial result2 = p7 % p8;
    result2.print();
    result2 = 3 * (p7 % p8) + 5;
    result2.print();
    std::cout << "Degree of result2: " << result2.find_degree_of() << std::endl;
    std::cout << "\n";

    // Example5
    std::vector<std::pair<power, coeff>> terms9 = {{0, 0}};
    polynomial p9(terms9.begin(), terms9.end());
    p9.print();
    p8.print();
    polynomial result3 = p9 % p8;
    result3.print();
    std::cout << "Degree of result3: " << result3.find_degree_of() << std::endl;

    std::cout << "\n"
              << std::endl;
}

void long_express()
{
    std::vector<std::pair<power, coeff>> terms7 = {{10, 5}, {5, -3}, {2, 2}, {1, 1}};
    polynomial p7(terms7.begin(), terms7.end());
    std::vector<std::pair<power, coeff>> terms8 = {{8, 4}, {4, 2}, {2, -1}};
    polynomial p8(terms8.begin(), terms8.end());
    p7.print();
    p8.print();
    std::vector<std::pair<power, coeff>> terms9 = {{6, 5}, {5, -3}, {0, -2}, {17, 1}};
    polynomial p9(terms9.begin(), terms9.end());
    std::vector<std::pair<power, coeff>> terms10 = {{7, 4}, {4, 5}, {10, -1}};
    polynomial p10(terms10.begin(), terms10.end());
    polynomial result2 = p7 % p8;
    result2.print();
    result2 = 3 * (p7 % p8) + 5;
    result2.print();
    result2 = (3 * (p7 % p8) + 5) * 10;
    result2.print();
    result2 = 7 + (3 * (p7 % p8) + 5) * 10;
    result2.print();
    std::cout << "Degree of result2: " << result2.find_degree_of() << std::endl;
    std::cout << "\n";
}

void test_multi()
{

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

    polynomial result4 = constant * p5;
    std::cout << "Result of constant * p5: ";
    result4.print();
}

void test_Long_expression_with_degree()
{

    // // Test Case 1
    std::vector<std::pair<power, coeff>> terms1 = {{200, 3}, {100, -1}, {32, 0}, {300, 2}};
    polynomial p1(terms1.begin(), terms1.end());

    std::vector<std::pair<power, coeff>> terms2 = {{150, 2}, {32, 1}, {100, 1}};
    polynomial p2(terms2.begin(), terms2.end());

    auto start_time = std::chrono::high_resolution_clock::now();
    polynomial result1 = p1 * p2 + p1 - 2 * p2 % p1;
    auto end_time = std::chrono::high_resolution_clock::now();
    std::cout << "Degree of result1: " << result1.find_degree_of() << std::endl;

    result1.print();

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
    std::cout << "Time taken for expression 1: " << duration.count() << " microseconds" << std::endl;

    // Test Case 2
    std::vector<std::pair<power, coeff>> terms3 = {{1000, 5}, {500, -3}, {200, 2}, {150, 1}};
    polynomial p3(terms3.begin(), terms3.end());

    std::vector<std::pair<power, coeff>> terms4 = {{800, 4}, {400, 2}, {200, -1}};
    polynomial p4(terms4.begin(), terms4.end());

    start_time = std::chrono::high_resolution_clock::now();
    polynomial result2 = 3 * (p3 * p4 - 2 * p4 + p3 % p4) + 5;
    std::cout << "Degree of result2: " << result2.find_degree_of() << std::endl;

    end_time = std::chrono::high_resolution_clock::now();

    result2.print();

    duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
    std::cout << "Time taken for expression 2: " << duration.count() << " microseconds" << std::endl;

    // Test Case 3
    start_time = std::chrono::high_resolution_clock::now();
    std::vector<std::pair<power, coeff>> term69 = {{0, 0}};
    polynomial p69(term69.begin(), term69.end());
    polynomial result3 = (3 * (p3 * p4 - 2 * p4 + p3 % p4 + p3 + p4 + 87 + p4 * 5) + 5);
    std::cout << "Degree of result3: " << result3.find_degree_of() << std::endl;

    end_time = std::chrono::high_resolution_clock::now();

    result3.print();

    duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
    std::cout << "Time taken for expression 3: " << duration.count() << " microseconds" << std::endl;
}

void additional_test_cases()
{
    // Case 1: Zero divisor
    std::vector<std::pair<power, coeff>> terms1 = {{4, 1}, {2, 2}, {0, -2}};
    polynomial p1(terms1.begin(), terms1.end());
    p1.print();

    std::vector<std::pair<power, coeff>> zeroDivisorTerms = {{0, 0}};
    polynomial zeroDivisor(zeroDivisorTerms.begin(), zeroDivisorTerms.end());
    zeroDivisor.print();

    polynomial result1 = p1 % zeroDivisor;
    std::cout << "Remainder after division (Zero divisor): ";
    result1.print();
    std::cout << "\n";

    // Case 2: Zero remainder
    std::vector<std::pair<power, coeff>> zeroRemainderTerms = {{2, 1}, {0, 1}};
    polynomial zeroRemainder(zeroRemainderTerms.begin(), zeroRemainderTerms.end());
    zeroRemainder.print();
    zeroRemainder.print();
    std::cout << "zeroRemainder.find_degree_of();" << zeroRemainder.find_degree_of();
    polynomial result2 = zeroRemainder % zeroRemainder;
    std::cout << "Remainder after division (Zero remainder): ";
    result2.print();
    std::cout << "\n";

    // Case 3: Negative coefficients
    std::vector<std::pair<power, coeff>> negCoeffTerms = {{3, -2}, {1, -1}};
    polynomial negCoeffPoly(negCoeffTerms.begin(), negCoeffTerms.end());
    negCoeffPoly.print();

    std::vector<std::pair<power, coeff>> terms3 = {{1, 1}, {0, -1}};
    polynomial p3(terms3.begin(), terms3.end());
    p3.print();

    polynomial result3 = negCoeffPoly % p3;
    std::cout << "Remainder after division (Negative coefficients): ";
    result3.print();
    std::cout << "\n";

    // Case 4: Large coefficients
    std::vector<std::pair<power, coeff>> largeCoeffTerms = {{150, 2}, {32, 1}, {100, 1}};
    polynomial largeCoeffPoly(largeCoeffTerms.begin(), largeCoeffTerms.end());
    largeCoeffPoly.print();

    std::vector<std::pair<power, coeff>> terms4 = {{32, 1}, {0, 1}};
    polynomial p4(terms4.begin(), terms4.end());
    p4.print();

    polynomial result4 = largeCoeffPoly % p4;
    std::cout << "Remainder after division (Large coefficients): ";
    result4.print();
    std::cout << "\n";
}

void test_sparse()
{
    // Test 1
    std::vector<std::pair<power, coeff>> terms1 = {{10001, 3}, {1, -1}, {3, 2}};
    polynomial p1(terms1.begin(), terms1.end());
    p1.print();

    std::vector<std::pair<power, coeff>> terms2 = {{0, 2}};
    polynomial p2(terms2.begin(), terms2.end());
    p2.print();

    polynomial result1 = p1 * p2;
    std::cout << "Result of p1 * p2: ";
    result1.print();
    std::cout << "Degree of Result: " << result1.find_degree_of() << std::endl;
    std::cout << std::endl;
    // Test 2
    std::vector<std::pair<power, coeff>> terms3 = {{10001, 3}, {1, -1}, {3, 2}, {6969, 5}, {3737, 2}, {0, 87}};
    polynomial p3(terms3.begin(), terms3.end());
    p3.print();

    std::vector<std::pair<power, coeff>> terms4 = {{0, 2}};
    polynomial p4(terms4.begin(), terms4.end());
    p4.print();

    polynomial result2 = p3 * p4;
    std::cout << "Result of p3 * p4: ";
    result2.print();
    std::cout << "Degree of Result: " << result2.find_degree_of() << std::endl;
    std::cout << std::endl;
    // Test 3
    std::vector<std::pair<power, coeff>> terms5 = {{10001, 3}, {1, -1}, {3, 2}, {6969, 5}, {3737, 2}, {0, 87}};
    polynomial p5(terms5.begin(), terms5.end());
    p5.print();

    std::vector<std::pair<power, coeff>> terms6 = {{0, 7}};
    polynomial p6(terms6.begin(), terms6.end());
    p6.print();

    polynomial result3 = p5 * p6;
    std::cout << "Result of p5 * p6: ";
    result3.print();
    std::cout << "Degree of Result: " << result3.find_degree_of() << std::endl;
    std::cout << std::endl;

    result3 = 10 * p5;
    std::cout << "Result of p5 * p6: ";
    result3.print();
    std::cout << "Degree of Result: " << result3.find_degree_of() << std::endl;
    std::cout << std::endl;

    result3 = p6 + p5;
    std::cout << "Result of p5 + p6: ";
    result3.print();
    std::cout << "Degree of Result: " << result3.find_degree_of() << std::endl;
    std::cout << std::endl;

    result3 = p5 % p6 % p5;
    std::cout << "Result of p5%p6%p5: ";
    result3.print();
    std::cout << "Degree of Result: " << result3.find_degree_of() << std::endl;
    std::cout << std::endl;
}

void parsefile(const std::string &filename, std::vector<polynomial> &test)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    std::string line;
    polynomial currentPolynomial = polynomial();

    while (std::getline(file, line))
    {
        if (line == ";")
        {
            // End of polynomial, add it to the vector and reset
            // currentPolynomial.print();
            test.push_back(currentPolynomial);
            currentPolynomial = polynomial();
        }
        else
        {
            // Parse coefficient and power from the line
            std::istringstream iss(line);
            coeff coefficient;
            power exponent;
            char x; // To consume 'x'
            iss >> coefficient >> x >> x >> exponent;
            currentPolynomial.addTerm(exponent, coefficient);
        }
    }

    file.close();
}

void writePolynomialsToFile(const std::string &filename, const polynomial &answer)
{
    std::ofstream outfile(filename);
    if (!outfile.is_open())
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    answer.outputprint(outfile);

    outfile.close();
}

void test_simple()
{
    std::vector<polynomial> test;
    parsefile("simple_poly.txt", test);
    // for(auto & poly: test){
    //     poly.print();
    // }
    std::vector<std::pair<power, coeff>> terms1 = {{0, 1}};
    polynomial test_poly(terms1.begin(), terms1.end());
    auto start_time = std::chrono::high_resolution_clock::now();
    for (auto &poly : test)
    {
        test_poly = test_poly * poly;
    }
    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
    std::cout << "Time taken for expression 1: " << duration.count() << " microseconds" << std::endl;
    // std::cout << "Mul is done" << std::endl;
    //  test_poly.print();
    writePolynomialsToFile("output.txt", test_poly);
}

void test_find_degree_of()
{

    // Test case 1: Polynomial with a single term
    std::vector<std::pair<power, coeff>> terms1 = {{3, 2}};
    polynomial p1(terms1.begin(), terms1.end());
    assert(p1.find_degree_of() == 3);

    // Test case 2: Polynomial with multiple terms
    std::vector<std::pair<power, coeff>> terms2 = {{2, 5}, {4, 2}, {1, 7}};
    polynomial p2(terms2.begin(), terms2.end());
    assert(p2.find_degree_of() == 4);

    // Test case 3: Empty polynomial
    polynomial poly3;
    assert(poly3.find_degree_of() == 0);

    // Test case 4: Constant polynomial
    std::vector<std::pair<power, coeff>> terms3 = {{0, 8}};
    polynomial poly4(terms3.begin(), terms3.end());
    assert(poly4.find_degree_of() == 0);

    // Test case 5: Polynomial with zero coefficients
    std::vector<std::pair<power, coeff>> terms4 = {{3, 0}, {1, 0}, {0, 0}};
    polynomial poly5(terms4.begin(), terms4.end());
    poly5.print();
    assert(poly5.find_degree_of() == 0);

    std::vector<std::pair<power, coeff>> terms5 = {{3, 4}, {2, 7}, {3, 1}};
    polynomial poly6(terms5.begin(), terms5.end());
    poly6.print();
    poly6.print();

    assert(poly6.find_degree_of() == 3);
    polynomial result = poly6 + poly6;
    result.print();
    result.print();

    result.print();
    assert(result.find_degree_of() == 3);

    std::cout << "All test cases passed!" << std::endl;
}

int main()
{
    // bulky_Alan();
    // test_multi();
    // test_mod();
    // additional_test_cases();
    //  long_express();
    //  test_Long_expression_with_degree();
    // test_sparse();
    /** We're doing (x+1)^2, so solution is x^2 + 2x + 1*/
    test_simple();
    // test_find_degree_of();

    std::vector<std::pair<power, coeff>> solution = {{2, 1}, {1, 2}, {0, 1}};

    /** This holds (x+1), which we'll pass to each polynomial */
    std::vector<std::pair<power, coeff>> poly_input = {{1, 1}, {0, 1}};

    polynomial p1(poly_input.begin(), poly_input.end());
    polynomial p2(poly_input.begin(), poly_input.end());

    std::optional<double> result = poly_test(p1, p2, solution);

    if (result.has_value())
    {
        std::cout << "Passed test, took " << result.value() / 1000 << " seconds" << std::endl;
    }
    else
    {
        std::cout << "Failed test" << std::endl;
    }

    // test_mod();
}