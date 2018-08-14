#include "binary_heap.hpp"
#include <exception>
#include <algorithm>

void test_pop(binary_heap<int, std::string> &h, int k, std::string v) {
	auto x = h.top();
	h.pop();

	if(x.first != k){
		throw std::invalid_argument("Expected key " + std::to_string(k) + " but got " + std::to_string(x.first));
	}
	if(x.second != v){
		throw std::invalid_argument("Expected value " + v + " but got " + x.second);
	}
}

void test_equal(std::pair<int, std::string> p1, std::pair<int, std::string> p2) {
	int k1 = p1.first, k2 = p2.first;
	std::string v1 = p1.second, v2 = p2.second;
	if(k1 != k2){
		throw std::invalid_argument("Expected key " + std::to_string(k1) + " but got " + std::to_string(k2));
	}
	if(v1 != v2){
		throw std::invalid_argument("Expected value " + v1 + " but got " + v2);
	}
}

int main(int argc, char const *argv[]) {

	binary_heap<int, std::string> max_heap([](int k1, int k2){ return k1 > k2;});
	binary_heap<int, std::string> min_heap([](int k1, int k2){ return k1 < k2;});

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

		test_pop(max_heap, 13, "n");	
		test_pop(max_heap, 11, "f");
		test_pop(max_heap, 7, "h");
		test_pop(max_heap, 5, "c");
		test_pop(max_heap, 3, "w");
		test_pop(max_heap, 2, "x");
		test_pop(max_heap, 1, "z");
		test_pop(max_heap, 0, "a");
			
		test_pop(min_heap, 0, "a");
		test_pop(min_heap, 1, "z");
		test_pop(min_heap, 2, "x");
		test_pop(min_heap, 3, "w");	
		test_pop(min_heap, 5, "c");
		test_pop(min_heap, 7, "h");
		test_pop(min_heap, 11, "f");
		test_pop(min_heap, 13, "n");

		srand(time(0));

		const int SIZE = 1000000;
		std::vector<std::pair<int, std::string>> v, u;
		for(int i=0; i<SIZE; ++i){
			int key = rand() % (SIZE * 100) + 1;
			std::string str = "data" + std::to_string(key);
			v.push_back({key, str});
			min_heap.push(key, str);
		}

		time_t start = clock();
		sort(v.begin(), v.end(), std::greater<std::pair<int, std::string>>());
		std::cout << "Time " << (clock()-start)/(double) CLOCKS_PER_SEC << std::endl;

		start = clock();
		min_heap.heap_sort();
		std::cout << "Time " << (clock()-start)/(double) CLOCKS_PER_SEC << std::endl;

		for(int i=0; i<min_heap.length(); ++i){
			test_equal(v[i], min_heap[i]);
		}

		min_heap.push(0, "a");	
		min_heap.push(1, "z");
		min_heap.push(2, "x");
		min_heap.push(3, "w");
		min_heap.push(5, "c");
		min_heap.push(7, "h");
		min_heap.push(11, "f");
		min_heap.push(13, "n");

		test_pop(min_heap, 0, "a");
		test_pop(min_heap, 1, "z");
		test_pop(min_heap, 2, "x");
		test_pop(min_heap, 3, "w");	
		test_pop(min_heap, 5, "c");
		test_pop(min_heap, 7, "h");
		test_pop(min_heap, 11, "f");
		test_pop(min_heap, 13, "n");

		std::cout << "OK" << std::endl;
	} catch (std::exception &e) {
		std::cout << "ERROR" << std::endl;
		std::cout << e.what() << std::endl;
	}

	return 0;
}
