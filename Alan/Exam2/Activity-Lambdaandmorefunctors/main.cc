#include <iostream>
#include <vector>

// Task 1: Write a function my_foreach
template<typename Iterator, typename Function>
void my_foreach(Iterator start, Iterator end, Function func) {
    for (auto it = start; it != end; it++) {
        func(*it);
    }
}

// Task 2: Write a function Increment
void Increment(int& num) {
    num++;
}


// Task 4: Write a function object IncrementK
class IncrementK {
private:
    int k;

public:
    IncrementK(int _k) : k(_k) {}

    void operator()(int& num) const {
        num += k;
    }
};

int main() {
    // Task 2
    std::vector<int> vec1 = {1, 2, 3, 4, 5};
    std::cout << "Before" << std::endl;
    for (const auto& num : vec1) {
        std::cout << num << " " << std::endl;;
    }
    my_foreach(vec1.begin(), vec1.end(), Increment);

    std::cout << "After" << std::endl;
    for (const auto& num : vec1) {
        std::cout << num << " " << std::endl;;
    }



    // [capture](parameters) -> return_type {
    //     // function body
    // }
    // Task 3 implement lambda
    std::vector<int> vec2 = {1, 2, 3, 4, 5};
    std::cout << "Before" << std::endl;
    for (const auto& num : vec2) {
        std::cout << num << " " << std::endl;;
    }
    my_foreach(vec2.begin(), vec2.end(), [](int& num) { num++; });

    std::cout << "After" << std::endl;
    for (const auto& num : vec2) {
        std::cout << num << " " << std::endl;;
    }

    // Task 4
    std::vector<int> vec3 = {1, 2, 3, 4, 5};

    std::cout << "Before" << std::endl;
    for (const auto& num : vec3) {
        std::cout << num << " " << std::endl;;
    }
    int k = 10;
    my_foreach(vec3.begin(), vec3.end(), IncrementK(k));

    std::cout << "After" << std::endl;
    for (const auto& num : vec3) {
        std::cout << num << " " << std::endl;;
    }




    return 0;
}