
#include "hash_map.h"
#include <iostream>

int main() {
    int i;
    // Test Case 1: Creating a hash_map
    std::cout << "enter test case 1 "<< std::endl;
    hash_map map(10);

    if(map.get_size() != 0){
        std::cout << "map.get_size() == 0 "<< std::endl;
        return 0;
    }
    if(map.get_capacity() != 10){
        std::cout << "map.get_capacity() == 10 "<< std::endl;
        return 0;
    }

    // Test Case 2: Inserting and getting values
    std::cout << "enter test case 2 "<< std::endl;
    map.insert(1, 1.1);
    map.insert(2, 8.7);
    map.insert(2, 2.2);
    map.insert(3, 6.9);
    map.insert(3, 3.3);
    std::cout << "value of key "<<map.get_value(1).value() << std::endl;
    std::cout << "value of key "<<map.get_value(2).value() << std::endl;
    std::cout << "value of key "<<map.get_value(3).value() << std::endl;
    if(map.get_value(1).value() != float(1.1)){
        std::cout << "map.get_value(1).value() is wrong"<< std::endl;
        return 0;
    }
    if(map.get_value(2).value()!= float(2.2)){
        std::cout << "map.get_value(2).value() is wrong"<< std::endl;
        return 0;
    }  
    if(map.get_value(3).value()!= float(3.3)){
        std::cout << "map.get_value(3).value() is wrong"<< std::endl;
        return 0;
    }   
    if(map.get_size() != 3){
        std::cout << "map.get_size() is wrong" << std::endl;
        return 0;
    }


    // Test Case 3: Removing a key
    std::cout << "enter test case 3 "<< std::endl;
    bool removed = map.remove(1);

    if(!removed){
        std::cout << "removed is wrong" << std::endl;
        return 0;
    }
    if(map.get_value(1).has_value() != false){
        std::cout << "map.get_value(1).has_value() == false" << std::endl;
        return 0;
    }
    if(map.get_size() != 2){
        std::cout << "map.get_size() == 1" << std::endl;
        return 0;
    }
    removed = map.remove(1);
    if(removed){
        std::cout << "removed is wrong" << std::endl;
        return 0;
    }
    if(map.get_value(1).has_value() != false){
        std::cout << "map.get_value(1).has_value() == false" << std::endl;
        return 0;
    }
    if(map.get_size() != 2){
        std::cout << "map.get_size() == 1" << std::endl;
        return 0;
    }
    // Test Case 4: Copy constructor
    std::cout << "enter test case 4 "<< std::endl;
    hash_map map2 = map;

    if(map2.get_size() != 2){
        std::cout << "map2.get_size() == 2" << std::endl;
        return 0;
    }
    if(map2.get_capacity() != 10){
        std::cout << "map2.get_capacity() == 10 "<< std::endl;
        return 0;
    }
    if(map2.get_value(2).value()!= float(2.2)){
        std::cout << "map2.get_value(2).value()!= 2.2" << std::endl;
        return 0;
    }
    if(map2.get_value(3).value() != float(3.3)){
        std::cout << "map2.get_value(3).value() == 3.3" << std::endl;
        return 0;
    }

    // Test Case 5: Assignment operator
    std::cout << "enter test case 5 "<< std::endl;
    hash_map map3(5);
    map3 = map2;

    if(map3.get_size() != 2){
        std::cout << "map3.get_size() == 2" << std::endl;
        return 0;
    }
    if(map3.get_capacity() != 10){
        std::cout << "map3.get_capacity() == 10 "<< std::endl;
        return 0;
    }
    if(map3.get_value(2).value() != float(2.2)){
        std::cout << "map3.get_value(2).value() == 2.2" << std::endl;
        return 0;
    }
    if(map3.get_value(3).value() != float(3.3)){
        std::cout << "map3.get_value(3).value() == 3.3" << std::endl;
        return 0;
    }

    // Test Case 6: Copying keys to an array
    std::cout << "enter test case 6 "<< std::endl;
    int keys[10];
    map3.get_all_keys(keys);

    if(keys[0] != 2){
        std::cout << "keys[0] == 2" << std::endl;
        return 0;
    }
    if(keys[1] != 3){
        std::cout << "keys[1] == 3" << std::endl;
        return 0;
    }


    // Test Case 7: Getting bucket sizes
    std::cout << "enter test case 7 "<< std::endl;
    size_t buckets[10];
    map3.get_bucket_sizes(buckets);
    for(i = 0;i < 10;i ++){
        std::cout << "Bucket " << i << " has " << buckets[i] << " key/value pairs\n";  
    }
    std::cout << "All test cases passed!" << std::endl;

    return 0;
}

