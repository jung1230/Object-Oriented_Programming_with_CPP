#include <iostream>
#include <vector>

int main() {
    std::vector<int> Vector;
    std::cout << "\n-------------------- push_back() --------------------\n";
 
    std::cout << "Capacity: " << Vector.capacity() << std::endl;
    std::cout << "Size: " << Vector.size() << std::endl;
    for (int i = 0; i < 10; ++i) {
        Vector.push_back(i);

        // Output capacity and size after each push_back()
        std::cout << "Capacity: " << Vector.capacity() << std::endl;
        std::cout << "Size: " << Vector.size() << std::endl;
    }


    std::cout << "\n-------------------- pop_back() --------------------\n";

    while (!Vector.empty()) {
        Vector.pop_back();

        // Output capacity and size after each pop_back()
        std::cout << "Capacity: " << Vector.capacity() << std::endl;
        std::cout << "Size: " << Vector.size() << std::endl;
    }
    return 0;
}