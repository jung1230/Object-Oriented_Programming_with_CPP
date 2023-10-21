#include <vector>
#include <iostream>
# include <list>
#include <algorithm> // Needed for std::for_each


// pass list by const reference and use a const iterator to print
void ConstIterator(const std::list<int>& l) {
    std::list<int>::const_iterator pl = l.begin();
    while ( pl != l.end() ) {
        std::cout << *pl << " ";
        pl++;
    }
    std::cout << std::endl << std::endl;
}

void Increment(int &l){
l++;
}

int main() {
    std::vector<int> v = {1, 2, 3, 4, 5};
    std::vector<int>::iterator p = v.begin();
    while (p != v.end()) {
        std::cout << *p << " ";
        p++;
    }


    std::list<int> l = {1, 2, 3, 4, 5};
    std::list<int>::iterator pl = l.begin();
    //  use a traditional ::iterator object to print the list values
    while (pl != l.end()) {
        std::cout << *pl << " ";
        pl++;
    }
    // use a range-based for loop with auto to print the values
    for(auto i:l){
        std::cout << i << " ";

    }
    // pass list by const reference and use a const iterator to print
    ConstIterator(l);

    // use for_each method with an appropriate Increment()
    // function to modify each value in the list. Print before / after to prove it’s
    // working

    std::for_each(l.begin(),l.end(),Increment);
    for(auto i:l){
        std::cout << i << " ";

    }
    return 0;
}



