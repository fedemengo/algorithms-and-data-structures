#include "binary_heap/binary_heap.hpp"
#include "fibonacci_heap/fibonacci_heap.hpp"
#include "leftist_heap/leftist_heap.hpp"
#include "skew_heap/skew_heap.hpp"
#include <benchmark/benchmark.h>
#include <cstring>
#include <queue>

static void FiboPushPop(benchmark::State &state) {
  fibonacci_heap<int, int> h([](int k1, int k2) { return k1 < k2; });

  for (auto _ : state) {
    for (int i = 0; i < state.range(0); ++i)
      h.insert(i, i);
    while (h.size())
      h.remove();
  }
}
BENCHMARK(FiboPushPop)->Arg(1000)->Arg(10000)->Arg(100000);

static void BinaryPushPop(benchmark::State &state) {
  binary_heap<int, int> h([](int k1, int k2) { return k1 < k2; });

  for (auto _ : state) {
    for (int i = 0; i < state.range(0); ++i)
      h.push(i, i);
    while (h.size())
      h.pop();
  }
}
BENCHMARK(BinaryPushPop)->Arg(1000)->Arg(10000)->Arg(100000);

static void LeftistPushPop(benchmark::State &state) {
  leftist_heap<int, int> h([](int k1, int k2) { return k1 < k2; });

  for (auto _ : state) {
    for (int i = 0; i < state.range(0); ++i)
      h.push(i, i);
    while (h.size())
      h.pop();
  }
}
BENCHMARK(LeftistPushPop)->Arg(1000)->Arg(10000)->Arg(100000);

static void SkewPushPop(benchmark::State &state) {
  skew_heap<int, int> h([](int k1, int k2) { return k1 < k2; });

  for (auto _ : state) {
    for (int i = 0; i < state.range(0); ++i)
      h.push(i, i);
    while (h.size())
      h.pop();
  }
}
BENCHMARK(SkewPushPop)->Arg(1000)->Arg(10000)->Arg(100000);

static void PQPushPop(benchmark::State &state) {
  std::priority_queue<int> pq;

  for (auto _ : state) {
    for (int i = 0; i < state.range(0); ++i)
      pq.push(i);
    while (pq.size())
      pq.pop();
  }
}
BENCHMARK(PQPushPop)->Arg(1000)->Arg(10000)->Arg(100000);
