#include "skip_list.hpp"
#include <vector>
#include <gtest/gtest.h>


struct skip_list_Test : testing::Test {

    const int SIZE = 1000;
	skip_list<int, std::string> *list;
    skip_list<int, std::string> *l2;
    std::vector<std::string> *check;

	skip_list_Test(){
		list = new skip_list<int, std::string>([](int k1, int k2){
            return k1 < k2;
        });
        l2 = new skip_list<int, std::string>([](int k1, int k2){
            return k1 > k2;
        });
        check = new std::vector<std::string>();
	}

    void SetUp( ) { 
        for(int i=0; i<SIZE; ++i){
            std::string str = "h" + std::to_string(i);
            list->insert(i, str);
            l2->insert(i, str);
            check->push_back(str);
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
        auto n = list->top();
        ASSERT_EQ(n.first, *s.begin());
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

    srand(time(0));
    for(int i=0; i<check->size(); i++){
        int idx = rand() % list->size();
        list->remove(idx);
        auto f = s.find(idx);
        if(f != s.end())
            s.erase(f);

        auto n = list->find(idx);
        auto it = s.lower_bound(idx);
        s.insert(idx * list->size());
        list->insert(idx * list->size(), "h" + std::to_string(idx * list->size()));
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


TEST_F(skip_list_Test, RemoveAndIndex) {
	
    srand(time(0));
    for(int i=0; i<check->size(); i++){
        int idx = rand() % list->size();
        if(list->remove(idx)){
            auto p = check->begin();
            while(*p != "h" + std::to_string(idx))
                p++;
            check->erase(p);
        }
        for(int i=0; i<list->size(); ++i){
            ASSERT_EQ((*check)[i], (*list)[i].second);
        }
    }
}

TEST_F(skip_list_Test, RemoveAt) {

    srand(time(0));
    for(int i=0; i<check->size(); i++){
        int idx = rand() % list->size();
        list->remove_at(idx);
        check->erase(check->begin() + idx);
        for(int i=0; i<list->size(); ++i){
            ASSERT_EQ((*check)[i], (*list)[i].second);
        }
    }
}

TEST(max_skip_list_Test, Insert) {
    const int SIZE = 1000;
    skip_list<int, std::string> l2([](int k1, int k2){ return k1 > k2; });
    std::set<int, std::greater<int>> s;
    srand(time(0));

    int z = 1;
    for(int i=0; i<SIZE; ++i){
        int x = rand() % (SIZE*z);
        if(!s.count(x)){
            s.insert(x);
            l2.insert(x, "");
            ++z;
        }
        auto n = l2.top();
        ASSERT_EQ(n.first, *s.begin());
    }
}

int main(int argc, char *argv[]) {

    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
