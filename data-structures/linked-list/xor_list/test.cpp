#include "xor_list.hpp"
#include <vector>
#include <gtest/gtest.h>


struct xor_list_Test : testing::Test {

    const int SIZE = 10000;
	xor_list<std::string> *list;
    std::vector<std::string> *check;

	xor_list_Test(){
		list = new xor_list<std::string>({});
        check = new std::vector<std::string>();
	}

    void SetUp( ) { 
        for(int i=0; i<SIZE/2; ++i){
            std::string str = "h" + std::to_string(i);
            list->push_back(str);
            check->push_back(str);
        }
        for(int i=SIZE/2; i<SIZE; ++i){
            std::string str = "h" + std::to_string(i);
            list->push_front(str);
            check->insert(check->begin(), str);
        }
   }
};

TEST_F(xor_list_Test, PopFront) { 
	int i = 0;
    for(std::string &str: *check){
        std::string s = list->pop_front();
        ASSERT_EQ(s, str);
    }
}

TEST_F(xor_list_Test, PopBack) { 
	int i = 0;
    for(std::string &str: *check){
        std::string s = list->pop_back();
        ASSERT_EQ(s, (*check)[check->size()-++i]);
    }
}

TEST_F(xor_list_Test, Find) { 

    srand(time(0));
    for(int i=0; i<check->size(); i++){
        int idx = rand() % (check->size() - 3) + 2;
        idx = std::min(std::max(idx, 0), (int) check->size()-1);
		std::string data = (*check)[idx];
        auto node = list->find(data);
        ASSERT_TRUE(node.first != nullptr);
        ASSERT_EQ(node.first->data, data);
        if (node.second.first != nullptr)
			ASSERT_EQ(node.second.first->data, (*check)[idx-1]);
		if (node.second.second != nullptr)
        	ASSERT_EQ(node.second.second->data, (*check)[idx+1]);
    }
}

TEST_F(xor_list_Test, Get) { 

    srand(time(0));
    for(int i=0; i<check->size(); i++){
        int idx = rand() % (check->size() - 3) + 2;
        idx = std::min(std::max(idx, 0), (int) check->size()-1);
		std::string data = (*check)[idx];
		auto node = list->get(idx);
        ASSERT_TRUE(node.first != nullptr);
        ASSERT_EQ(node.first->data, data);
        if (node.second.first != nullptr)
        	ASSERT_EQ(node.second.first->data, (*check)[idx-1]);
        if (node.second.second != nullptr)
        	ASSERT_EQ(node.second.second->data, (*check)[idx+1]);
    }
}

TEST_F(xor_list_Test, Insert) {
	srand(time(0));
	for(int i=0; i<SIZE; ++i){	
		int idx = rand() % std::max(1, (int) (check->size() - 1)) + 1;
		std::string s = "test" + std::to_string(idx);
		list->insert(idx, s);
		check->insert(check->begin()+idx, s);
	}
	int i = 0;
    for(std::string &str: *check){
        std::string s = list->pop_front();
        ASSERT_EQ(s, str);
    }
}

TEST_F(xor_list_Test, Remove) {
	
	srand(time(0));
	while (check->size()) {
		int idx = rand() % std::max(1, (int) (check->size() - 1)) + 1;
        idx = std::min(std::max(idx, 0), (int) check->size()-1);
		check->erase(check->begin()+idx);
		list->remove(idx);

		int i = 0;
		for (auto it = list->begin(); it != list->end(); it++, i++)
			ASSERT_EQ(*it, (*check)[i]);
	}
}

TEST_F(xor_list_Test, Reverse) { 
    int i = check->size()-1;
    list->reverse();
    for(std::string x: *list)
        ASSERT_EQ(x, (*check)[i--]);
}

TEST_F(xor_list_Test, Range) { 
	int i = 0;
    for(std::string str: *list)
        ASSERT_EQ(str, (*check)[i++]);
}


TEST_F(xor_list_Test, Iterator) { 
    int i = 0;
	for(auto it = list->begin(); it != list->end(); i++, it++)
        ASSERT_EQ(*it, (*check)[i]);
}

int main(int argc, char *argv[]) {

    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
