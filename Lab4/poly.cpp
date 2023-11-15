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
    // go through each terms and copy it. If i do not add const at the begining, error will occur
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
        std::cout << "empty";
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
polynomial &polynomial::operator=(const polynomial &other){
    // self assignment
    if (this == &other) {
        return *this;
    }

    // clear terms of this
    this->terms.clear();

    // go through each term and copy it
    for (const std::pair<power, coeff> &term : other.terms) {
        this->terms.push_back(term);
    }

    return *this;
}



/**
 * @brief Returns the degree of the polynomial
 *
 * @return size_t
 *  The degree of the polynomial
 */
size_t polynomial::find_degree_of() const{
    // Alan
    std::vector<std::pair<power, coeff>> termss = canonical_form();

    if (termss.empty()) {
        return 0;
    } 
    else {
        return termss.begin()->first;
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

    
    // Remove terms with coefficient 0. remove_if is used to move elements with a coefficient of 0 to the end of the vector, and erase is used to remove elements from the iterator returned by std::remove_if to the end of the vector.
    //sorted_terms.erase(std::remove_if(sorted_terms.begin(), sorted_terms.end(),[](const auto &term) { return term.second == 0; }),sorted_terms.end());


    std::vector<std::pair<power, coeff>> combined_terms;

    for (const auto &term : sorted_terms) {
        // If the term's power does not match the last term's power,  or the combined_terms vector is empty, add the term
        if (term.second == 0){
            continue;
        }
        else if (combined_terms.empty() || term.first != combined_terms.back().first) {
            combined_terms.push_back(term);
        } 
        // If the powers are same, sum coefficients
        else {  
            if (combined_terms.back().second + term.second != 0){
                combined_terms.back().second += term.second;
            }
            else
                combined_terms.pop_back();
            
        }
    }
    
    if(combined_terms.empty()){
        std::vector<std::pair<power, coeff>> zero;
        zero = {{0,0}};
        return zero;
    }
         
    return combined_terms;
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
    result.canonical_form();

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
    result.canonical_form();

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
    result.canonical_form();

    return result;
}

// * operator overload
polynomial polynomial::operator*(const polynomial& other) const{
    polynomial result;

    for (const std::pair<power, coeff>& term1 : this->terms) {
        for (const std::pair<power, coeff>& term2 : other.terms) {
            // Multiply the coefficients and add the powers
            result.terms.push_back({term1.first + term2.first, term1.second * term2.second});
        }
    }

    result.canonical_form();
    return result;
}
polynomial polynomial::operator*(int constant) const{
    polynomial result;

    for (const std::pair<power, coeff>& term : this->terms) {
        // Multiply the coefficient by the constant
        result.terms.push_back({term.first, term.second * constant});
    }
    result.canonical_form();
    return result;
}
polynomial operator*(int constant, const polynomial& poly){
    polynomial result;

    for (const std::pair<power, coeff>& term : poly.terms) {
        // Multiply the coefficient by the constant
        result.terms.push_back({term.first, term.second * constant});
    }
    result.canonical_form();
    return result;
}


// % operator overload
polynomial polynomial::operator%(const polynomial& other) const{

    if (other.terms.size() == 1 && other.terms[0].second == 0) {
        return *this;  
    }

    // get remainder by using geting quotient
    polynomial quotient = *this / other;  
    polynomial product = other * quotient; 
    polynomial remainder = *this - product; 
    remainder.canonical_form();  
    return remainder;

}




polynomial polynomial::operator-(const polynomial& other) const{
    
    polynomial result;
    std::vector<std::pair<power, coeff>> sorted_terms1 = canonical_form();
    std::vector<std::pair<power, coeff>> sorted_terms2 = other.canonical_form();

    auto iter1 = sorted_terms1.begin();
    auto iter2 = sorted_terms2.begin();

    // Loop through both polynomials
    while (iter1 != sorted_terms1.end() && iter2 != sorted_terms2.end()) {
        // If both terms have the same power
        if (iter1->first == iter2->first) {
            result.terms.push_back({iter1->first, iter1->second - iter2->second});
            iter1++;
            iter2++;
        }
        // if first term is bigger than second, move the first one into result directly
        else if (iter1->first > iter2->first) {
            result.terms.push_back(*iter1);
            iter1++;
        } else {
            // Subtract the second term
            result.terms.push_back({iter2->first, -iter2->second}); 
            iter2++;
        }
    }

    // Copy remaining terms from the first polynomial
    while (iter1 != sorted_terms1.end()) {
        result.terms.push_back(*iter1);
        iter1++;
    }
    // Copy remaining terms from the second polynomial with negation
    while (iter2 != sorted_terms2.end()) {
        result.terms.push_back({iter2->first, -iter2->second});
        iter2++;
    }
    result.canonical_form();

    return result;
}
polynomial polynomial::operator-(int constant) const{
    // Copy the caller
    polynomial result(*this);

    // Check if there's already a term with power 0
    auto it = std::find_if(result.terms.begin(), result.terms.end(), [](const std::pair<power, coeff>& term) {return term.first == 0;});

    // If a term with power 0 exists, subtract the constant from its coefficient
    if (it != result.terms.end()) {
        it->second -= constant;
    } else {
        // No term with power 0 exists, add a new term with the negation of the constant
        result.terms.push_back({0, -constant});
    }
    result.canonical_form();

    return result;
}
polynomial operator-(int constant, const polynomial& poly){
    // copy poly
    polynomial result(poly);

    // Check if there's already a term with power 0
    auto it = std::find_if(result.terms.begin(), result.terms.end(), [](const std::pair<power, coeff>& term) { return term.first == 0; });

    // If a term with power 0 exists, subtract the constant from its coefficient
    if (it != result.terms.end()) {
        it->second = constant - it->second;
    }
    // No term with power 0 exists, add a new term with the constant
    else {
        result.terms.push_back({0, constant});
    }
    result.canonical_form();

    return result;
}


// / operator overload
polynomial polynomial::operator/(const polynomial& other) const {
    polynomial quotient;
    polynomial dividend(*this);
    polynomial divisor(other);

    // Canonicalize the polynomials
    dividend.canonical_form();
    divisor.canonical_form();

    // Check if the divisor is zero
    if (divisor.terms.size() == 1 && divisor.terms[0].second == 0) {
        return quotient;  
    }

// Counter for consecutive same degrees, this is use for avoiding infinite while loop
    size_t consecutive_same_degree_count = 0;  
    const size_t max_consecutive_same_degree = 3;

    // Perform polynomial long division
    while (dividend.find_degree_of() >= divisor.find_degree_of()) {
        // Get the leading terms of the dividend and divisor
        auto leading_term_dividend = dividend.canonical_form().front();
        auto leading_term_divisor = divisor.canonical_form().front();

        // get the quotient term
        power quotient_power = leading_term_dividend.first - leading_term_divisor.first;
        coeff quotient_coeff = leading_term_dividend.second / leading_term_divisor.second;

        // Add the quotient term to the result
        std::vector<std::pair<power, coeff>> quotient_vector = {{quotient_power, quotient_coeff}};
        quotient = quotient + polynomial(quotient_vector.begin(), quotient_vector.end());

        // dividend - (divisor * quotient term)
        std::vector<std::pair<power, coeff>> term_to_subtract_vector = {{quotient_power, quotient_coeff}};
        polynomial term_to_subtract = divisor * polynomial(term_to_subtract_vector.begin(), term_to_subtract_vector.end());

        dividend = dividend - term_to_subtract;
        

        // Check if the degree of remaining terms in the dividend is not decreasing
        if (dividend.find_degree_of() >= leading_term_dividend.first) {
            consecutive_same_degree_count++;
        } else {
            consecutive_same_degree_count = 0; 
        }
        // Check if the consecutive same degree count exceeds the threshold , avoid infinite loop
        if (consecutive_same_degree_count >= max_consecutive_same_degree) {
            break;  
        }
    }

    quotient.canonical_form();
    return quotient;
}


polynomial polynomial::operator/(int constant) const {
    // Check if the constant is zero
    if (constant == 0) {
        return polynomial();  
    }

    // Copy the caller
    polynomial result(*this);

    // Divide each term's coefficient by the constant
    for (auto& term : result.terms) {
        term.second /= constant;
    }

    result.canonical_form();
    return result;
}

// Friend function for int / polynomial
polynomial operator/(int constant, const polynomial& poly) {
    // Check if the polynomial is zero
    if (poly.terms.size() == 1 && poly.terms[0].second == 0) {
        return polynomial();  
    }

    polynomial result;

    if (poly.terms.size() == 1 && poly.terms[0].first == 0) {
        result.terms.push_back({0, constant / poly.terms[0].second});
    }
    else{
        result.terms.push_back({0,0});
    }    

    return result;
}