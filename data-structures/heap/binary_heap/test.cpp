#include "heap.hpp"

int main(int argc, char const *argv[]) {

    heap<int, std::string> H([](int k1, int k2){ return k1 > k2;});

	H.push(0, "awesome");
    H.push(1, "hello");
	H.push(2, "dope");
	H.push(4, "wow");
	H.push(10, "awdacce");
    H.push(11, "h12dd");
	H.push(12, "fferras");
	H.push(14, "norrerg");

	H.update_key(13, "dope");

	while(H.size()) {
		auto x = H.top(); H.pop();
		std::cout << x.second << std::endl;
	}
	
	return 0;
}

