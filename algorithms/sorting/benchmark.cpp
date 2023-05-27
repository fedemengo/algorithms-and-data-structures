#include <algorithm>
#include <benchmark/benchmark.h>
#include <chrono>
#include <iostream>
#include <vector>

#include "heap_sort/heap_sort.hpp"
#include "insertion_sort/insertion_sort.hpp"
#include "merge_sort/merge_sort.hpp"
#include "quick_sort/quick_sort.hpp"
#include "selection_sort/selection_sort.hpp"

std::vector<int> random_vector(size_t size) {
  srand(time(0));
  std::vector<int> v1;
  v1.reserve(size);

  for (int i = 0; i < size; ++i) {
    int x = rand() % (10 * size);
    v1.push_back(x);
  }
  return v1;
}

static void selection_sort(benchmark::State &state) {
  auto rv = random_vector(state.range(0));
  for (auto _ : state) {
    selection_sort(rv);
    std::random_shuffle(rv.begin(), rv.end());
  }
}

static void insertion_sort(benchmark::State &state) {
  auto rv = random_vector(state.range(0));
  for (auto _ : state) {
    insertion_sort(rv);
    std::random_shuffle(rv.begin(), rv.end());
  }
}

static void merge_sort(benchmark::State &state) {
  auto rv = random_vector(state.range(0));
  for (auto _ : state) {
    merge_sort(rv);
    std::random_shuffle(rv.begin(), rv.end());
  }
}

static void heap_sort(benchmark::State &state) {
  auto rv = random_vector(state.range(0));
  for (auto _ : state) {
    heap_sort(rv);
    std::random_shuffle(rv.begin(), rv.end());
  }
}

static void quick_sort(benchmark::State &state) {
  auto rv = random_vector(state.range(0));
  for (auto _ : state) {
    quick_sort(rv);
    std::random_shuffle(rv.begin(), rv.end());
  }
}

BENCHMARK(selection_sort)->Arg(1 << 8)->Arg(1 << 10)->Arg(1 << 12);
BENCHMARK(insertion_sort)->Arg(1 << 8)->Arg(1 << 10)->Arg(1 << 12);
BENCHMARK(merge_sort)->Arg(1 << 8)->Arg(1 << 10)->Arg(1 << 12);
BENCHMARK(heap_sort)->Arg(1 << 8)->Arg(1 << 10)->Arg(1 << 12);
BENCHMARK(quick_sort)->Arg(1 << 8)->Arg(1 << 10)->Arg(1 << 12);

