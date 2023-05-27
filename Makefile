
test: build-test run-test

test-docker:
	docker run --rm -v $(PWD):/workspace -w /workspace ghcr.io/fedemengo/googletest:1.13.0 ./scripts/test.sh .

build-test: test/*_test.cpp src/core.cpp
	$(CC) $(CFLAGS) -o ./bin/$(TEST_RUNNER) $^ $(TESTFLAGS)

run-test:
	./bin/$(TEST_RUNNER)

# Run benchmarks
bench: build-bench run-bench

bench-docker:
	docker run --rm -v $(PWD):/workspace -w /workspace ghcr.io/fedemengo/googletest:1.13.0 ./scripts/bench.sh .

build-bench: test/*_bench.cpp src/core.cpp
	$(CC) $(CFLAGS) -o ./bin/$(BENCH_RUNNER) $^ $(BENCHFLAGS) $(TESTFLAGS)

run-bench:
	./bin/$(BENCH_RUNNER) --benchmark_format=console --benchmark_out=./test/benchmarks/benchmark --benchmark_out_format=console --benchmark_filter=BM_


