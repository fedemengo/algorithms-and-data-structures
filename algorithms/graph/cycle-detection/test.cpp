
#include <iostream>
#include <cstring>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <queue>
#include <gtest/gtest.h>
#include "cycle-detection.hpp"

TEST(dfs_Test, VisitOrder) {

    graph G(3);
    G[0].push_back(1);
    G[1].push_back(2);
    G[2].push_back(0);
    ASSERT_TRUE(dfs(G));

    G.clear();
    G[0].push_back(1);
    G[0].push_back(2);
    G[1].push_back(3);
    ASSERT_FALSE(dfs(G));
}

int main(int argc, char *argv[]) {
	testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
