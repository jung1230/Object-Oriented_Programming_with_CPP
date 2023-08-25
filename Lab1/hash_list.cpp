#include "hash_list.h"
#include <iostream>
/**-----------------------------------------------------------------------------------
 * START Part 1
 *------------------------------------------------------------------------------------*/

void display(struct node* node){
  while (node != nullptr){
    std::cout << node->key << " "<< node->value << " "<< std::endl;
    node = node->next;
  }
  std::cout <<"end of display\n"<< std::endl;
}


 // constructor, initiallize the list of size, head, iand iter_ptr
hash_list::hash_list() {
    size = 0;
    head = nullptr;
    iter_ptr = nullptr;
}

// methods 
void hash_list::insert(int key, float value) {
    //  * @brief Insert a node with the corresponding key value pair into the list.
    //  * If a node with the associated key already exists, update that node with the new value
    //  * instead of adding a new node to the list.
    //  * 
    //  * @param key
    //  *  The key to insert into the list
    //  * @param value
    //  *  The value to insert into the list
    

    // this is for printing debugging stuff
    // std::cout <<"start to display, inserting"<<key<<value<< std::endl;
    // display(head);

    //check if the list is empty. if so, insert first node, size++, and return
    if(head == nullptr){
        node *new_node = new node(key, value, nullptr);
        head = new_node;
        size++;
        return;
    }
    
    //iterate the list to find specific key
    node *cur = head;
    while(cur != nullptr){
        if(cur -> key == key){
            cur -> value = value;
            return;
        }
        cur = cur -> next;
    }

    // the key don't exist, so insert a new node at the front
    node *new_node = new node(key, value, head);
    head = new_node;
    size++;
}

std::optional<float> hash_list::get_value(int key) const { 
    /**
     * @brief Return an optional containing the value associated with the specified key. If the key
     * isn't in the list return an empty optional.
     * 
     * @param key
     *  The key to search the list for
     * @return
     *  If the key isn't in the list returns an empty optional
     *  If the key is in the list returns the corresponding value
     */

    //iterate the list to find specific key
    node *cur = head;
    while(cur != nullptr){
        if(cur -> key == key){
            return cur -> value; 
        }
        cur = cur -> next;
    }

    // can't find the key, return empty optional
    return std::nullopt; 
}

bool hash_list::remove(int key) { return false; }

size_t hash_list::get_size() const { return size; }

hash_list::~hash_list() {}

/**-----------------------------------------------------------------------------------
 * END Part 1
 *------------------------------------------------------------------------------------*/


/**-----------------------------------------------------------------------------------
 * START Part 2
 *------------------------------------------------------------------------------------*/

hash_list::hash_list(const hash_list &other) {}

hash_list &hash_list::operator=(const hash_list &other) { return *this; }

void hash_list::reset_iter() {}


void hash_list::increment_iter() {}


std::optional<std::pair<const int *, float *>> hash_list::get_iter_value() { return std::nullopt; }


bool hash_list::iter_at_end() { return false; }
/**-----------------------------------------------------------------------------------
 * END Part 2
 *------------------------------------------------------------------------------------*/
