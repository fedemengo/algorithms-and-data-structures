#include "fibonacci_heap.hpp"
#include <gtest/gtest.h>

const int SIZE = 10000;
std::vector<std::pair<int, std::string>> vx, v1, v2, v3, v;

std::pair<int, std::string> GetAndRemove(fibonacci_heap<int, std::string> &h){
	std::pair<int, std::string> x = h.get();
	h.remove();
	return x;
}

struct min_fibonacci_heap_Test : testing::Test {
	fibonacci_heap<int, std::string> *heap;

	min_fibonacci_heap_Test(){
		heap = new fibonacci_heap<int, std::string>([](int k1, int k2){ return k1 < k2;});
	}
};

struct max_fibonacci_heap_Test : testing::Test {
	fibonacci_heap<unsigned long long int, std::string> *heap;

	max_fibonacci_heap_Test(){
		heap = new fibonacci_heap<unsigned long long int, std::string>([](unsigned long long int k1, unsigned long long int k2){ return k1 > k2;});
	}
};

TEST_F(min_fibonacci_heap_Test, InsertRemove) {

	for(auto &p: vx)
		heap->insert(p.first, p.second);

	std::sort(vx.begin(), vx.end());
	for(auto &p: vx)
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

TEST_F(max_fibonacci_heap_Test, UpdateKey) {

	std::set<std::pair<unsigned long long int, std::string>, std::greater<std::pair<unsigned long long int, std::string>>> s;
	for(int i=0; i<SIZE; ++i){
		s.insert({i*3, "data" + std::to_string(i*3)});
		heap->insert(i*3, "data" + std::to_string(i*3));
	}

	int upds = SIZE / 2;

	while(upds){
		unsigned long long int k = rand() % SIZE;

		std::set<std::pair<unsigned long long int, std::string>>::iterator it;
		it = s.find({k*3, "data" + std::to_string(k*3)});

		if(it != s.end()){
			unsigned long long int k1 = it->first;
			std::string v = it->second;
			s.erase(it);
			s.insert({k1*105943, v});
			
			heap->update_key(k1*105943, v);
			upds--;
		}
	}


	while(s.size()){
		std::pair<unsigned long long int, std::string> p = *s.begin();
		s.erase(s.begin());
		ASSERT_EQ(s.size(), heap->size()-1);
		std::pair<unsigned long long int, std::string> x = heap->get();
		heap->remove();
		EXPECT_EQ(p, x);
	}
}

int main(int argc, char *argv[]) {

	srand(time(0));
	for(int i=0; i<SIZE; i++){
		int key = rand() % (SIZE * 100) + 1;
		std::string str = "data" + std::to_string(key);
		v1.push_back({key, str});
		vx.push_back({key, str});
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

	testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
