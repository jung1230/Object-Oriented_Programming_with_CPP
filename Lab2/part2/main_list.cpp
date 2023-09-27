#include <iostream>
#include <cstdio>

#include "hash_list.h"


void iterator_example(hash_list<int, float> &list)
{
    /** We have to reset the iterator before we use it */
    list.reset_iter();

    /** We want to iterate over all nodes, so keep iterating until we're at the end */
    while (!list.iter_at_end())
    {
        /** Get pointers to key/value pairs */
        std::optional<std::pair<const int *, float *>> node_values = list.get_iter_value();

        /** Increment the VALUE. Note that the key remains unchanged */
        (*node_values.value().second)++;

        std::cout << "Key: " << *node_values.value().first
                  << " and value: " << *node_values.value().second << std::endl;

        /** Go to the next element */
        list.increment_iter();
    }
}


// check size, value, and try find value with two conditions
void t_insert(void){ 
    std::cout << "-------------------------------\nenter unittest of insert and get_value" << std::endl;
    hash_list<int, float> list;

    //check if the list is initiallize correctly
    if (list.get_size() != 0){
        std::cout << "t_insert: Invalid size(0)" << std::endl;
    }

    list.insert(3,3.3);
    // check if the list is increased
    if (list.get_size() != 1){
        std::cout << "t_insert: Invalid size(1)" << std::endl;
    }
    // check if the inserted value is in the list
    if (!list.get_value(3).has_value()){
        std::cout << "t_insert: expected 3 to be in list but it wasn't" << std::endl;
    }
    // check if the non-inserted value is in the list
    if (list.get_value(4).has_value()){
        std::cout << "t_insert: don't expected 4 to be in list but it was" << std::endl;
    }
    // check if it return null when key not found
    if  (list.get_value(4) != std:: nullopt){
        std::cout << "t_insert: the key is found" << std::endl;
    }

    list.insert(4,4.4);
    // check if the list is increased
    if (list.get_size() != 2){
        std::cout << "t_insert: Invalid size(2)" << std::endl;
    }
    // check if the inserted value is in the list
    if (!list.get_value(4).has_value()){
        std::cout << "t_insert: expected 4 to be in list but it wasn't" << std::endl;
    }
    // check if the non-inserted value is in the list
    if (list.get_value(5).has_value()){
        std::cout << "t_insert: don't expected 5 to be in list but it was" << std::endl;
    }
    // check if it return null when key not found
    if  (list.get_value(5) != std:: nullopt){
        std::cout << "t_insert: the key is found" << std::endl;
    }

    std::optional<float> temp = list.get_value(3);
    if (!temp){
        std::cout << "temp is empty." << std::endl;
    }
    temp = list.get_value(7);
    if (temp) {
        std::cout << "it should be empty" << *temp << std::endl;
    } 
    std::cout << "exit unittest of insert and get_value\n------------------------------------" << std::endl;
}

void t_remove(void){
    std::cout << "-------------------------------\nenter unittest of remove" << std::endl;
    hash_list<int, float> list;
    list.insert(3,5.5);
    list.insert(1,2.3);
    list.remove(1);
    if(list.get_value(3) != 5.5){
        std::cout << "t_remove: invalid value" << std::endl;
    }
    if(list.get_value(1) != std::nullopt){
        std::cout << "t_remove: invalid remove" << std::endl;
    }
    if(list.get_size() != 1){
        std::cout << "t_remove: invalid size" << std::endl;
    }
    list.remove(3);
    if(list.get_value(3) != std::nullopt){
        std::cout << "t_remove: invalid remove" << std::endl;
    }
    if(list.get_size() != 0){
        std::cout << "t_remove: invalid size" << std::endl;
    }
    std::cout << "exit unittest of remove\n------------------------------------" << std::endl;
}

void t_copy(void){
    std::cout << "-------------------------------\nenter unittest of copy" << std::endl;
    hash_list<int, float> list1;
    list1.insert(1, 1.1);
    list1.insert(2, 2.2);
    list1.insert(3, 3.3);
    // test for copy by construtor
    hash_list<int, float> list2(list1);
    if(list1.get_value(1) != list2.get_value(1))
        std::cout << "t_copy: wrong copy value of key 1 by copy of constuctor" << std::endl;
    if(list1.get_value(2) != list2.get_value(2))
        std::cout << "t_copy: wrong copy value of key 2 by copy of constuctor" << std::endl;
    if(list1.get_value(3) != list2.get_value(3))
        std::cout << "t_copy: wrong copy value of key 3 by copy of constuctor" << std::endl;
    // test for copy by operator
    hash_list<int, float> list3;
    list3.insert(1, 3.4);
    list3.insert(2, 7.5);
    list3.insert(3, 6.6);
    list3 = list1;
    if(list1.get_value(1) != list3.get_value(1))
        std::cout << "t_copy: wrong copy value of key 1 by copy of operator" << std::endl;
    if(list1.get_value(2) != list3.get_value(2))
        std::cout << "t_copy: wrong copy value of key 2 by copy of operator" << std::endl;
    if(list1.get_value(3) != list3.get_value(3))
        std::cout << "t_copy: wrong copy value of key 3 by copy of operator" << std::endl;
    std::cout << "exit unittest of copy\n------------------------------------" << std::endl;
}

int main(int argc, char *argv[])
{
    //Part1
    std::cout << "------------------------------------------------------\nEnter PART1\n" << std::endl;
    t_insert();
    t_remove();
    //trace_5();
    hash_list<int, float> list;



    if (list.get_size() != 0)
    {
        std::cout << "Invalid size" << std::endl;
        exit(1);
    }

    list.insert(3, 3.3);
    list.insert(4, 4.4);
    list.insert(5, 5.5);
    list.insert(6, 6.6);

    if (list.get_size() != 4)
    {
        std::cout << "Invalid size" << std::endl;
        exit(1);
    }

    if (!list.get_value(3).has_value())
    {
        std::cout << "expected 3 to be in list but it wasn't" << std::endl;
        exit(1);
    }


    //Part2
    std::cout << "------------------------------------------------------\nEnter PART2\n" << std::endl;
    t_copy();
    iterator_example(list);

}
