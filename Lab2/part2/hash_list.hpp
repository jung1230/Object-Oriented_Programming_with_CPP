//#include "hash_list.h"


/**
    * @brief Create an empty list
    */
template <typename K, typename V> 
hash_list<K, V>::hash_list(){ 
    //constructor, initiallize the list of size, head, iand iter_ptr
    size = 0;
    head = nullptr;
    iter_ptr = nullptr;
}

/**-----------------------------------------------------------------------------------
    * START Part 1
    *------------------------------------------------------------------------------------*/

/**
    * @brief Insert a node with the corresponding key value pair into the list.
    * If a node with the associated key already exists, update that node with the new value
    * instead of adding a new node to the list.
    * 
    * @param key
    *  The key to insert into the list
    * @param value
    *  The value to insert into the list
    */
template <typename K, typename V> 
void hash_list<K, V>::insert(K key, V value){
    //check if the list is empty. if so, insert first node, size++, and return
    if(head == nullptr){
        node<K, V> *new_node = new node<K, V>(key, value, nullptr);
        head = new_node;
        size++;
        return;
    }
    
    //iterate the list to find specific key
    
    reset_iter();
    while(!iter_at_end()){
        if(iter_ptr -> key == key){
            iter_ptr -> value = value;
            return;
        }
        increment_iter();
    }

    // the key don't exist, insert a new node at the front
    node<K, V> *new_node = new node<K, V>(key, value, head);
    head = new_node;
    size++;
}

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
template <typename K, typename V> 
std::optional<V> hash_list<K, V>::get_value(K key) const { 
    // ptr for current
    node<K, V> *cur = head;

    // while not to the end
    while (cur != nullptr) {
        if (cur -> key == key) {
            // key found, return value
            return cur->value;
        }
        cur = cur -> next;
    }
    // can't find the key, return empty optional
    return std::nullopt; 
}

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
template <typename K, typename V> 
bool hash_list<K, V>::remove(K key){
    node<K, V> dummy = node<K, V>(87, 87, head); // dummy node which next is point to head
    node<K, V> *prev = &dummy; // Keep record of previous node
    //check if the list is empty. if so, return false
    if(head == nullptr){
        return false;
    }
    //iterate the list to find specific node containing the key
    reset_iter();
    while(!iter_at_end()){
        if(iter_ptr -> key == key){ // if find the node, delete it and return true
            prev -> next = iter_ptr-> next;
            head = dummy.next;
            size --;
            delete iter_ptr;
            return true;
        }
        prev = iter_ptr;
        increment_iter();
    }
    //After travering the whole list, if the node is not found, return false
    return false; 
}

/**
    * @brief Return the number of nodes in the list. 
    * This function must run in constant time
    * 
    * @return
    *  the number of nodes in the list
    */
template <typename K, typename V> 
size_t hash_list<K, V>::get_size() const{
    return size;
}

/**
    * @brief Free all memory associated with the nodes. 
    * This must not free the nodes recursively
    */
template <typename K, typename V> 
hash_list<K, V>::~hash_list(){
    if(head != nullptr){
        reset_iter();
        iter_ptr = head->next;
        while(head != nullptr){ 
            delete head;
            size --;
            head = iter_ptr;
            if(head != nullptr)
                increment_iter();
        }
}
}


/**-----------------------------------------------------------------------------------
    * END Part 1
    *------------------------------------------------------------------------------------*/


/**-----------------------------------------------------------------------------------
    * START Part 2
    *------------------------------------------------------------------------------------*/
/**
    * @brief The copy constructor
    * 
    * @param other
    *  The list to create a copy of
    */
template <typename K, typename V>
hash_list<K, V>::hash_list(const hash_list<K, V> &other){
    // "other" is something that we want to copy, copy size and head
    size = other.size;
    
    // remember to allocate mem for copying constructor
    if (other.head != nullptr){
        head = new node<K, V>(other.head -> key, other.head -> value, nullptr);

        // copy all node from other
        node<K, V> *cur_other = other.head -> next;
        node<K, V> *cur_new = head;
        node<K, V> *temp;
        
        while(cur_other != nullptr){
            temp = new node<K, V>(cur_other -> key, cur_other -> value, nullptr);
            cur_new -> next = temp;
            cur_new = cur_new -> next;
            cur_other = cur_other -> next;
        }
    }
    else
        head = other.head;
    
}

/**
    * @brief Assignment operator
    * 
    * @param other
    *  The list to create a copy of 
    * @return
    *  A reference to the list that was created. This allows for code like
    *  a = b = c to work
    */
template <typename K, typename V>
hash_list<K, V>& hash_list<K, V>::operator=(const hash_list<K, V> &other){
    node<K, V> *curr;
    node<K, V> *cur_next;
    node<K, V> *temp;
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
        head = new node<K, V>(other.head -> key, other.head -> value, nullptr);

        // copy all node from other
        cur_next = other.head -> next;
        curr = head;
        while(cur_next != nullptr){
            temp = new node<K, V>(cur_next -> key, cur_next -> value, nullptr);
            curr -> next = temp;
            curr = curr -> next;
            cur_next = cur_next -> next;
        }
    }
    else
        head = other.head;

    return *this;
}

/**
    * @brief Resets the iterator back to point to the first element in the list. If the list is 
    * empty then the iterator is set to NULL.
    */
template <typename K, typename V>
void hash_list<K, V>:: reset_iter(){
    // if the list is empty, set iterator to NULL
    if (head == nullptr){
        iter_ptr = nullptr;
    }
    // else, set it to point to the first element
    else{
        iter_ptr = head;
    }
}

/**
    * @brief Moves the iterator to the next element. If the iterator points to the last element
    * of the list when this is called the iterator is set to NULL. If the iterator is NULL
    * when this function is called then this function does nothing
    */
template <typename K, typename V>
void hash_list<K, V>::increment_iter(){
    if(iter_ptr == nullptr)
        iter_ptr = nullptr;
    else if(iter_ptr -> next == nullptr)
        iter_ptr = nullptr;
    else
        iter_ptr = iter_ptr -> next;
}

/**
    * @brief Return an optional that contains a pointer to the key and a pointer to the value
    * of the node pointed to by the iterator. If the iterator is NULL this returns
    * an empty optional
    * 
    * @return
    *  If the iterator is NULL returns an empty optional
    *  Otherwise returns a pointer to the key/value pointed to by the current iterator
    */
template <typename K, typename V>
std::optional<std::pair<const K*, V*>> hash_list<K, V>::get_iter_value() {
    if (iter_ptr != nullptr) 
        return std::pair{&(iter_ptr -> key), &(iter_ptr -> value)};
     else 
        //return empty optional when there is no things
        return std::nullopt; 
}
/**
    * @brief Returns true if the iterator is NULL
    * 
    * @return
    *  True if the iterator is NULL
    *  False otherwise
    */
template <typename K, typename V>
bool hash_list<K, V>::iter_at_end(){
    if (iter_ptr == nullptr)
        return true;
    else
        return false; 
}
/**-----------------------------------------------------------------------------------
    * END Part 2
    *------------------------------------------------------------------------------------*/


