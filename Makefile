
CC := g++
CFLAGS := -std=c++2a -Wall -O3
TESTFLAGS = -lgtest -lgtest_main
BENCHFLAGS = -lbenchmark -lbenchmark_main

PROJECT = algos_ds
TEST_RUNNER = $(PROJECT)_test
BENCH_RUNNER = $(PROJECT)_bench

FILES := $(shell find . -type f -name "test.cpp")

print: 
	@echo $(FILES)

test: build-test run-test

test-docker:
	docker run --rm -v $(PWD):/workspace -w /workspace ghcr.io/fedemengo/googletest:1.13.0 make test

build-test: $(FILES)
	$(CC) $(CFLAGS) -o $(TEST_RUNNER) $^ $(TESTFLAGS)

run-test:
	./$(TEST_RUNNER)

bench: run-bench

bench-docker:
	docker run --rm -v $(PWD):/workspace -w /workspace ghcr.io/fedemengo/googletest:1.13.0 make bench

run-bench:
	./scripts/bench.sh .

