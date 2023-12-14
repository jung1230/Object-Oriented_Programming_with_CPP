#include "poly.h"
#include <iostream>
#include <vector>
#include <utility>
#include <cstddef>
#include <algorithm>
#include <thread>
#include <map>
#include <iterator>
#include<fstream>
#include<sstream>

const size_t num_of_threads = 8; // Number of threads
/**
 * @brief Construct a new polynomial object that is the number 0 (ie. 0x^0)
 *
 */
polynomial::polynomial() : terms({{0, 0}})
{
    // Alan
}

/**
 * @brief Construct a new polynomial object from an iterator to pairs of <power,coeff>
 *
 * @tparam Iter
 *  An iterator that points to a std::pair<power, coeff>
 * @param begin
 *  The start of the container to copy elements from
 * @param end
 *  The end of the container to copy elements from
 */
// template <typename Iter>
// polynomial::polynomial(Iter begin, Iter end){
//     // Alan
//     // copy each item by using the iterator
//     for (Iter it = begin; it != end; it++) {
//         terms.push_back(*it);
//     }

// }

/**
 * @brief Construct a new polynomial object from an existing polynomial object
 *
 * @param other
 *  The polynomial to copy
 */
polynomial::polynomial(const polynomial &other)
{
    // Alan
    // go through each terms and copy it. If i do not add const at the begining, error will occur
    for (const std::pair<power, coeff> term : other.terms)
    {
        // result iter is a pair that contain iter and a bool (succeed or failed = 1 or 0)
        auto result_iter = this->terms.emplace(term);

        // This part checks if the insertion was successful. If the term already exists in the terms container, it updates the coefficient of the existing term to match the coefficient of the term being copied.
        if (!result_iter.second)
        {
            result_iter.first->second = term.second;
        }
        // this->terms.insert(term);
    }
}

/**
 * @brief Prints the polynomial.
 *
 * Only used for debugging, isn't graded.
 *
 */
void polynomial::print() const
{
    // Alan
    std::vector<std::pair<power, coeff>> sorted_terms = canonical_form();
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

/**
 * @brief Turn the current polynomial instance into a deep copy of another
 * polynomial
 *
 * @param other
 * The polynomial to copy
 * @return
 * A reference to the copied polynomial
 */
polynomial &polynomial::operator=(const polynomial &other)
{
    // self assignment
    if (this == &other)
    {
        return *this;
    }

    // clear terms of this
    this->terms.clear();

    // go through each term and copy it
    for (const std::pair<power, coeff> term : other.terms)
    {
        auto result_iter = this->terms.emplace(term);
        // If the term already exists, update its coefficient
        if (!result_iter.second)
        {
            result_iter.first->second = term.second;
        }
        // this->terms.insert(term);
    }

    return *this;
}

/**
 * @brief Returns the degree of the polynomial
 *
 * @return size_t
 *  The degree of the polynomial
 */
size_t polynomial::find_degree_of() const
{
    return canonical_form().at(0).first;
}

/**
 * @brief Returns a vector that contains the polynomial is canonical form. This
 *        means that the power at index 0 is the largest power in the polynomial,
 *        the power at index 1 is the second largest power, etc.
 *
 *        ie. x^2 + 7x^4 + 1 would be returned as [(4,7),(2,1),(0,1)]
 *
 *        Note: any terms that have a coefficient of zero aren't returned in
 *        in the canonical form, with one exception.
 *        See the above example (there's no x^3 term, so
 *        there's no entry in the vector for x^3)
 *
 *        The only exception to this is the polynomial 0. If your polynomial is
 *        just the constant 0 then you would return a single entry of [(0,0)]
 *
 *        ie. y = 0 would be returned as [(0,0)]
 *
 * @return std::vector<std::pair<power, coeff>>
 *  A vector of pairs representing the canonical form of the polynomial
 */
std::vector<std::pair<power, coeff>> polynomial::canonical_form() const
{
    std::vector<std::pair<power, coeff>> sorted_terms;
    for (const auto &pairr : this->terms)
    {
        if (pairr.second != 0)
            sorted_terms.push_back(pairr);
        else
            continue;
    }
    if (sorted_terms.size() == 0)
    {
        sorted_terms.push_back({0, 0});
    }

    return sorted_terms;
}

// + operator overload
// Alan
polynomial polynomial::operator+(const polynomial &other) const
{
    polynomial result;
    //std::cout << "Inside +" << std::endl;
    //result.print();
    // std::vector<std::pair<power, coeff>> sorted_terms1 = canonical_form();
    // std::vector<std::pair<power, coeff>> sorted_terms2 = other.canonical_form();

    auto iter1 = terms.begin();
    auto iter2 = other.terms.begin();

    // loop through both polynomial
    while (iter1 != terms.end() && iter2 != other.terms.end())
    {
        // if both term have same power
        if (iter1->first == iter2->first)
        {
            if(iter1->second + iter2->second != 0){
                auto result_iter = result.terms.emplace(iter1->first, iter1->second + iter2->second);
                // If the term already exists, update its coefficient
                if (!result_iter.second)
                {
                    result_iter.first->second = iter1->second + iter2->second;
                }
                // if(iter2->first == 0){ // Map cannot insert the key value pair if there is already the key in the map
                //     result.terms.erase(0);
                // }
                // result.terms.insert({iter1->first, iter1->second + iter2->second});
            }
            iter1++;
            iter2++;
        }
        // if first term is bigger than second, move the first one into result directly
        else if (iter1->first > iter2->first)
        {
            result.terms.insert(*iter1);
            iter1++;
        }
        else
        {
            result.terms.insert(*iter2);
            iter2++;
        }
    }

    // Copy remaining terms for terms1
    while (iter1 != terms.end())
    {
        auto result_iter = result.terms.emplace(*iter1);
        // If the term already exists, update its coefficient
        if (!result_iter.second)
        {
            result_iter.first->second = iter1->second;
        }
        // if(iter1->first == 0){
        //     result.terms.erase(0);
        //     result.terms.insert(*iter1);
        // }
        // else
        //     result.terms.insert(*iter1);
        iter1++;
    }
    // Copy remaining terms for terms2
    while (iter2 != other.terms.end())
    {
        auto result_iter = result.terms.emplace(*iter2);
        // If the term already exists, update its coefficient
        if (!result_iter.second)
        {
            result_iter.first->second = iter2->second;
        }
        // if(iter2->first == 0){
        //     result.terms.erase(0);
        //     result.terms.insert(*iter2);
        // }
        // else
        //     result.terms.insert(*iter2);
        iter2++;
    }
    if(result.terms.empty())
        result.terms.insert({0,0});
    return result;
}
polynomial polynomial::operator+(int constant) const
{
    // copy caller
    // std::cout << "Inside poly + constant" << std::endl;
    // print();
    polynomial result(*this);
    // result.print();
    // Check if there's already a term with power 0
    auto it = result.terms.end();
    it--;
    // std::cout << it->first << " " << it->second << std::endl;
    // If a term with power 0 exists, add the constant to its coefficient
    if (it->first == 0)
    {
        it->second += constant;
        if(it->second == 0)
            result.terms.erase(it->first);
    }
    // No term with power 0 exists, add a new term for the constant
    else
    {
        if(constant != 0)
            result.terms.insert({0, constant});
    }
    if(result.terms.empty())
        result.terms.insert({0,0});
    return result;
}
// Note: the friend function declaration is done outside the class scope, and it does not have the polynomial:: prefix. This is because it is not a member function of the polynomial class.
polynomial operator+(int constant, const polynomial &poly)
{
    // copy poly
    polynomial result(poly);

    // Check if there's already a term with power 0
    auto it = result.terms.end();
    it--;
    // If a term with power 0 exists, add the constant to its coefficient
    if (it->first == 0)
    {
        it->second += constant;
        if(it->second == 0)
            result.terms.erase(it->first);
    }
    // No term with power 0 exists, add a new term for the constant
    else
    {
        if(constant != 0)
            result.terms.insert({0, constant});
    }
    if(result.terms.empty())
        result.terms.insert({0,0});
    return result;
}

// * operator overload
polynomial polynomial::operator*(const polynomial &other) const
{    
    polynomial result;
    // Check the sizes of both polynomials
    size_t size1 = terms.size();
    size_t size2 = other.terms.size();


// Use multiple threads for the larger polynomial
    if (size1 >= 10 && size2 >= 10)
    {
        //std::cout<<"+++++++++++++++++++++++++++++++++++++++++++thread++++++++++++++++++++++++++++++++++++++++++++++++++++"<<std::endl;

        std::vector<std::thread> threads;
        std::vector<polynomial> results;
        std::vector<polynomial> multipliers;
        //std::vector<int> counts;

        // Lamda function for thread to do the multiply
        auto thread_multiply = [this, &results, &other, &multipliers](size_t thread_ID, size_t total_thread_num)
        {
            auto it = this->terms.begin();

            // advances an iterator by a specified number of steps
            std::advance(it, thread_ID);
            for (size_t i = thread_ID; i < terms.size(); i = i + total_thread_num)// Divide the workload
            { 
                //counts[thread_ID] = 1;
                if(i != thread_ID)
                    std::advance(it, total_thread_num);
                for (const auto &term2 : multipliers[thread_ID].terms)
                {
                    auto result_iter = results[thread_ID].terms.emplace(it->first + term2.first, it->second * term2.second);

                    // If the term already exists, update its coefficient
                    if (!result_iter.second)
                    {
                        result_iter.first->second += it->second * term2.second;
                    }
                }
            }
        };
        for (size_t i = 0; i < num_of_threads; i++)
        {
            results.push_back(polynomial());
            multipliers.push_back(other);
        }
        // std::cout << "Here I am" << std::endl;
        // Launch the threads
        for (size_t i = 0; i < num_of_threads; i++)
        {
            threads.push_back(std::thread(thread_multiply, i, num_of_threads));
        }

        // Join the threads
        for (size_t i = 0; i < num_of_threads; i++)
        {
            threads[i].join();
        }
        // std::cout << "MUL done" << std::endl;
        for (auto &mul_term : results)
        {
            //mul_term.print();
            result = result + mul_term;
        }
    }
// Use a single thread for both polynomials
    else
    {
        //std::cout<<"------------------------------------single-------------------------------------"<<std::endl;
        for (const auto term1 : this->terms)
        {
            for (const auto term2 : other.terms)
            {
                // Multiply the coefficients and add the powers
                auto result_iter = result.terms.emplace(term1.first + term2.first, term1.second * term2.second);

                // If the term already exists, update its coefficient
                if (!result_iter.second)
                {
                    result_iter.first->second += term1.second * term2.second;
                }
            }
        }
    }

    return result;
  
}
polynomial polynomial::operator*(int constant) const
{
    polynomial result;
    std::vector<std::thread> threads;
    std::vector<polynomial> results;
    // Lamda function for thread to do the multiply
    auto thread_multiply = [this, &results, &constant](size_t thread_ID, size_t total_thread_num)
    {
        auto it = this->terms.begin();
        std::advance(it, thread_ID);
        for (size_t i = thread_ID; i < terms.size(); i = i + total_thread_num)
        { // Divide the workload
            if(i != thread_ID)
                std::advance(it, total_thread_num);
            // if(it->first == 0)
            //     results[thread_ID].terms.erase(it->first);
            // results[thread_ID].terms.insert({it->first, it->second * constant});
            auto result_iter = results[thread_ID].terms.emplace(it->first, it->second * constant);

            // If the term already exists, update its coefficient
            if (!result_iter.second)
            {
                result_iter.first->second += it->second * constant;
            }
        }
    };
    for (size_t i = 0; i < num_of_threads; i++)
    {
        results.push_back(polynomial());
    }
    // Launch the threads
    for (size_t i = 0; i < num_of_threads; i++)
    {
        threads.push_back(std::thread(thread_multiply, i, num_of_threads));
    }

    // Join the threads
    for (size_t i = 0; i < num_of_threads; i++)
    {
        threads[i].join();
    }

    for (auto &mul_term : results)
    {
        result = result + mul_term;
    }

    return result;
    // for (const std::pair<power, coeff> &term : this->terms)
    // {
    //     // Multiply the coefficient by the constant
    //     result.terms.push_back({term.first, term.second * constant});
    // }
    // return result;
}
polynomial operator*(int constant, const polynomial &poly)
{
    // std::cout << "Inside *" << std::endl;
    polynomial result;
    std::vector<std::thread> threads;
    std::vector<polynomial> results;
    // Lamda function for thread to do the multiply
    auto thread_multiply = [poly, &results, constant](size_t thread_ID, size_t total_thread_num)
    {
        auto it = poly.terms.begin();
        std::advance(it, thread_ID);
        for (size_t i = thread_ID; i < poly.terms.size(); i = i + total_thread_num)
        { // Divide the workload
            if(i != thread_ID)
                std::advance(it, total_thread_num);
            // if(it->first == 0)
            //     results[thread_ID].terms.erase(it->first);
            // results[thread_ID].terms.insert({it->first, it->second * constant});
            auto result_iter = results[thread_ID].terms.emplace(it->first, it->second * constant);

            // If the term already exists, update its coefficient
            if (!result_iter.second)
            {
                result_iter.first->second += it->second * constant;
            }
        }
    };
    for (size_t i = 0; i < num_of_threads; i++)
    {
        results.push_back(polynomial());
    }
    // Launch the threads
    for (size_t i = 0; i < num_of_threads; i++)
    {
        threads.push_back(std::thread(thread_multiply, i, num_of_threads));
    }

    // Join the threads
    for (size_t i = 0; i < num_of_threads; i++)
    {
        threads[i].join();
    }

    for (auto &mul_term : results)
    {
        result = result + mul_term;
    }
    // result.print();
    return result;
    // for (const std::pair<power, coeff> &term : poly.terms)
    // {
    //     // Multiply the coefficient by the constant
    //     result.terms.push_back({term.first, term.second * constant});
    // }
    // return result;
}

// % operator overload
polynomial polynomial::operator%(const polynomial &other) const
{
    polynomial remainder;
    // std::cout << "Inside Mod" << std::endl;
    polynomial dividend(this->terms.begin(), this->terms.end());
    polynomial divisor(other.terms.begin(), other.terms.end());
    // dividend.canonical_form();
    // divisor.canonical_form();
    auto last = divisor.terms.end();
    last--;
    // Check if the divisor is zero
    if (divisor.terms.size() == 1 && last->second == 0)
    {
        return remainder;
    }

    // Perform polynomial long division
    while (dividend.find_degree_of() >= divisor.find_degree_of())
    {
        // Get the leading terms of the dividend and divisor
        auto leading_term_dividend = *(dividend.terms.begin());
        auto leading_term_divisor = *(divisor.terms.begin());

        // get the quotient term
        power quotient_power = leading_term_dividend.first - leading_term_divisor.first;
        coeff quotient_coeff = leading_term_dividend.second / leading_term_divisor.second;

        // Subtract from the dividend to get the remainder
        std::vector<std::pair<power, coeff>> term_to_subtract_vector = {{quotient_power, quotient_coeff}};
        polynomial term_to_subtract = divisor * polynomial(term_to_subtract_vector.begin(), term_to_subtract_vector.end());
        dividend = dividend - term_to_subtract; // this might be the issue
        //dividend.print();
        // Check if the degree of remaining terms in the dividend is not decreasing
        if (dividend.find_degree_of() >= leading_term_dividend.first)
        {
            break;
        }

    }

    remainder = dividend;
    return remainder;
}

polynomial polynomial::operator-(const polynomial &other) const
{

    polynomial result;

    auto iter1 = this->terms.begin();
    auto iter2 = other.terms.begin();

    // Loop through both polynomials
    while (iter1 != this->terms.end() && iter2 != other.terms.end())
    {
        // If both terms have the same power
        if (iter1->first == iter2->first)
        {
            if(iter1->second - iter2->second != 0){
                auto result_iter = result.terms.emplace(iter1->first, iter1->second - iter2->second);
                // If the term already exists, update its coefficient
                if (!result_iter.second)
                {
                    result_iter.first->second = iter1->second - iter2->second;
                }
                // if(iter2->first == 0)
                //     result.terms.erase(0);
                // result.terms.insert({iter1->first, iter1->second - iter2->second});
            }
            iter1++;
            iter2++;
        }
        // if first term is bigger than second, move the first one into result directly
        else if (iter1->first > iter2->first)
        {
            result.terms.insert(*iter1);
            iter1++;
        }
        else
        {
            // Subtract the second term
            result.terms.insert({iter2->first, -iter2->second});
            iter2++;
        }
    }

    // Copy remaining terms from the first polynomial
    while (iter1 != this->terms.end())
    {
        auto result_iter = result.terms.emplace(*iter1);
        // If the term already exists, update its coefficient
        if (!result_iter.second)
        {
            result_iter.first->second = iter1->second;
        }
        // if(iter1->first == 0)
        //     result.terms.erase(0);
        // result.terms.insert(*iter1);
        iter1++;
    }
    // Copy remaining terms from the second polynomial with negation
    while (iter2 != other.terms.end())
    {
        auto result_iter = result.terms.emplace(*iter2);
        // If the term already exists, update its coefficient
        if (!result_iter.second)
        {
            result_iter.first->second = -iter2->second;
        }
        // if(iter2->first == 0)
        //     result.terms.erase(0);
        // result.terms.insert(*iter2);
        iter2++;
    }
    if(result.terms.empty())
        result.terms.insert({0,0});
    return result;
}


polynomial polynomial::operator-(int constant) const
{
    // Copy the caller
    polynomial result(*this);

    // Check if there's already a term with power 0
    auto it = result.terms.end();
    it--;
    // If a term with power 0 exists, subtract the constant from its coefficient
    if (it->first == 0)
    {
        if(it->second - constant !=0)
            it->second -= constant;
        else
            result.terms.erase(it->first);
    }
    else
    {
        // No term with power 0 exists, add a new term with the negation of the constant
        if(constant != 0)
            result.terms.insert({0, -constant});
    }
    if(result.terms.empty())
        result.terms.insert({0,0});
    return result;
}


polynomial operator-(int constant, const polynomial &poly)
{
    // copy poly
    polynomial result(poly);

    // Negate all coefficients
    for (auto &term : result.terms)
    {
        term.second = -term.second;
    }
    // Check if there's already a term with power 0
    auto it = result.terms.end();
    it--;
    // If a term with power 0 exists, subtract the constant from its coefficient
    if (it->first == 0)
    {
        if(constant + it->second != 0)
            it->second = constant + it->second;
        else
            result.terms.erase(it->first);
    }
    // No term with power 0 exists, add a new term with the constant
    else
    {
        if(constant != 0)
            result.terms.insert({0, constant});
    }
    if(result.terms.empty())
        result.terms.insert({0,0});
    return result;
}


void polynomial::addTerm(power expo, coeff num){
    //std::cout << expo << " " << num << std::endl;
    if(terms.find(expo) == terms.end()){ // Not found
        terms.insert({expo, num});
    }
    else{ // Found
        terms.erase(expo);
        terms.insert({expo, num});
    }
}

void polynomial::outputprint(std::ostream& os) const{
    auto termm = canonical_form();
    auto it = termm.end();
    it--;
    while(it != termm.begin()){
        os << it->second << "x^" << it->first << std::endl;
        it--;
    }
    os << it->second << "x^" << it->first << std::endl;
    os << ";" << std::endl;
}