#include <iostream>
#include <algorithm>
#include <vector>
#include <gtest/gtest.h>
#include "lis.hpp"

TEST(lis_Test1, Check) { ASSERT_EQ(lis(std::vector<int>{1, 2}), 1); }
TEST(lis_Test2, Check) { ASSERT_EQ(lis(std::vector<int>{5, 4, 3, 2, 1}), 5); }
TEST(lis_Test3, Check) { ASSERT_EQ(lis(std::vector<int>{3, 2, 1, 10, 9, 8, 7}), 4); }
TEST(lis_Test4, Check) { ASSERT_EQ(lis(std::vector<int>{5, 4, 3, 3, 2, 1, 0}), 6); }

int main(int argc, char *argv[]){
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

