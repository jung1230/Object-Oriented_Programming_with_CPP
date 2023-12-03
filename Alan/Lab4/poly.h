#ifndef POLY_H
#define POLY_H

#include <map>
#include <utility>
#include <cstddef>

using power = size_t;
using coeff = int;

class polynomial
{
public:
    /**
     * @brief Construct a new polynomial object that is the number 0 (ie. 0x^0)
     *
     */
    polynomial();

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
    template <typename Iter>
    polynomial(Iter begin, Iter end){
        // Alan
        // copy each item by using the iterator
        for (Iter it = begin; it != end; it++)
        {
            terms.insert(*it);
        }
    }

    /**
     * @brief Construct a new polynomial object from an existing polynomial object
     *
     * @param other
     *  The polynomial to copy
     */
    polynomial(const polynomial &other);

    /**
     * @brief Prints the polynomial.
     *
     * Only used for debugging, isn't graded.
     *
     */
    void print() const;

    /**
     * @brief Turn the current polynomial instance into a deep copy of another
     * polynomial
     *
     * @param other
     * The polynomial to copy
     * @return
     * A reference to the copied polynomial
     */
    polynomial &operator=(const polynomial &other);

    /**
     * @brief Returns the degree of the polynomial
     *
     * @return size_t
     *  The degree of the polynomial
     */
    size_t find_degree_of() const;

    /**
     * @brief Returns a map that contains the polynomial in canonical form. This
     *        means that the power is the key and the coefficient is the value.
     *
     *        ie. x^2 + 7x^4 + 1 would be returned as {4: 7, 2: 1, 0: 1}
     *
     *        Note: any terms that have a coefficient of zero aren't returned in
     *        in the canonical form, with one exception.
     *        See the above example (there's no x^3 term, so
     *        there's no entry in the map for x^3)
     *
     *        The only exception to this is the polynomial 0. If your polynomial is
     *        just the constant 0 then you would return an empty map.
     *
     *        ie. y = 0 would be returned as {}
     *
     * @return std::map<power, coeff>
     *  A map representing the canonical form of the polynomial
     */
    std::map<power, coeff> canonical_form() const;

    // ----------------------------------------  Alan :: part 1  ------------------------------------------------------
    /**
     * Overload the +, * and % operators. The function prototypes are not
     * provided.
     * 
     * Addition (+) should support
     * 1. polynomial + polynomial
     * 2. polynomial + int
     * 3. int + polynomial
     * 
     * Multiplication (*) should support
     * 1. polynomial * polynomial
     * 2. polynomial * int
     * 3. int * polynomial
     * 
     * Modulo (%) should support
     * 1. polynomial % polynomial
     */

    // + operator overload
    polynomial operator+(const polynomial &other) const;
    polynomial operator+(int constant) const;
    friend polynomial operator+(int constant, const polynomial &poly);

    // * operator overload
    polynomial operator*(const polynomial &other) const;
    polynomial operator*(int constant) const;
    friend polynomial operator*(int constant, const polynomial &poly);

    // % operator overload
    polynomial operator%(const polynomial &other) const;

    // - operator overload
    polynomial operator-(const polynomial &other) const;
    polynomial operator-(int constant) const;
    friend polynomial operator-(int constant, const polynomial &poly);

private:
    std::map<power, coeff> terms;
};

#endif