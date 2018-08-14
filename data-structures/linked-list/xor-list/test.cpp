#include "xor_list.hpp"
#include <vector>
#include <gtest/gtest.h>


struct xor_list_Test : testing::Test {

    const int SIZE = 2000;
	xor_list<std::string> *l1;
    xor_list<std::string> *l2;
    std::vector<std::string> *check;

	xor_list_Test(){
		l1 = new xor_list<std::string>({});
        l2 = new xor_list<std::string>({});
        check = new std::vector<std::string>();
	}

    void SetUp( ) { 
        for(int i=0; i<SIZE; ++i){
            std::string str = "h" + std::to_string(i);
            l1->push_back(str);
            l2->push_front(str);
            check->push_back(str);
        }
   }
};

TEST_F(xor_list_Test, Range) { 
	int i = 0;
    for(std::string str: *l2)
        ASSERT_EQ(str, (*check)[check->size()-++i]);
}

TEST_F(xor_list_Test, PopBack) { 
	int i = 0;
    for(std::string &str: *check){
        std::string s = l2->pop_back();
        ASSERT_EQ(s, (*check)[i++]);
    }
}

TEST_F(xor_list_Test, Iterator) { 
    int i = 0;
	for(auto it = l1->begin(); it != l1->end(); i++, it++)
        ASSERT_EQ(*it, (*check)[i]);
}

TEST_F(xor_list_Test, Swap) { 
    int i = check->size()-1;
    l1->swap();
    for(std::string x: *l1)
        ASSERT_EQ(x, (*check)[i--]);
}

TEST_F(xor_list_Test, PopFront) { 
	int i = 0;
    for(std::string &str: *check){
        std::string s = l1->pop_front();
        ASSERT_EQ(s, (*check)[i++]);
    }
}

int main(int argc, char *argv[]) {

    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
