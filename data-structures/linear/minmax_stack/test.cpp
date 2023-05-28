#include "minmax_stack.hpp"
#include <gtest/gtest.h>

const int SIZE = 100000;

struct min_stack_Test : testing::Test {
	minmax_stack<int> *min_stack;
	std::vector<int> *v;
	std::multiset<int> *s;

	min_stack_Test() {
		min_stack = new minmax_stack<int>([](int k1, int k2){ return k1 < k2;});
		v = new std::vector<int>();
		s = new std::multiset<int>();
	}

	void SetUp(){
		srand(time(0));
		for(int i=0; i<SIZE; i++){
			int x = rand() % (SIZE * 100);
			v->push_back(x);
		}
	}
};

TEST_F(min_stack_Test, Push) { 
	
	for(int x: *v){
		min_stack->push(x);
		s->insert(x);
		ASSERT_EQ(*(s->begin()), min_stack->minmax());
	}
}

TEST_F(min_stack_Test, Pop) {

	for(int x: *v){
		min_stack->push(x);
		s->insert(x);
		ASSERT_EQ(*(s->begin()), min_stack->minmax());
	}

	for(int i=v->size()-1; i>-1; --i){
		ASSERT_EQ(*(s->begin()), min_stack->minmax());
		min_stack->pop();
		s->erase(s->find((*v)[i]));
	}
}

struct max_stack_Test : testing::Test {
	minmax_stack<int> *min_stack;
	std::vector<int> *v;
	std::multiset<int, std::greater<int>> *s;

	max_stack_Test() {
		min_stack = new minmax_stack<int>([](int k1, int k2){ return k1 > k2;});
		v = new std::vector<int>();
		s = new std::multiset<int, std::greater<int>>();
	}

	void SetUp(){
		srand(time(0));
		for(int i=0; i<SIZE; i++){
			int x = rand() % (SIZE * 100);
			v->push_back(x);
		}
	}
};

TEST_F(max_stack_Test, Push) { 
	
	for(int x: *v){
		min_stack->push(x);
		s->insert(x);
		ASSERT_EQ(*(s->begin()), min_stack->minmax());
	}
}

TEST_F(max_stack_Test, Pop) {

	for(int x: *v){
		min_stack->push(x);
		s->insert(x);
		ASSERT_EQ(*(s->begin()), min_stack->minmax());
	}

	for(int i=v->size()-1; i>-1; --i){
		ASSERT_EQ(*(s->begin()), min_stack->minmax());
		min_stack->pop();
		s->erase(s->find((*v)[i]));
	}
}

