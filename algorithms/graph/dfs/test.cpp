
#include <iostream>
#include <cstring>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <queue>
#include <gtest/gtest.h>
#include "dfs.hpp"

void test_equal(std::queue<int> &q, int x1) {
    int x2 = q.front();
    q.pop();
    ASSERT_EQ(x1, x2);
}

TEST(dfs_Test, VisitOrder) {
    graph G(5);

    G[0].push_back(1);
    G[0].push_back(2);
    G[0].push_back(4);
    G[1].push_back(2);
    G[1].push_back(3);
    G[1].push_back(1);
    G[2].push_back(0);
    G[2].push_back(2);
    G[2].push_back(3);
    G[3].push_back(1);
    G[3].push_back(3);
    G[3].push_back(4);
    G[4].push_back(2);
    G[4].push_back(3);

    std::queue<int> order;
    dfs_rec(G, order);

    test_equal(order, 0);        
    test_equal(order, 1);        
    test_equal(order, 2);        
    test_equal(order, 3);        
    test_equal(order, 4);
}

TEST(dfs_Test, RecursiveIterative){
    graph G(30);

    srand(time(0));
    int edges = 0;
    for(int i=0; i<G.size(); ++i){
        for(int j=0; j<G.size(); ++j){
            if(rand() & 1){
                G[i].push_back(j);
                edges++;
            }
        }
    }

    std::queue<int> o1, o2;
    dfs_rec(G, o1);
    dfs_iter(G, o2);

    //std::cout << edges << std::endl;
    ASSERT_EQ(o1.size(), o2.size());

    while(o1.size()){
        ASSERT_EQ(o1.front(), o2.front());
        o1.pop();
        o2.pop();
    }
}

int main(int argc, char *argv[]) {
	testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
