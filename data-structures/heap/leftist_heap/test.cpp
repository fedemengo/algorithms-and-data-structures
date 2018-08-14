#include "leftist_heap.hpp"
#include <exception>
#include<set>
#include<vector>

void test_pop(leftist_heap<int, std::string> &h, int k, std::string v) {
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

	leftist_heap<int, std::string> max_heap([](int k1, int k2){ return k1 > k2;});
	leftist_heap<int, std::string> min_heap([](int k1, int k2){ return k1 < k2;});
	leftist_heap<int, std::string> lh([](int k1, int k2){ return k1 < k2;});
	leftist_heap<int, std::string> l2([](int k1, int k2){ return k1 < k2;});

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

		std::set<int> s;
		std::vector<int> v, u;
		const int SIZE = 1000000;
		for(int i=0; i<2*SIZE; i++){
			int key = rand() % SIZE * 100 + 1;
			if(s.count(key) == 0){
				s.insert(key);
				v.push_back(key);
			}
		}

		while(s.size()){
			int min = *(s.begin());
			s.erase(s.begin());
			u.push_back(min);
			//std::cout << min << std::endl;
		}

		//time_t start = clock();
		int half = v.size()/2;
		for(int i=0; i<half; i++){
			lh.push(v[i], "data" + std::to_string(v[i]));
		}

		for(int i=half; i<v.size(); i++){
			l2.push(v[i], "data" + std::to_string(v[i]));
		}

		lh.merge(l2);

		int i = 0;
		while(lh.size()){
			test_pop(lh, u[i], "data" + std::to_string(u[i]));
			i++;
		}

		//std::cout << "Time " << (clock()-start)/(double) CLOCKS_PER_SEC << std::endl;

		std::cout << "OK" << std::endl;
	} catch (std::exception &e) {
		std::cout << "ERROR" << std::endl;
		std::cout << e.what() << std::endl;
	}

	return 0;
}
