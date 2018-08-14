#include "fibonacci_heap.hpp"
#include <exception>

void test_extract(fibonacci_heap<int, std::string> &h, int k, std::string v) {
	auto x = h.get();
	h.remove();

	if(x.first != k){
		throw std::invalid_argument("Expected key " + std::to_string(k) + " but got " + std::to_string(x.first));
	}
	if(x.second != v){
		throw std::invalid_argument("Expected value " + v + " but got " + x.second);
	}
}

int main(int argc, char const *argv[]) {

	// min heap
	fibonacci_heap<int, std::string> F1([](int k1, int k2){ return k1 < k2;});
	fibonacci_heap<int, std::string> F2([](int k1, int k2){ return k1 < k2;});
	fibonacci_heap<int, std::string> F3([](int k1, int k2){ return k1 < k2;});
	fibonacci_heap<int, std::string> F4([](int k1, int k2){ return k1 > k2;});

	try {
		F1.insert(1, "hello");
		F2.insert(3, "dope");
		F1.insert(6, "wow");
		F2.insert(-10, "awesome");

		F3.insert(0, "a");	
		F3.insert(11, "z");
		F3.insert(2, "x");
		F3.insert(3, "w");
		F3.insert(5, "c");
		F3.insert(7, "h");
		F3.insert(11, "f");
		F3.insert(13, "n");

		F1.merge(F2);

		F3.update_key(-3, "w");
		F3.update_key(4, "f");
		F3.update_key(-1, "z");

		F3.merge(F1);

		test_extract(F3, -10, "awesome");
		test_extract(F3, -3, "w");
		test_extract(F3, -1, "z");
		test_extract(F3, 0, "a");
		test_extract(F3, 1, "hello");
		test_extract(F3, 2, "x");
		test_extract(F3, 3, "dope");
		test_extract(F3, 4, "f");
		test_extract(F3, 5, "c");
		test_extract(F3, 6, "wow");
		test_extract(F3, 7, "h");
		test_extract(F3, 13, "n");

		F4.insert(-100, "test");
		F4.update_key(1000000, "test");

		int SIZE = 100000;
		for(int i=0; i<SIZE; ++i){
			F3.insert(i, std::to_string(i) + "min");
			F4.insert(i, std::to_string(i) + "max");
		}

		test_extract(F4, 1000000, "test");

		int i = 0;
		while(F4.size()){
			test_extract(F3, i, std::to_string(i) + "min");
			test_extract(F4, SIZE-1-i, std::to_string(SIZE-1-i) + "max");
			++i;
		}

		std::cout << "OK" << std::endl;
	} catch (std::exception &e) {
		std::cout << "ERROR" << std::endl;
		std::cout << e.what() << std::endl;
	}
	
	return 0;
}
