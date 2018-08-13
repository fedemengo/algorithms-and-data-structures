
#include <iostream>
#include <vector>
#include <unordered_map>
#include <functional>
#include "../binary_heap/binary_heap.hpp"

/**
 * Priority queue implementation based on binary heap
 *
 **/

template <typename KEY, typename DATA>
class priority_queue : private binary_heap<KEY, DATA> {
public:
	priority_queue(std::function<bool(KEY, KEY)> cmp) : binary_heap<KEY, DATA>(cmp) {}

	void update_priority(KEY new_key, DATA data){
		binary_heap<KEY, DATA>::update_key(new_key, data);
	}

	void push(KEY key, DATA data){
		binary_heap<KEY, DATA>::push(key, data);
	}

	std::pair<KEY, DATA> top(){ 
		return binary_heap<KEY, DATA>::top();
	}

	void pop(){
		binary_heap<KEY, DATA>::pop();
	}

	int size() { 
		return binary_heap<KEY, DATA>::size();
	}
};
