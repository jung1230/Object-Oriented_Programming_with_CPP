#include <iostream>
#include "hash_list.h"

using std::cout;
using std::endl;

// function prototypes
void t_constructor(void);
void t_iter_multiple_nodes(void);

// test harness
int unittest_main(){
  // invoke unit tests as separate functions
  //cout << "start unittest\n----------------------------------------------------" << endl;
  t_constructor();
  t_iter_multiple_nodes();

  return 0;
}

void t_constructor(void) {
  // arrange
  hash_list list;

  // act
  // in this simple case there is nothing more to do

  // assert
  if(list.get_size() != 0) {
    cout << "t_constructor: invalid size" << endl;
    // generally for unit testing don't abort execution
    // so the rest of your test suite can continue      
  }
}

void t_iter_multiple_nodes(void) {
  // --- arrange ---
  // create empty list; populate with values; reset iterator
  hash_list list;
  list.insert(7,70);
  list.insert(8,80);
  list.insert(9,90);
  list.reset_iter();

  // --- act ---
  // iterate through the loop
  while (!list.iter_at_end()) {
    // Get pointers to key/value pairs
    std::optional<std::pair<const int *, float *>> node_value = list.get_iter_value();
        
    // output node
    cout << "key: " << *node_value.value().first
	 << ", value: " << *node_value.value().second << endl;

    // go to next element
    list.increment_iter();
  }
  // --- assert ---
  // in this example, verification is by visual inspection because 
  // the order nodes are printed depends on your implementation
}
