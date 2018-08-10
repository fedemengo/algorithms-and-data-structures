#include "fibonacci_heap.hpp"
#include <exception>

void test_extract(fibonacci_heap<int, std::string> &h, int k, std::string v) {
	auto x = h.extract_min();

	if(x.first != k){
		throw std::invalid_argument("Expected key " + std::to_string(k) + " but got " + std::to_string(x.first));
	}
	if(x.second != v){
		throw std::invalid_argument("Expected value " + v + " but got " + x.second);
	}
}

int main(int argc, char const *argv[]) {

    fibonacci_heap<int, std::string> F1({}), F2({}), F3({});

	try {
		F1.insert(1, "hello");
		F2.insert(2, "dope");
		F1.insert(4, "wow");
		F2.insert(0, "awesome");

		F3.insert(0, "a");	
		F3.insert(11, "z");
		F3.insert(2, "x");
		F3.insert(3, "w");
		F3.insert(5, "c");
		F3.insert(7, "h");
		F3.insert(11, "f");
		F3.insert(13, "n");

		F1.merge(F2);

		test_extract(F1, 0, "awesome");
		test_extract(F1, 1, "hello");
		test_extract(F1, 2, "dope");
		test_extract(F1, 4, "wow");

		F3.decrease_key(-3, "w");
		F3.decrease_key(4, "f");
		F3.decrease_key(-1, "z");

		test_extract(F3, -3, "w");
		test_extract(F3, -1, "z");
		test_extract(F3, 0, "a");
		test_extract(F3, 2, "x");
		test_extract(F3, 4, "f");
		test_extract(F3, 5, "c");
		test_extract(F3, 7, "h");
		test_extract(F3, 13, "n");

		std::cout << "OK" << std::endl;
	} catch (std::exception &e) {
		std::cout << "ERROR" << std::endl;
		std::cout << e.what() << std::endl;
	}
	
	return 0;
}
