#include "hash_map.h"
/**-----------------------------------------------------------------------------------
* START Part 1
*------------------------------------------------------------------------------------*/
/**
    * @brief Construct a new hash map object
    */
hash_map::hash_map(size_t capacity){

    // initialize _size, _capacity, and _head
    _size = 0;
    _capacity = capacity;
    _head = new hash_list[capacity];

}

/**
    * @brief Construct a new hash map object
    *
    * @param other
    *  The map to create a copy of
    */
hash_map::hash_map(const hash_map &other) {
    // initialize _size, _capacity, and _head
    _size = other._size;
    _capacity = other._capacity;
    _head = new hash_list[_capacity];
    
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
hash_map &hash_map::operator=(const hash_map &other){
    size_t i;
    if(this == &other) // Special case: handle self-test
        return *this;
    i = 0;
    // Remove the old data
    delete[] _head;
    // initialize _size, _capacity, and _head
    _size = other._size;
    _capacity = other._capacity;
    _head = new hash_list[_capacity];
    
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
void hash_map::insert(int key, float value){
    int idx;
    // Calculate the hash index
    idx = std::abs(key) % _capacity; 
    _head[idx].insert(key, value);
    _size++;
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
std::optional<float> hash_map::get_value(int key) const{
    int idx;
    // Calculate the hash index
    idx = std::abs(key) % _capacity;
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
bool hash_map::remove(int key){
    // Calculate the hash index
    size_t index = std::abs(key) % _capacity; 
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
size_t hash_map::get_size() const{
    return _size;
}

/**
    * @brief Returns the capacity of the map
    *
    * @return
    *  The capacity of the hash map
    */
size_t hash_map::get_capacity() const{
    return _capacity;
}

/**
    * @brief Copies all the keys from the hash_map into the specified array
    *
    * @param keys
    *  A pointer to an array that has enough space to store all the keys
    *  in the hash_map.
    */
void hash_map::get_all_keys(int *keys){
    int curr = 0;

    for(size_t i = 0; i <  _capacity; i++){
        // go through every index
        _head[i].reset_iter();

        while(1){
            // get the key
            if(_head[i].get_iter_value() != std::nullopt){
                // set up keys array
                int key = *_head[i].get_iter_value().value().first;
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
void hash_map::get_bucket_sizes(size_t *buckets){
    size_t i;
    for(i = 0; i < _capacity; i++){
        //go through the array og hash_list and get the size of hash_list
        buckets[i] = _head[i].get_size();
    }
}

/**
    * @brief Frees all memory associated with the map
    */
hash_map::~hash_map() {
    // destructor
    delete[] _head; 
}


/**-----------------------------------------------------------------------------------
* END Part 1
*------------------------------------------------------------------------------------*/


