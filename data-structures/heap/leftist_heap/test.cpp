#include "leftist_heap.hpp"
#include <gtest/gtest.h>
#include <vector>
#include <algorithm>

const int SIZE = 100000;
std::vector<std::pair<int, std::string>> values;

std::pair<int, std::string> TopAndPop(leftist_heap<int, std::string> &h) {
  std::pair<int, std::string> x = h.top();
  h.pop();
  return x;
}

struct min_leftist_heap_Test : testing::Test {
  leftist_heap<int, std::string> *heap;

  min_leftist_heap_Test() {
    heap = new leftist_heap<int, std::string>(
        [](int k1, int k2) { return k1 < k2; });
  }
};

TEST_F(min_leftist_heap_Test, PushPop) {

  for (auto &p : values)
    heap->push(p.first, p.second);

  std::vector<std::pair<int, std::string>> x(values);
  std::sort(x.begin(), x.end());
  for (auto &p : x)
    ASSERT_EQ(p, TopAndPop(*heap));
}

TEST_F(min_leftist_heap_Test, Merge) {

  leftist_heap<int, std::string> h([](int k1, int k2) { return k1 < k2; });

  std::vector<std::pair<int, std::string>> x(values);
  for (auto &p : values) {
    x.push_back({p.first * 100, "data" + std::to_string(p.first * 100)});
    h.push(p.first * 100, "data" + std::to_string(p.first * 100));
  }

  for (auto &p : values)
    heap->push(p.first, p.second);

  heap->merge(h);
  std::sort(x.begin(), x.end());

  for (auto &p : x)
    ASSERT_EQ(p, TopAndPop(*heap));
}

TEST(max_leftist_heap_Test, PushPop) {
  leftist_heap<int, std::string> max_heap(
      [](int k1, int k2) { return k1 > k2; });

  for (auto &p : values)
    max_heap.push(p.first, p.second);

  std::vector<std::pair<int, std::string>> x(values);
  std::sort(x.begin(), x.end(), std::greater<std::pair<int, std::string>>());

  for (auto &p : x)
    ASSERT_EQ(p, TopAndPop(max_heap));
}

int main(int argc, char *argv[]) {

  srand(time(0));
  for (int i = 0; i < SIZE; i++) {
    int key = rand() % (SIZE * 100) + 1;
    std::string str = "data" + std::to_string(key);
    values.push_back({key, str});
  }

  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
