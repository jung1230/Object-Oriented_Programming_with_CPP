#include <iostream>
#include <vector>

// -------------------------- step 1 --------------------------
// pred
bool IsOdd(int i) {
    return i % 2 != 0;
}
// pred
bool IsEven(int i) {
    return i % 2 == 0;
}
// pred
bool IsGreater5(int i) {
    return i > 5;
}
// pred
bool IsLongerThanFive(const std::string& str) {
    return str.length() > 5;
}


template<typename Predicate>
void MatchCond(Predicate pred) {
    for (int i = 1; i < 11; i++) {
        if (pred(i)) {
            std::cout << i << " ";
        }
    }
    std::cout << std::endl;
}


// -------------------------- step 2 & 3 --------------------------
template<typename Iter, typename Predicate>
Iter find_if(Iter start, Iter end, Predicate pred) {
    for (Iter it = start; it != end; it++) {
        if (pred(*it)) {
            return it;
        }
    }
    return end;
}




int main() {

// -------------------------- step 1 --------------------------
    MatchCond(IsOdd);
    MatchCond(IsEven);
    MatchCond(IsGreater5);

// -------------------------- step 2 --------------------------
    std::vector<int> vec = {2, 14, 7, 9, 16, 3};
    auto p = find_if(vec.begin(), vec.end(), IsEven);
    if(p == vec.end())
        std::cout << "No Match" << std::endl;
    else
        std::cout << "first match: " << *p << std::endl;



// -------------------------- step 3 --------------------------
    std::vector<std::string> strVec = {"Alan","Peter", "lewis", "Max"};

    auto strMatch = find_if(strVec.begin(), strVec.end(), IsLongerThanFive);
    if(strMatch == strVec.end())
        std::cout << "No Match" << std::endl;
    else
        std::cout << "first match: " << *strMatch << std::endl;

    std::vector<int> intVec = {2, 14, 7, 9, 16, 3};
    auto intMatch = find_if(intVec.begin(), intVec.end(), IsOdd);
    if(intMatch == intVec.end())
        std::cout << "No Match" << std::endl;
    else
        std::cout << "first match: " << *intMatch << std::endl;
    return 0;
}
