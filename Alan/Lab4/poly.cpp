#include "poly.h"
#include <iostream>
#include <algorithm>
#include <iterator>
#include <mutex>
#include <thread>

polynomial::polynomial() : terms({{0, 0}})
{
    // Alan
}



polynomial::polynomial(const polynomial &other) : terms(other.terms)
{
    // Alan
}

void polynomial::print() const
{
    // Alan
    std::map<power, coeff> sorted_terms = canonical_form();
    if (sorted_terms.empty())
    {
        std::cout << "empty";
    }
    else
    {
        auto iter = sorted_terms.begin();
        std::cout << iter->second << "(x^" << iter->first << ")";

        // Print the rest of the terms
        for (iter++; iter != sorted_terms.end(); iter++)
        {
            std::cout << " + " << iter->second << "(x^" << iter->first << ")";
        }
    }
    std::cout << std::endl;
}

polynomial &polynomial::operator=(const polynomial &other)
{
    // self assignment
    if (this == &other)
    {
        return *this;
    }

    // copy terms
    this->terms = other.terms;

    return *this;
}

size_t polynomial::find_degree_of() const
{
    // Alan
    if (terms.empty())
    {
        return 0;
    }
    else
    {
        return terms.rbegin()->first;
    }
}

std::map<power, coeff> polynomial::canonical_form() const
{
    std::map<power, coeff> combined_terms;

    for (const auto &term : terms)
    {
        // If the term's power does not match the last term's power, or the combined_terms map is empty, add the term
        if (term.second != 0)
        {
            auto &existing_term = combined_terms[term.first];
            existing_term += term.second;

            // If the resulting coefficient is zero, remove the term from the map
            if (existing_term == 0)
            {
                combined_terms.erase(term.first);
            }
        }
    }

    return combined_terms;
}





// + operator overload
polynomial polynomial::operator+(const polynomial &other) const
{
    polynomial result;
    std::map<power, coeff> sorted_terms1 = canonical_form();
    std::map<power, coeff> sorted_terms2 = other.canonical_form();

    auto iter1 = sorted_terms1.begin();
    auto iter2 = sorted_terms2.begin();

    // loop through both polynomials
    while (iter1 != sorted_terms1.end() && iter2 != sorted_terms2.end())
    {
        // if both terms have the same power
        if (iter1->first == iter2->first)
        {
            result.terms[iter1->first] = iter1->second + iter2->second;
            iter1++;
            iter2++;
        }
        // if the power of the first term is greater than the second, move the first one into result directly
        else if (iter1->first > iter2->first)
        {
            result.terms[iter1->first] = iter1->second;
            iter1++;
        }
        else
        {
            result.terms[iter2->first] = iter2->second;
            iter2++;
        }
    }

    // Copy remaining terms from the first polynomial
    while (iter1 != sorted_terms1.end())
    {
        result.terms[iter1->first] = iter1->second;
        iter1++;
    }
    // Copy remaining terms from the second polynomial
    while (iter2 != sorted_terms2.end())
    {
        result.terms[iter2->first] = iter2->second;
        iter2++;
    }

    return result;
}

polynomial polynomial::operator+(int constant) const
{
    polynomial result(*this);

    // If a term with power 0 exists, add the constant to its coefficient
    result.terms[0] += constant;

    return result;
}

polynomial operator+(int constant, const polynomial &poly)
{
    polynomial result(poly);

    // If a term with power 0 exists, add the constant to its coefficient
    result.terms[0] += constant;

    return result;
}

// * operator overload
polynomial polynomial::operator*(const polynomial &other) const
{
    polynomial result;

    // Function to compute a subset of the terms
    auto computeSubset = [&](auto start, auto end) {
        for (auto it = start; it != end; ++it) {
            for (auto &term : other.terms) {
                result.terms[it->first + term.first] += it->second * term.second;
            }
        }
    };

    // If the number of terms is small, don't use threads
    if (terms.size() < 100 || other.terms.size() < 100) {
        computeSubset(terms.begin(), terms.end());
    } else {
        // Mutex to protect the critical section
        std::mutex resultMutex;

        // Number of threads to use (adjust as needed)
        const size_t numThreads = 4;

        // Split the work among threads
        std::vector<std::thread> threads;
        size_t termsPerThread = terms.size() / numThreads;
        auto it = terms.begin();

        for (size_t i = 0; i < numThreads - 1; ++i) {
            auto start = it;
            std::advance(it, termsPerThread);
            auto end = it;
            threads.emplace_back(computeSubset, start, end);
        }

        // Last thread takes care of any remaining terms
        auto start = it;
        auto end = terms.end();
        threads.emplace_back(computeSubset, start, end);

        // Wait for all threads to finish
        for (auto &thread : threads) {
            thread.join();
        }
    }

    return result;
}





polynomial polynomial::operator*(int constant) const
{
    polynomial result;

    for (const auto &term : terms)
    {
        // Multiply the coefficient by the constant
        result.terms[term.first] = term.second * constant;
    }

    return result;
}

polynomial operator*(int constant, const polynomial &poly)
{
    polynomial result;

    for (const auto &term : poly.terms)
    {
        // Multiply the coefficient by the constant
        result.terms[term.first] = term.second * constant;
    }

    return result;
}


// % operator overload
polynomial polynomial::operator%(const polynomial &other) const
{
    polynomial remainder;
    polynomial dividend(*this);
    polynomial divisor(other);

    dividend.canonical_form();
    divisor.canonical_form();

    // Check if the divisor is zero
    if (divisor.terms.size() == 1 && divisor.terms.begin()->second == 0)
    {
        return remainder;
    }

    // Perform polynomial long division
    while (dividend.find_degree_of() >= divisor.find_degree_of())
    {
        // Get the leading terms of the dividend and divisor
        auto leading_term_dividend = dividend.canonical_form().begin();
        auto leading_term_divisor = divisor.canonical_form().begin();

        // get the quotient term
        power quotient_power = leading_term_dividend->first - leading_term_divisor->first;
        coeff quotient_coeff = leading_term_dividend->second / leading_term_divisor->second;

        // Subtract from the dividend to get the remainder
        std::map<power, coeff> term_to_subtract_map = {{quotient_power, quotient_coeff}};
        polynomial term_to_subtract(term_to_subtract_map.begin(), term_to_subtract_map.end());
        dividend = dividend - term_to_subtract;

        // Check if the degree of remaining terms in the dividend is not decreasing
        if (dividend.find_degree_of() >= leading_term_dividend->first)
        {
            break;
        }
    }

    remainder = dividend;
    remainder.canonical_form();
    return remainder;
}

polynomial polynomial::operator-(const polynomial &other) const
{
    polynomial result;
    std::map<power, coeff> sorted_terms1 = canonical_form();
    std::map<power, coeff> sorted_terms2 = other.canonical_form();

    auto iter1 = sorted_terms1.begin();
    auto iter2 = sorted_terms2.begin();

    // Loop through both polynomials
    while (iter1 != sorted_terms1.end() && iter2 != sorted_terms2.end())
    {
        // If both terms have the same power
        if (iter1->first == iter2->first)
        {
            result.terms[iter1->first] = iter1->second - iter2->second;
            iter1++;
            iter2++;
        }
        // If the power of the first term is greater than the second, move the first one into result directly
        else if (iter1->first > iter2->first)
        {
            result.terms[iter1->first] = iter1->second;
            iter1++;
        }
        else
        {
            // Subtract the second term
            result.terms[iter2->first] = -iter2->second;
            iter2++;
        }
    }

    // Copy remaining terms from the first polynomial
    while (iter1 != sorted_terms1.end())
    {
        result.terms[iter1->first] = iter1->second;
        iter1++;
    }
    // Copy remaining terms from the second polynomial with negation
    while (iter2 != sorted_terms2.end())
    {
        result.terms[iter2->first] = -iter2->second;
        iter2++;
    }

    return result;
}

polynomial polynomial::operator-(int constant) const
{
    // Copy the caller
    polynomial result(*this);

    // If a term with power 0 exists, subtract the constant from its coefficient
    result.terms[0] -= constant;

    return result;
}

polynomial operator-(int constant, const polynomial &poly)
{
    // Copy poly
    polynomial result(poly);

    // If a term with power 0 exists, subtract the constant from its coefficient
    result.terms[0] = constant - result.terms[0];

    return result;
}
