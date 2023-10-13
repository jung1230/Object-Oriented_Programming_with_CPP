#include <vector>
#include <iostream>

int main() {
    std::vector<int> intVec(10, 1);

    for (int i : intVec) {
        std::cout << i << ' ';
    }
    std::cout << std::endl;

    int test ;

    test = intVec[20]; // nothing happen
    std::cout << test<< std::endl;

    // this provide bonds tracking!
    test = intVec.at(20); // terminate called after throwing an instance of 'std::out_of_range'. what():  vector::_M_range_check: __n (which is 20) >= this->size() (which is 10)
    std::cout << test<< std::endl;
    return 0;
}