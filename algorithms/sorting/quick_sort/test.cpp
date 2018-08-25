#include <iostream>
#include <algorithm>
#include <vector>
#include <gtest/gtest.h>
#include "quick_sort.hpp"

struct quick_sort_Test : testing::Test {
	const int SIZE = 1000000;
	std::vector<int> v1, v2;

	quick_sort_Test() {}

	void SetUp() {
		srand(time(0));
		for(int i=0; i<SIZE; ++i){
			int x = rand() % (10 * SIZE);
			v1.push_back(x);
			v2.push_back(x);
		}
	}
};

TEST_F(quick_sort_Test, Check) {
	quick_sort(v1, 0, v1.size());
	std::sort(v2.begin(), v2.end());

	for(int i=0; i<v1.size(); ++i)
		ASSERT_EQ(v1[i], v2[i]);
}

int main(int argc, char *argv[]){
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

