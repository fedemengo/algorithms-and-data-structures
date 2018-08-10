#include "priority_queue.hpp"
#include <exception>

void test_pop(priority_queue<int, std::string> &h, int k, std::string v) {
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

	priority_queue<int, std::string> max_pq([](int k1, int k2){ return k1 > k2;});
	priority_queue<int, std::string> min_pq([](int k1, int k2){ return k1 < k2;});

	try {
		max_pq.push(0, "a");	
		max_pq.push(1, "z");
		max_pq.push(2, "x");
		max_pq.push(3, "w");
		max_pq.push(5, "c");
		max_pq.push(7, "h");
		max_pq.push(11, "f");
		max_pq.push(13, "n");

		min_pq.push(0, "a");	
		min_pq.push(1, "z");
		min_pq.push(2, "x");
		min_pq.push(3, "w");
		min_pq.push(5, "c");
		min_pq.push(7, "h");
		min_pq.push(11, "f");
		min_pq.push(13, "n");

		max_pq.update_priority(12, "w");
		max_pq.update_priority(8, "a");
		max_pq.update_priority(9, "x");

		min_pq.update_priority(-3, "w");
		min_pq.update_priority(4, "f");
		min_pq.update_priority(-1, "z");

		test_pop(max_pq, 13, "n");	
		test_pop(max_pq, 12, "w");
		test_pop(max_pq, 11, "f");
		test_pop(max_pq, 9, "x");
		test_pop(max_pq, 8, "a");
		test_pop(max_pq, 7, "h");
		test_pop(max_pq, 5, "c");
		test_pop(max_pq, 1, "z");
			
		test_pop(min_pq, -3, "w");	
		test_pop(min_pq, -1, "z");
		test_pop(min_pq, 0, "a");
		test_pop(min_pq, 2, "x");
		test_pop(min_pq, 4, "f");
		test_pop(min_pq, 5, "c");
		test_pop(min_pq, 7, "h");
		test_pop(min_pq, 13, "n");

		std::cout << "OK" << std::endl;
	} catch (std::exception &e) {
		std::cout << "ERROR" << std::endl;
		std::cout << e.what() << std::endl;
	}

	return 0;
}
