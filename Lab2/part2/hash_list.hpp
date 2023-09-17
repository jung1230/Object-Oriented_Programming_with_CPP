#include "hash_list.h"


/**
    * @brief Create an empty list
    */
//Alan
template <typename K, typename V> hash_list<k,v>::hash_list(){ 
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
void insert(int key, float value);

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
//Alan
template <typename K, typename V> std::optional<V> hash_list<K, V>::get_value(K key) const { 
    // ptr for current
    node *cur = head;

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
bool remove(int key);

/**
    * @brief Return the number of nodes in the list. 
    * This function must run in constant time
    * 
    * @return
    *  the number of nodes in the list
    */
// Alan
template <typename K, typename V> size_t hash_list<K, V>::get_size() const{
    return size;
}

/**
    * @brief Free all memory associated with the nodes. 
    * This must not free the nodes recursively
    */
~hash_list();


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
    // Alan
template <typename K, typename V>
hash_list<K, V>::hash_list(const hash_list &other){
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

/**
    * @brief Assignment operator
    * 
    * @param other
    *  The list to create a copy of 
    * @return
    *  A reference to the list that was created. This allows for code like
    *  a = b = c to work
    */
hash_list &operator=(const hash_list &other);

/**
    * @brief Resets the iterator back to point to the first element in the list. If the list is 
    * empty then the iterator is set to NULL.
    */
// Alan
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
void increment_iter();

/**
    * @brief Return an optional that contains a pointer to the key and a pointer to the value
    * of the node pointed to by the iterator. If the iterator is NULL this returns
    * an empty optional
    * 
    * @return
    *  If the iterator is NULL returns an empty optional
    *  Otherwise returns a pointer to the key/value pointed to by the current iterator
    */
// Alan
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
bool iter_at_end();
/**-----------------------------------------------------------------------------------
    * END Part 2
    *------------------------------------------------------------------------------------*/


