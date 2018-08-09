#include "fibo.hpp"

int main(int argc, char const *argv[]) {

    fibonacci_heap<int, std::string> F1({}), F2({});

    F1.insert(1, "hello");
	F2.insert(2, "dope");
	F1.insert(4, "wow");
	F2.insert(0, "awesome");

	F1.merge(F2);

	while(F1.size()) {
		auto x = F1.extract_min();
		std::cout << x.second << std::endl;
	}
	
	return 0;
}
