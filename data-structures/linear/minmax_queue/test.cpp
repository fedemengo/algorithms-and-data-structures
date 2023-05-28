
#include "minmax_queue.hpp"
#include <gtest/gtest.h>

const int SIZE = 100000;

struct min_queue_Test : testing::Test {
	minmax_queue<int> *min_queue;
	std::set<int> *v;
	std::set<int> *s;

	min_queue_Test() {
		min_queue = new minmax_queue<int>([](int k1, int k2){ return k1 < k2;});
		v = new std::set<int>();
		s = new std::set<int>();
	}

	void SetUp(){
		srand(time(0));
		for(int i=0; i<SIZE; i++){
			int x = rand() % (SIZE * 100);
			v->insert(x);
		}
	}
};

TEST_F(min_queue_Test, Push) { 
	
	for(int x: *v){
		min_queue->push(x);
		s->insert(x);
		ASSERT_EQ(*(s->begin()), min_queue->minmax());
	}
}

TEST_F(min_queue_Test, Pop) {

	for(int x: *v){
		min_queue->push(x);
		s->insert(x);
		ASSERT_EQ(*(s->begin()), min_queue->minmax());
	}

	for(int x: *v){
		ASSERT_EQ(*(s->begin()), min_queue->minmax());
		min_queue->pop();
		s->erase(s->find(x));
	}
}

struct max_queue_Test : testing::Test {
	minmax_queue<int> *min_queue;
	std::set<int, std::greater<int>> *v;
	std::set<int, std::greater<int>> *s;

	max_queue_Test() {
		min_queue = new minmax_queue<int>([](int k1, int k2){ return k1 > k2;});
		v = new std::set<int, std::greater<int>>();
		s = new std::set<int, std::greater<int>>();
	}

	void SetUp(){
		srand(time(0));
		for(int i=0; i<SIZE; i++){
			int x = rand() % (SIZE * 100);
			v->insert(x);
		}
	}
};

TEST_F(max_queue_Test, Push) { 
	
	for(int x: *v){
		min_queue->push(x);
		s->insert(x);
		ASSERT_EQ(*(s->begin()), min_queue->minmax());
	}
}

TEST_F(max_queue_Test, Pop) {

	for(int x: *v){
		min_queue->push(x);
		s->insert(x);
		ASSERT_EQ(*(s->begin()), min_queue->minmax());
	}

	for(int x: *v){
		ASSERT_EQ(*(s->begin()), min_queue->minmax());
		min_queue->pop();
		s->erase(s->find(x));
	}
}

