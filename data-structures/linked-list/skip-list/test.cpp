#include "skip_list.hpp"
#include <vector>
#include <gtest/gtest.h>


struct skip_list_Test : testing::Test {

    const int SIZE = 10000;
	skip_list<int, std::string> *list;
    std::vector<std::string> *check;

	skip_list_Test(){
		list = new skip_list<int, std::string>({});
        check = new std::vector<std::string>();
	}

    void SetUp( ) { 
        for(int i=0; i<SIZE; ++i){
            std::string str = "h" + std::to_string(i);
            list->insert(i, str);
            check->push_back(str);
            //list->print();
        }
   }
};

TEST_F(skip_list_Test, Insert) {
    std::set<int> s;
    for(int i=0; i<SIZE; ++i){
        s.insert(i);
    }

	for(int i=0; i<SIZE; ++i){
        list->insert(i, (*check)[i]);
        s.insert(i);
        auto n = list->min();
        ASSERT_EQ(n.first, *s.begin());
        //list->print();
    }
}

TEST_F(skip_list_Test, Find) { 
    srand(time(0));
    for(int i=0; i<check->size(); i++){
        int idx = rand() % check->size();
        auto node = list->find(idx);
        ASSERT_EQ(node.second, "h" + std::to_string(idx));
    }
}

TEST_F(skip_list_Test, Remove) {
	
    std::multiset<int> s;
    for(int i=0; i<SIZE; ++i){
        s.insert(i);
    }

    for(int i=0; i<SIZE; ++i){
        list->insert(i/2, (*check)[i]);
        s.insert(i/2);
    }

    srand(time(0));
    for(int i=0; i<check->size(); i++){
        int idx = (rand() % list->size())/2;
        list->remove(idx);
        auto f = s.find(idx);
        if(f != s.end())
            s.erase(f);

        auto n = list->find(idx);
        auto it = s.lower_bound(idx);
        ASSERT_EQ(n.first, *it);
    }
}

TEST_F(skip_list_Test, Iterator) { 
    srand(time(0));
    int i=0;
    for(std::string &str: *list){
        ASSERT_EQ(str, (*check)[i]);
        ++i;
    }
}

TEST_F(skip_list_Test, IndexOp) { 
    
    for(int i=0; i<list->size(); ++i)
        ASSERT_EQ("h" + std::to_string(i), (*list)[i].second);
}

TEST_F(skip_list_Test, NaiveIndexing) { 
    
    for(int i=0, j = 0; i<list->size(); j = 0, ++i){
        auto it = list->begin();
        while(j++ < i) it++;
        ASSERT_EQ("h" + std::to_string(j-1), (*it));
    }
}

int main(int argc, char *argv[]) {

    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
