
#include <benchmark/benchmark.h>
#include <cstring>
#include "skip-list/skip_list.hpp"
#include <map>

static void SetInsert(benchmark::State& state) {
	std::map<int, int> m;
  
    for (auto _ : state) {
        for(int i=0; i<state.range(0); ++i)
            m.insert(std::pair<int, int>(i, i*5));
    }
}
BENCHMARK(SetInsert)->Arg(1000)->Arg(10000)->Arg(100000);

static void SkipListInsert(benchmark::State& state) {
    skip_list<int, int> s([](int k1, int k2){ return k1 < k2;});
  
    for (auto _ : state) {
        for(int i=0; i<state.range(0); ++i)
            s.insert(i, i*5);
    }
}
BENCHMARK(SkipListInsert)->Arg(1000)->Arg(10000)->Arg(100000);
/*
static void LeftistPushPop(benchmark::State& state) {
    leftist_heap<int, int> h([](int k1, int k2){ return k1 < k2;});
  
    for (auto _ : state) {
        for(int i=0; i<state.range(0); ++i)
            h.push(i, i);
        while(h.size()) h.pop();
    }
}
BENCHMARK(LeftistPushPop)->Arg(1000)->Arg(10000)->Arg(100000);

static void SkewPushPop(benchmark::State& state) {
    skew_heap<int, int> h([](int k1, int k2){ return k1 < k2;});
  
    for (auto _ : state) {
        for(int i=0; i<state.range(0); ++i)
            h.push(i, i);
        while(h.size()) h.pop();
    }
}
BENCHMARK(SkewPushPop)->Arg(1000)->Arg(10000)->Arg(100000);
*/
BENCHMARK_MAIN();
