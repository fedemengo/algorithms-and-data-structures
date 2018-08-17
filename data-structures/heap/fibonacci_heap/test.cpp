#include "fibonacci_heap.hpp"
#include <gtest/gtest.h>

std::pair<int, std::string> GetAndRemove(fibonacci_heap<int, std::string> &h){
	std::pair<int, std::string> x = h.get();
	h.remove();
	return x;
}

struct min_fibonacci_heap_Test : testing::Test {
	
	const int SIZE = 100000;
	fibonacci_heap<int, std::string> *heap;
	std::vector<std::pair<int, std::string>> v1, v2, v3, v;

	min_fibonacci_heap_Test(){
		heap = new fibonacci_heap<int, std::string>([](int k1, int k2){ return k1 < k2;});
	}

	void SetUp() {
		srand(time(0));
		for(int i=0; i<SIZE; i++){
			int key = rand() % (SIZE * 100) + 1;
			std::string str = "data" + std::to_string(key);
			v1.push_back({key, str});
			v.push_back({key, str});
		}
		for(int i=0; i<SIZE; i++){
			int key = rand() % (SIZE * 100) + 1;
			std::string str = "data" + std::to_string(key);
			v2.push_back({key, str});
			v.push_back({key, str});
		}
		for(int i=0; i<SIZE; i++){
			int key = rand() % (SIZE * 100) + 1;
			std::string str = "data" + std::to_string(key);
			v3.push_back({key, str});
			v.push_back({key, str});
		}
		std::sort(v.begin(), v.end());
	}
};

TEST_F(min_fibonacci_heap_Test, Insert) {

	std::set<int> s;
	for(auto &p: v1) {
		heap->insert(p.first, p.second);
		s.insert(p.first);
		ASSERT_EQ(*s.begin(), heap->get().first);
	}
}

TEST_F(min_fibonacci_heap_Test, Remove) {

	for(auto &p: v1)
		heap->insert(p.first, p.second);

	std::sort(v1.begin(), v1.end());
	for(auto &p: v1)
    	ASSERT_EQ(p, GetAndRemove(*heap));
}

TEST_F(min_fibonacci_heap_Test, Merge) {

	fibonacci_heap<int, std::string> F2([](int k1, int k2){ return k1 < k2;});
	fibonacci_heap<int, std::string> F3([](int k1, int k2){ return k1 < k2;});

	for(auto &p: v1)
		heap->insert(p.first, p.second);
	
	for(auto &p: v2)
		F2.insert(p.first, p.second);

	for(auto &p: v3)
		F3.insert(p.first, p.second);

	heap->merge(F2);
	F3.merge(*heap);

	for(auto &p: v)
		ASSERT_EQ(p, GetAndRemove(F3));
}

struct max_fibonacci_heap_Test : testing::Test {
	using ull = unsigned long long int;
	const int SIZE = 100000;
	const int A_PRIME = 105943;
	fibonacci_heap<ull, std::string> *heap;
	std::set<std::pair<ull, std::string>, std::greater<std::pair<ull, std::string>>> s;

	max_fibonacci_heap_Test(){
		heap = new fibonacci_heap<ull, std::string>([](ull k1, ull k2){ return k1 > k2;});
	}

	void SetUp() {
		for(int i=0; i<SIZE; ++i){
			s.insert({i*3, "data" + std::to_string(i*3)});
			heap->insert(i*3, "data" + std::to_string(i*3));
		}
	}
};

TEST_F(max_fibonacci_heap_Test, UpdateKey) {

	int upds = SIZE / 2;
	while(upds){
		ull k = rand() % SIZE;

		std::set<std::pair<ull, std::string>>::iterator it;
		it = s.find({k*3, "data" + std::to_string(k*3)});

		if(it != s.end()){
			ull k1 = it->first;
			std::string v = it->second;
			s.erase(it);
			s.insert({k1*A_PRIME, v});
			
			heap->update_key(k1*A_PRIME, v);
			upds--;
		}
	}

	while(s.size()){
		std::pair<ull, std::string> p = *s.begin();
		s.erase(s.begin());
	
		std::pair<ull, std::string> x = heap->get();
		heap->remove();
		ASSERT_EQ(p, x);
	}
}

int main(int argc, char *argv[]) {
	testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
