#include <vector>
#include <iostream>

void pass_para(std::vector<int> temp_vector){
    temp_vector[2] = 87;

    std::cout << "In func" <<std::endl;

    for (int i : temp_vector) {
        std::cout << i << ' ';
    }
    std::cout << std::endl;
}

void pass_array(int *array){
    array[2] = 87;

    std::cout << "In func" <<std::endl;

    for (int i = 0; i < 10; i++) {
        std::cout << array[i] << ' ';
    }
    std::cout << std::endl;
}

int main() {
    int i;
    std::vector<int> intVec(10, 1);

    std::cout << "Before" <<std::endl;
    for (int i : intVec) {
        std::cout << i << ' ';
    }
    std::cout << std::endl;

    pass_para(intVec);
    std::cout << "After" <<std::endl;
    for (int i : intVec) {
        std::cout << i << ' ';
    }
    std::cout << std::endl;



    std::cout << "\n" <<std::endl;
    int array[10];
    std::cout << "Before" <<std::endl;
    for (i = 0; i < 10; i++) {
        array[i] = i;
        std::cout << array[i] << ' ';
    }
    std::cout << std::endl;
    pass_array(array);
    std::cout << "After" <<std::endl;
    for (i = 0; i < 10; i++) {
        std::cout << array[i] << ' ';
    }
    std::cout << std::endl;
    return 0;
}