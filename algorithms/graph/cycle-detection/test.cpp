
#include "cycle-detection.hpp"
#include <gtest/gtest.h>

TEST(dfs_Test, VisitOrder) {

  graph G1(3);
  G1[0].push_back(1);
  G1[1].push_back(2);
  G1[2].push_back(0);
  ASSERT_TRUE(dfs(G1));

  graph G2(4);
  G2[0].push_back(1);
  G2[0].push_back(2);
  G2[1].push_back(3);
  ASSERT_FALSE(dfs(G2));
}
