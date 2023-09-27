


/**
    * @brief Construct a new hash map object
    */
template <typename K, typename V>
hash_map<K, V>::hash_map(size_t capacity,float upper_load_factor,float lower_load_factor){
    //constructor, initiallize the list of size, capacity, upper_load_factor, and  lower_load_factor   
    _size = 0;
    _capacity = capacity;
    _upper_load_factor = upper_load_factor;
    _lower_load_factor = lower_load_factor;
    _head = new hash_list<K, V>[_capacity];
}


/**
    * @brief Construct a new hash map object
    *
    * @param other
    *  The map to create a copy of
    */
template <typename K, typename V>
hash_map<K, V>::hash_map(const hash_map &other){
    //copy size, capacity, upper_load_factor, lower_load_factor, array of hash list pointer, 
    // and the hash list object the pointer points to
    _size = other._size;
    _capacity = other._capacity;
    _upper_load_factor = other._upper_load_factor;
    _lower_load_factor = other._lower_load_factor;
    _head = new hash_list<K, V>[_capacity];

    // copy list
    for (size_t i = 0; i < _capacity; i++) {
        _head[i] = other._head[i];
    }
}

/**
    * @brief Constructs a new hash map from other
    *
    * @param other
    *  The map to create a copy of
    * @return hash_map&
    *  Returns a reference to the newly constructed hash map. This ensures that
    *  a = b = c works
    */
template <typename K, typename V>
hash_map<K, V>& hash_map<K, V>::operator=(const hash_map &other){
    size_t i;
    if(this == &other) // Special case: handle self-test
        return *this;
    i = 0;
    // Remove the old data
    delete[] _head;
    // initialize _size, _capacity, and _head
    _size = other._size;
    _capacity = other._capacity;
    _head = new hash_list<K,V>[_capacity];
    
    // copy list
    for (i = 0; i < _capacity; i++) {
        _head[i] = other._head[i];
    }
    return *this;

}

/**
    * @brief Insert the key/value pair into the map. If the specified key already exists
    * in the map update the associated value, otherwise insert a new key value pair
    *
    * @param key
    *  The key to insert
    * @param value
    *  The value to insert
    */
template <typename K, typename V>
void hash_map<K, V>::insert(K key, V value){
    size_t idx;
    int need;
    // Calculate the hash index
    idx = _hash ( key ) % _capacity ;
    if(_head[idx].get_value(key))
        //There is already a key in hash list
        _head[idx].insert(key, value);
    else{
        //Insert new key
        _head[idx].insert(key, value);
        _size++;
    }
    need = need_to_rehash(); // Check whether there is need to rehash
    rehash(need); // Rehash
}

/**
    * @brief Return an optional containing the value associated with the specified key.
    * If the key isn't in the map return an empty optional.
    *
    * @param key
    *  The key to search for
    * @return
    *  An empty optional (if the key isn't in the map), otherwise return an optional
    *  containing the value associated with the specified key
    */
template <typename K, typename V>
std::optional<V> hash_map<K, V>::get_value(K key) const{
    size_t idx;
    // Calculate the hash index
    idx = _hash(key) % _capacity;
    return (_head[idx].get_value(key));
}


/**
    * @brief Remove the key and corresponding value from the map and return true.
    * If the key isn't in the map return false.
    *
    * @param key
    *  The key to remove from the list
    * @return
    *  True if key was present
    *  False otherwise
    */
template <typename K, typename V>
bool hash_map<K, V>::remove(K key){
    // Calculate the hash index
    size_t index =  _hash(key) % _capacity;
    bool removed;
    // remove the specific key of the specific index
    if (_head[index].remove(key)) {
        removed = true;

        //decrease the number of key/value pairs in the map
        _size--;
    } else 
        removed = false;
    
    return removed;
}

/**
    * @brief Return the number of key/value pairs in the map
    */
template <typename K, typename V>
size_t hash_map<K, V>:: get_size() const{
    return _size;
}

/**
    * @brief Returns the capacity of the map
    *
    * @return
    *  The capacity of the hash map
    */
template <typename K, typename V>
size_t hash_map<K, V>::get_capacity() const{
    return _capacity;
}

/**
    * @brief Copies all the keys from the hash_map into the specified array
    *
    * @param keys
    *  A pointer to an array that has enough space to store all the keys
    *  in the hash_map.
    */
template <typename K, typename V>
void hash_map<K, V>:: get_all_keys(K *keys){    
    int curr = 0;

    for(size_t i = 0; i <  _capacity; i++){
        // go through every index
        _head[i].reset_iter();

        while(1){
            // get the key
            if(_head[i].get_iter_value() != std::nullopt){
                // set up keys array
                K key = *_head[i].get_iter_value().value().first;
                keys[curr] = key;
                curr += 1;
            }
            // increase iterator
            _head[i].increment_iter();
            // check if this is the last
            if(_head[i].iter_at_end())
                break;
        }

    }
}


/**
    * @brief Copies all the keys from the hash_map into the specified array
    * and sorts the array by key value. The smallest key value should be at the
    * front of the array, and the largest key value should be at the end of the
    * array
    *
    * @param keys
    *  A pointer to an array that has enough space to store all the keys
    *  in the hash_map.
    */
template <typename K, typename V>
void hash_map<K ,V>::get_all_sorted_keys(K *keys){
    int curr = 0;
    size_t j;
    size_t i;
    K temp;
    for(i = 0; i <  _capacity; i++){
        // go through every index
        _head[i].reset_iter();
        while(1){
            // get the key
            if(_head[i].get_iter_value() != std::nullopt){
                // set up keys array
                K key = *_head[i].get_iter_value().value().first;
                keys[curr] = key;
                for(j = curr; j > 0; j--){ // Insertion sort
                    if(keys[j] < keys[j-1]){
                        temp = keys[j];
                        keys[j] = keys[j-1];
                        keys[j-1] = temp;
                    }
                }
                curr += 1;
            }
            // increase iterator
            _head[i].increment_iter();
            // check if this is the last
            if(_head[i].iter_at_end())
                break;
        }

    }
}

/**
    * @brief Get the number of elements in each hash_list pointed to by _head.
    * So buckets[0] should be the number of elements in the hash list at index 0
    *    buckets[1] should be the number of elements in the hash list at index 1
    *    etc
    * In order for this to work you MUST use the hash function that we specified in the
    * handout. To remind you again here, the hash function is simply the absolute value of the
    * key
    *
    * @param buckets
    *  A pointer to an array that has at least _capacity elements
    */
// Alan
template <typename K, typename V>
void hash_map<K, V>:: get_bucket_sizes(size_t *buckets){
    size_t i;
    for(i = 0; i < _capacity; i++){
        //go through the array og hash_list and get the size of hash_list
        buckets[i] = _head[i].get_size();
    }
}

template <typename K, typename V>
int hash_map<K, V>::need_to_rehash(){
    int need; // 0: no need, -1: need to decrease, 1: need to expand
    if(_size > _upper_load_factor*_capacity)
        need = 1;
    else if(_size < _lower_load_factor*_capacity)
        need = -1;
    else
        need = 0;
    return need;
}

template <typename K, typename V>
void hash_map<K, V>::rehash(int need){
    std::optional<std::pair<const K *, V *>> node_values;
    size_t newcap;
    size_t idx;
    hash_list<K, V> *temp;
    if(need == 0) // There is no need
        return;
    else if(need == 1){ // Increase the size
        if(_capacity >= _capacities[2]) // If the capacity reach the maximum capacity, there is no need expand
            return;
        else if(_capacity >= _capacities[1]){ // Expand the capacity to _capacities[2]
            temp = new hash_list<K, V>[_capacities[2]];
            newcap = _capacities[2];
        }
        else if(_capacity >= _capacities[0]){ // Expand the capacity to _capacities[1]
            temp = new hash_list<K, V>[_capacities[1]];
            newcap = _capacities[1];
        }
        else{ // Expand the capacity to _capacities[0]
            temp = new hash_list<K, V>[_capacities[0]];
            newcap = _capacities[0];
        }
    }
    else if(need == -1){ // Decrease the size
        if(_capacity > _capacities[2]){ // Decrease the capacity to _capacities[2]
            temp = new hash_list<K, V>[_capacities[2]];
            newcap = _capacities[2];
        } 
        else if(_capacity > _capacities[1]){ // Decrease the capacity to _capacities[1]
            temp = new hash_list<K, V>[_capacities[1]];
            newcap = _capacities[1];
        }
        else if(_capacity > _capacities[0]){ // Decrease the capacity to _capacities[0]
            temp = new hash_list<K, V>[_capacities[0]];
            newcap = _capacities[0];
        }
        else{ // If the capacity reach the minimum capacity, there is no need expand
           return;
        }
    }
    else // Error
        return;
    //Rehash
    for(size_t i = 0; i < _capacity; i++){
        _head[i].reset_iter();
        while(!_head[i].iter_at_end()){
            node_values = _head[i].get_iter_value();
            idx = _hash ( *node_values.value().first ) % newcap ; // Calculate new hash index
            temp[idx].insert(*node_values.value().first, *node_values.value().second);
            _head[i].increment_iter();
        }
    }
    _capacity = newcap;
    delete[] _head;
    _head = temp;
    return;
}



/**
    * @brief Frees all memory associated with the map
    */
template <typename K, typename V>
hash_map<K, V>::~hash_map(){
    delete[] _head;
}

