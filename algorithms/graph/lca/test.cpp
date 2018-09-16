
#include <iostream>
#include <cstring>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <queue>
#include <gtest/gtest.h>
#include "lca.hpp"

TEST(lca_Test, LCA1) {
    // tree
    graph G(20);

    G[0].push_back(1);
    G[0].push_back(2);
    G[1].push_back(3);
    G[1].push_back(4);
    G[2].push_back(5);
    G[2].push_back(6);
    G[3].push_back(7);
    G[3].push_back(8);
    G[4].push_back(9);
    G[4].push_back(10);
    G[5].push_back(11);
    G[5].push_back(12);
    G[6].push_back(13);
    G[6].push_back(14);

    G[15].push_back(0);
    G[15].push_back(16);

    std::queue<int> order;
    LCA lca(G, 15);

    EXPECT_EQ(1, lca.lca(3, 9));
    EXPECT_EQ(15, lca.lca(14, 16));
    EXPECT_EQ(0, lca.lca(2, 7));
    EXPECT_EQ(2, lca.lca(11, 13));
    EXPECT_EQ(4, lca.lca(9, 10));
    EXPECT_EQ(1, lca.lca(9, 3));
    EXPECT_EQ(15, lca.lca(16, 14));
    EXPECT_EQ(0, lca.lca(7, 2));
    EXPECT_EQ(2, lca.lca(13, 11));
    EXPECT_EQ(4, lca.lca(10, 9));
}


TEST(lca_Test, LCA2) {
    // tree
    graph G(10);

    G[0].push_back(1);
    G[0].push_back(2);
    G[1].push_back(9);
    G[2].push_back(3);
    G[3].push_back(4);
    G[4].push_back(5);
    G[5].push_back(6);
    G[6].push_back(7);
    G[7].push_back(8);
    
    std::queue<int> order;
    LCA lca(G, 0);

    EXPECT_EQ(0, lca.lca(1, 2));
    EXPECT_EQ(0, lca.lca(9, 7));
    EXPECT_EQ(0, lca.lca(9, 2));
    EXPECT_EQ(3, lca.lca(3, 7));
}

int main(int argc, char *argv[]) {
	testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
