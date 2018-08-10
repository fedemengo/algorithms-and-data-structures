#include "binary_heap.hpp"
#include <exception>

void test_pop(heap<int, std::string> &h, int k, std::string v) {
	auto x = h.top();
	h.pop();

	if(x.first != k){
		throw std::invalid_argument("Expected key " + std::to_string(k) + " but got " + std::to_string(x.first));
	}
	if(x.second != v){
		throw std::invalid_argument("Expected value " + v + " but got " + x.second);
	}
}

int main(int argc, char const *argv[]) {

	heap<int, std::string> max_heap([](int k1, int k2){ return k1 > k2;});
	heap<int, std::string> min_heap([](int k1, int k2){ return k1 < k2;});

	try {
		max_heap.push(0, "a");	
		max_heap.push(1, "z");
		max_heap.push(2, "x");
		max_heap.push(3, "w");
		max_heap.push(5, "c");
		max_heap.push(7, "h");
		max_heap.push(11, "f");
		max_heap.push(13, "n");

		min_heap.push(0, "a");	
		min_heap.push(1, "z");
		min_heap.push(2, "x");
		min_heap.push(3, "w");
		min_heap.push(5, "c");
		min_heap.push(7, "h");
		min_heap.push(11, "f");
		min_heap.push(13, "n");

		max_heap.update_key(12, "w");
		max_heap.update_key(8, "a");
		max_heap.update_key(9, "x");

		min_heap.update_key(-3, "w");
		min_heap.update_key(4, "f");
		min_heap.update_key(-1, "z");

		test_pop(max_heap, 13, "n");	
		test_pop(max_heap, 12, "w");
		test_pop(max_heap, 11, "f");
		test_pop(max_heap, 9, "x");
		test_pop(max_heap, 8, "a");
		test_pop(max_heap, 7, "h");
		test_pop(max_heap, 5, "c");
		test_pop(max_heap, 1, "z");
			
		test_pop(min_heap, -3, "w");	
		test_pop(min_heap, -1, "z");
		test_pop(min_heap, 0, "a");
		test_pop(min_heap, 2, "x");
		test_pop(min_heap, 4, "f");
		test_pop(min_heap, 5, "c");
		test_pop(min_heap, 7, "h");
		test_pop(min_heap, 13, "n");

		std::cout << "OK" << std::endl;
	} catch (std::exception &e) {
		std::cout << "ERROR" << std::endl;
		std::cout << e.what() << std::endl;
	}

	return 0;
}

