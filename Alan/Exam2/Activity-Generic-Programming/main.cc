#include <iostream>
#include <vector>
#include <list>

// Step 1
int sumvec(std::vector<int>::iterator start, std::vector<int>::iterator end) {
    int sum = 0;
    for (std::vector<int>::iterator iter = start; iter != end; iter++) { //or use auto do declare iter
        sum += *iter;
    }
    return sum;
}

// Step 2
int sumlist(std::list<int>::iterator start, std::list<int>::iterator end) {
    int sum = 0;
    for (auto iter = start; iter != end; iter++) {
        sum += *iter;
    }
    return sum;
}

// Step 3
template<typename T>
int commonfunc(T start, T end){
    int sum = 0;
    for (T iter = start; iter != end; iter++) {
        sum += *iter;
    }
    return sum;

} 

// Step 4
template<typename T, typename K>
K finalfunc(T start, T end, K sum){
    for (T iter = start; iter != end; iter++) {
        sum += *iter;
    }
    return sum;

} 

int main() {
    // Step 1
    std::vector<int> vec = {16, 23, 11, 14, 19};
    int sum_vec = sumvec(vec.begin(), vec.end());
    std::cout << "Sum of vec: " << sum_vec << std::endl;


    // Step 2
    std::list<int> li = {16, 23, 11, 14, 19};
    int sum_li = sumlist(li.begin(), li.end());
    std::cout << "Sum of li: " << sum_li << std::endl;


    // Step 3
    int com_vec = commonfunc(vec.begin(), vec.end());
    std::cout << "Sum of vec: " << com_vec << std::endl;
    
    int com_li = commonfunc(li.begin(), li.end());
    std::cout << "Sum of li: " << com_li << std::endl;

    // Step 4
    // maybe the sum is not a int
    std::list<double> lid = {16.5, 23.5, 11.5, 14.5, 19.5};
    double final_li = 0.0;
    final_li = finalfunc(lid.begin(), lid.end(), final_li);
    std::cout << "Sum of li: " << final_li << std::endl;
    int final_vec = 0;
    final_vec = finalfunc(vec.begin(), vec.end(), final_vec);
    std::cout << "Sum of vec: " << final_vec << std::endl;

    std::vector<std::string> stri = {"Ver","Ham","Rus"};
    std::string final_stri = "";
    final_stri = finalfunc(stri.begin(), stri.end(), final_stri);
    std::cout << "Sum of string: " << final_stri << std::endl;


}