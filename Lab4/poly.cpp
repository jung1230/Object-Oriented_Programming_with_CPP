#include "poly.h"
#include <iostream>
#include <vector>
#include <utility>
#include <cstddef>
#include <algorithm>

/**
 * @brief Construct a new polynomial object that is the number 0 (ie. 0x^0)
 *
 */
polynomial::polynomial() : terms({{0,0}}){
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
polynomial::polynomial(const polynomial &other){
    // Alan
    // iterate through each terms and copy it. If i do not add const at the begining, error will occur
    for (const std::pair<power, coeff> &term : other.terms) {
        this -> terms.push_back(term);
    }
}

/**
 * @brief Prints the polynomial.
 *
 * Only used for debugging, isn't graded.
 *
 */
void polynomial::print() const{
    // Alan
    std::vector<std::pair<power, coeff>> sorted_terms = canonical_form();
    if (sorted_terms.empty()) {
        std::cout << "0";
    } 
    else {
        auto iter = sorted_terms.begin();  
        std::cout << iter -> second << "(x^" << iter -> first << ")";

        // Print the rest of the terms
        for (iter++; iter != sorted_terms.end(); iter++) {
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
// polynomial &polynomial::operator=(const polynomial &other){
//     // Peter

// }



/**
 * @brief Returns the degree of the polynomial
 *
 * @return size_t
 *  The degree of the polynomial
 */
size_t polynomial::find_degree_of(){
    // Alan
    std::vector<std::pair<power, coeff>> sorted_terms = canonical_form();

    if (sorted_terms.empty()) {
        return 0;
    } 
    else {
        return sorted_terms.begin()->first;
    }

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
std::vector<std::pair<power, coeff>> polynomial::canonical_form() const{
    // Alan    
    // copy all the terms
    std::vector<std::pair<power, coeff>> sorted_terms = terms;
    // sort it by using sort in algrithm
    std::sort(sorted_terms.begin(), sorted_terms.end(), std::greater<>());

    // Remove terms with coefficient 0
    sorted_terms.erase(std::remove_if(sorted_terms.begin(), sorted_terms.end(),[](const auto &term) { return term.second == 0; }),sorted_terms.end());

    return sorted_terms;
}


// + operator overload
// Alan
polynomial polynomial::operator+(const polynomial& other) const{
    polynomial result;
    std::vector<std::pair<power, coeff>> sorted_terms1 = canonical_form();
    std::vector<std::pair<power, coeff>> sorted_terms2 = other.canonical_form();


    auto iter1 = sorted_terms1.begin();
    auto iter2 = sorted_terms2.begin();

    // loop throug both polynomial
    while (iter1 != sorted_terms1.end() && iter2 != sorted_terms2.end()){
        // if both term have same power
        if (iter1->first == iter2->first){
            result.terms.push_back({iter1->first, iter1->second + iter2->second});
            iter1++;
            iter2++;
        }
        // if first term is bigger than second, move the first one into result directly
        else if (iter1->first > iter2->first){
            result.terms.push_back(*iter1);
            iter1++;
        }
        else{
            result.terms.push_back(*iter2);
            iter2++;
        }
    }

    // Copy remaining terms for terms1
    while (iter1 != sorted_terms1.end()){
        result.terms.push_back(*iter1);
        iter1++;
    }
    // Copy remaining terms for terms2
    while (iter2 != sorted_terms2.end()){
        result.terms.push_back(*iter2);
        iter2++;
    }

    return result;
}
polynomial polynomial::operator+(int constant) const{
    // copy caller
    polynomial result(*this); 

    // Check if there's already a term with power 0
    auto it = std::find_if(result.terms.begin(), result.terms.end(), [](const std::pair<power, coeff>& term) {return term.first == 0;});

    // If a term with power 0 exists, add the constant to its coefficient
    if (it != result.terms.end()){
        it->second += constant;
    }
    // No term with power 0 exists, add a new term for the constant
    else{
        result.terms.push_back({0, constant});
    }

    return result;
}
        //Note: the friend function declaration is done outside the class scope, and it does not have the polynomial:: prefix. This is because it is not a member function of the polynomial class.
polynomial operator+(int constant, const polynomial& poly){
    // copy poly
    polynomial result(poly); 

    // Check if there's already a term with power 0
    auto it = std::find_if(result.terms.begin(), result.terms.end(), [](const std::pair<power, coeff>& term) {return term.first == 0;});

    // If a term with power 0 exists, add the constant to its coefficient
    if (it != result.terms.end()){
        it->second += constant;
    }
    // No term with power 0 exists, add a new term for the constant
    else{
        result.terms.push_back({0, constant});
    }

    return result;
}

// // * operator overload
// // Peter
// polynomial polynomial::operator*(const polynomial& other) const{

// }
// polynomial polynomial::operator*(int constant) const{

// }
// polynomial operator*(int constant, const polynomial& poly){

// }

// // % operator overload
// // Peter
// polynomial polynomial::operator%(const polynomial& other) const{

// }
