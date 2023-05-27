#include "merge_sort.hpp"
#include <algorithm>
#include <gtest/gtest.h>
#include <iostream>
#include <vector>

struct merge_sort_Test : testing::Test {
  const int SIZE = 1000000;
  std::vector<int> v1, v2;

  merge_sort_Test() {}

  void SetUp() {
    srand(time(0));
    for (int i = 0; i < SIZE; ++i) {
      int x = rand() % (10 * SIZE);
      v1.push_back(x);
      v2.push_back(x);
    }
  }
};

TEST_F(merge_sort_Test, Check) {
  merge_sort(v1);
  std::sort(v2.begin(), v2.end());

  for (int i = 0; i < v1.size(); ++i)
    ASSERT_EQ(v1[i], v2[i]);
}
