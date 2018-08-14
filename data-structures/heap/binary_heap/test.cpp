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

	std::vector<std::pair<int, std::string>> x(values);
	std::sort(x.begin(), x.end(), std::greater<std::pair<int, std::string>>());
	
	for(auto &p: x)
    	ASSERT_EQ(p, TopAndPop(max_heap));
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

	std::sort(values.begin(), values.end(), std::greater<std::pair<int, std::string>>());
	for(auto &p: values)
		heap->push(p.first, p.second);

	std::vector<std::pair<int, std::string>> x(values);
	std::sort(x.begin(), x.end());
	for(auto &p: x)
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

	std::sort(v.begin(), v.end(), std::greater<std::pair<int, std::string>>());
	heap->heap_sort();

	for(int i=0; i<heap->length(); ++i){
		std::pair<int, std::string> y = GetIndex(*heap, i);
		ASSERT_EQ(v[i], y);
	}
}

TEST_F(min_binary_heap_Test, PushPopAfterHeapSort) {

	std::vector<std::pair<int, std::string>> x(values);
	std::sort(x.begin(), x.end(), std::greater<std::pair<int, std::string>>());
	for(auto &p: values)
		heap->push(p.first, p.second);
	
	std::sort(x.begin(), x.end());
	for(auto &p: x)
    	ASSERT_EQ(p, TopAndPop(*heap));
}

int main(int argc, char **argv) {

	srand(time(0));
	for(int i=0; i<SIZE; i++){
		int key = rand() % (SIZE * 100) + 1;
		std::string str = "data" + std::to_string(key);
		values.push_back({key, str});
	}
	
	testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
