#include "priority_queue.hpp"
#include <gtest/gtest.h>
#include <algorithm>

const int SIZE = 100000;
std::vector<std::pair<unsigned long long int, std::string>> values;

std::pair<unsigned long long int, std::string> TopAndPop(priority_queue<unsigned long long int, std::string> &h){
	std::pair<unsigned long long int, std::string> x = h.top();
	h.pop();
	return x;
}

struct max_priority_queue_Test : testing::Test {
	priority_queue<unsigned long long int, std::string> *heap;

	max_priority_queue_Test(){
		heap = new priority_queue<unsigned long long int, std::string>([](unsigned long long int k1, unsigned long long int k2){ return k1 > k2;});
	}
};

// Instanciate obj inside test
TEST_F(max_priority_queue_Test, PushPop) { 
	
	for(auto &p: values)
		heap->push(p.first, p.second);

	std::vector<std::pair<unsigned long long int, std::string>> x(values);
	std::sort(x.begin(), x.end(), std::greater<std::pair<unsigned long long int, std::string>>());
	
	for(auto &p: x)
    	ASSERT_EQ(p, TopAndPop(*heap));
}

TEST_F(max_priority_queue_Test, UpdateKey) {

	std::set<std::pair<unsigned long long int, std::string>, std::greater<std::pair<unsigned long long int, std::string>>> s;
	for(int i=0; i<SIZE; ++i){
		s.insert({i*3, "data" + std::to_string(i*3)});
		heap->push(i*3, "data" + std::to_string(i*3));
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
			
			heap->update_priority(k1*105943, v);
			upds--;
		}
	}

	while(s.size()){
		std::pair<unsigned long long int, std::string> p = *s.begin();
		s.erase(s.begin());
		EXPECT_EQ(p, TopAndPop(*heap));
	}
}

TEST(min_priority_queue_Test, PushPop) {
	priority_queue<unsigned long long int, std::string> min_heap([](unsigned long long int k1, unsigned long long int k2){ return k1 < k2;});

	std::sort(values.begin(), values.end());
	for(auto &p: values)
		min_heap.push(p.first, p.second);

	std::vector<std::pair<unsigned long long int, std::string>> x(values);
	std::sort(x.begin(), x.end());
	for(auto &p: x)
    	ASSERT_EQ(p, TopAndPop(min_heap));
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
