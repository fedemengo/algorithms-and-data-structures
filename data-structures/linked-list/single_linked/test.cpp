#include "single_linked.hpp"
#include <vector>
#include <gtest/gtest.h>

struct single_linked_Test : testing::Test {

    const int SIZE = 2000;
	single_linked<std::string> *l1;
    std::vector<std::string> *check;

	single_linked_Test(){
		l1 = new single_linked<std::string>({});
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

TEST_F(single_linked_Test, PopFront) { 
    for(int i=0; i<check->size(); ++i){
		std::string str = l1->front();
		l1->pop_front();
		ASSERT_EQ(str, (*check)[i]);
	}
}

TEST_F(single_linked_Test, Range) { 
	int i = 0;
    for(std::string str: *l1)
        ASSERT_EQ(str, (*check)[i++]);
}

TEST_F(single_linked_Test, Iterator) { 
    int i = 0;
	for(auto it = l1->begin(); it != l1->end(); i++, it++)
        ASSERT_EQ(*it, (*check)[i]);
}

TEST_F(single_linked_Test, TestIndex) { 
    for(int i=0; i<check->size(); i++) {
        ASSERT_EQ((*l1)[i], (*check)[i]);
    }
}

TEST_F(single_linked_Test, RemoveIndex) { 
	int tests = 100;
	while(tests--){
        int index = rand() % l1->size();
        l1->erase(index);
        check->erase(check->begin() + index);
        
        for(int i=0; i<check->size(); i++) {
            ASSERT_EQ((*l1)[i], (*check)[i]);
        }
    }
}

TEST_F(single_linked_Test, Reverse) { 
	l1->reverse();
	int i = 0;
	for(auto it = l1->begin(); it != l1->end(); i++, it++)
        ASSERT_EQ(*it, (*check)[check->size()-1-i]);
}

int main(int argc, char *argv[]) {

    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

