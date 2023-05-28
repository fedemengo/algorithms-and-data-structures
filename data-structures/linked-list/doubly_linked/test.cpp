#include "doubly_linked.hpp"
#include <vector>
#include <gtest/gtest.h>

struct doubly_linked_Test : testing::Test {

    const int SIZE = 2000;
	doubly_linked<std::string> *l1;
    std::vector<std::string> *check;

	doubly_linked_Test(){
		l1 = new doubly_linked<std::string>({});
        check = new std::vector<std::string>();
	}

    void SetUp( ) { 
        for(int i=0; i<SIZE; ++i){
            std::string str = "h" + std::to_string(i);
            l1->push_back(str);
            check->push_back(str);
        }
   }
};

TEST_F(doubly_linked_Test, Range) { 
	int i = 0;
    for(std::string str: *l1)
        ASSERT_EQ(str, (*check)[i++]);
}

TEST_F(doubly_linked_Test, Iterator) { 
    int i = 0;
	for(auto it = l1->begin(); it != l1->end(); i++, it++)
        ASSERT_EQ(*it, (*check)[i]);
}

TEST_F(doubly_linked_Test, TestIndex) { 
    for(int i=0; i<check->size(); i++) {
        ASSERT_EQ((*l1)[i], (*check)[i]);
    }
}

TEST_F(doubly_linked_Test, RemoveIndex) { 
	while(l1->size()){
        int index = rand() % l1->size();
        l1->remove(index);
        check->erase(check->begin() + index);
        
        for(int i=0; i<check->size(); i++) {
            ASSERT_EQ((*l1)[i], (*check)[i]);
        }
    }
}

