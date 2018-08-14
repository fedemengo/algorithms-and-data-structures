#include "binary_heap.hpp"
#include <gtest/gtest.h>
#include <algorithm>

const int SIZE = 100000;
std::vector<std::pair<int, std::string>> values;

std::pair<int, std::string> TopAndPop(binary_heap<int, std::string> &h){
	std::pair<int, std::string> x = h.top();
	h.pop();
	return x;
}

// Instanciate obj inside test
TEST(max_binary_heap_Test, PushPop) { 
	binary_heap<int, std::string> max_heap([](int k1, int k2){ return k1 > k2;});
	
	for(auto &p: values)
		max_heap.push(p.first, p.second);

	for(int i=0; i<values.size(); ++i)
    	ASSERT_EQ(values[values.size()-i-1], TopAndPop(max_heap));
}

struct min_binary_heap_Test : testing::Test {
	binary_heap<int, std::string> *heap;

	min_binary_heap_Test(){
		heap = new binary_heap<int, std::string>([](int k1, int k2){ return k1 < k2;});
	}
};

std::pair<int, std::string> GetIndex(binary_heap<int, std::string> &h, int index){
	return h[index];
}

TEST_F(min_binary_heap_Test, PushPop) {

	for(auto &p: values)
		heap->push(p.first, p.second);

	for(auto &p: values)
    	ASSERT_EQ(p, TopAndPop(*heap));
}

TEST_F(min_binary_heap_Test, Heapsort) {
	std::vector<std::pair<int, std::string>> v;
	
	for(int i=0; i<SIZE; ++i){
		int key = rand() % (SIZE * 100) + 1;
		std::string str = "data" + std::to_string(key);
		v.push_back({key, str});
		heap->push(key, str);
	}

	sort(v.begin(), v.end(), std::greater<std::pair<int, std::string>>());
	heap->heap_sort();

	for(int i=0; i<heap->length(); ++i){
		std::pair<int, std::string> x = GetIndex(*heap, i);
		ASSERT_EQ(v[i], x);
	}
}

TEST_F(min_binary_heap_Test, PushPopAfterHeapSort) {

	for(auto &p: values)
		heap->push(p.first, p.second);

	for(auto &p: values)
    	ASSERT_EQ(p, TopAndPop(*heap));
}

int main(int argc, char **argv) {

	srand(time(0));
	for(int i=0; i<SIZE; i++){
		int key = rand() % (SIZE * 100) + 1;
		std::string str = "data" + std::to_string(key);
		values.push_back({key, str});
	}
	std::sort(values.begin(), values.end());
	
	testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
