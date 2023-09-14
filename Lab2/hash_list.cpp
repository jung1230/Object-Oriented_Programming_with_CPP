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

    // the key don't exist, insert a new node at the front
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

bool hash_list::remove(int key) {
    /**
     * @brief Remove the node containing the specified key from the list and return true.
     * If the key isn't in the list return false.
     * 
     * @param key
     *  The key to remove from the list
     * @return
     *  True if the key was removed from the list
     *  False if the key wasn't in the list
     */ 
    node dummy = node(87, 87, head); // dummy node which next is point to head
    node *prev = &dummy; // Keep record of previous node
    //check if the list is empty. if so, return false
    if(head == nullptr){
        return false;
    }
    //iterate the list to find specific node containing the key
    node *cur =head;
    while(cur != nullptr){
        if(cur -> key == key){ // if find the node, delete it and return true
            prev -> next = cur-> next;
            head = dummy.next;
            size --;
            delete cur;
            return true;
        }
        prev = cur;
        cur = cur -> next;
    }
    //After travering the whole list, if the node is not found, return false
    return false; 
}

size_t hash_list::get_size() const {
    // dang peter, salary theif
    return size; 
}

// destructor for hash list (remember to write commands, Peter. Thank you for your cooporation)
hash_list::~hash_list() {
    if(head != nullptr){
        node *cur = head->next;
        while(head != nullptr){ 
            delete head;
            size --;
            head = cur;
            if(head != nullptr)
                cur = head -> next;
        }
    }
}

/**-----------------------------------------------------------------------------------
 * END Part 1
 *------------------------------------------------------------------------------------*/


/**-----------------------------------------------------------------------------------
 * START Part 2
 *------------------------------------------------------------------------------------*/

hash_list::hash_list(const hash_list &other) {
    /**
     * @brief The copy constructor
     * 
     * @param other
     *  The list to create a copy of
     */

     // "other" is something that we want to copy, copy size and head
    size = other.size;
    
    // remember to allocate mem for copying constructor
    if (other.head != nullptr){
        head = new node(other.head -> key, other.head -> value, nullptr);

        // copy all node from other
        node *cur_other = other.head -> next;
        node *cur_new = head;
        node *temp;
        while(cur_other != nullptr){
            temp = new node(cur_other -> key, cur_other -> value, nullptr);
            cur_new -> next = temp;
            cur_new = cur_new -> next;
            cur_other = cur_other -> next;
        }
    }
    else
        head = other.head;

}

hash_list &hash_list::operator=(const hash_list &other) { 
    /**
     * @brief Assignment operator
     * 
     * @param other
     *  The list to create a copy of 
     * @return
     *  A reference to the list that was created. This allows for code like
     *  a = b = c to work
     */
    node *curr;
    node *cur_next;
    node *temp;
    if(this == &other){ //Special case, handle self assignment
        return *this;
    }
    if(head != nullptr){ // need to delete the list first
        curr = head;
        cur_next = head->next;
        while(curr != nullptr){
            delete curr;
            curr = cur_next;
            if(cur_next != nullptr)
                cur_next = cur_next -> next;
        }
        // After deletion, set head to nullptr
        head = nullptr;
    }
    size = other.size;
    
    // remember to allocate mem for copying constructor
    if (other.head != nullptr){
        head = new node(other.head -> key, other.head -> value, nullptr);

        // copy all node from other
        cur_next = other.head -> next;
        curr = head;
        while(cur_next != nullptr){
            temp = new node(cur_next -> key, cur_next -> value, nullptr);
            curr -> next = temp;
            curr = curr -> next;
            cur_next = cur_next -> next;
        }
    }
    else
        head = other.head;

    return *this;
}

void hash_list::reset_iter() {
    /**
     * @brief Resets the iterator back to point to the first element in the list. If the list is 
     * empty then the iterator is set to NULL.
     */

    // if the list is empty, set iterator to NULL
    if (head == nullptr){
        iter_ptr = nullptr;
    }
    // else, set it to point to the first element
    else{
        iter_ptr = head;
    }

}


void hash_list::increment_iter() {
    /**
     * @brief Moves the iterator to the next element. If the iterator points to the last element
     * of the list when this is called the iterator is set to NULL. If the iterator is NULL
     * when this function is called then this function does nothing
     */
    if(iter_ptr == nullptr)
        iter_ptr = nullptr;
    else if(iter_ptr -> next == nullptr)
        iter_ptr = nullptr;
    else
        iter_ptr = iter_ptr -> next;
}


std::optional<std::pair<const int *, float *>> hash_list::get_iter_value() { 
    /**
     * @brief Return an optional that contains a pointer to the key and a pointer to the value
     * of the node pointed to by the iterator. If the iterator is NULL this returns
     * an empty optional
     * 
     * @return
     *  If the iterator is NULL returns an empty optional
     *  Otherwise returns a pointer to the key/value pointed to by the current iterator
     */
    if(iter_ptr == nullptr)
        return std::nullopt;
    else
        return std::pair{&(iter_ptr -> key), &(iter_ptr ->value)};
}


bool hash_list::iter_at_end() { 
    /**
     * @brief Returns true if the iterator is NULL
     * 
     * @return
     *  True if the iterator is NULL
     *  False otherwise
     */
    if (iter_ptr == nullptr)
        return true;
    else
        return false; 
}
/**-----------------------------------------------------------------------------------
 * END Part 2
 *------------------------------------------------------------------------------------*/
