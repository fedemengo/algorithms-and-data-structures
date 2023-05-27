
test: run-test

test-docker:
	docker run --rm -v $(PWD):/workspace -w /workspace ghcr.io/fedemengo/googletest:1.13.0 make test

run-test:
	./scripts/test.sh .

bench: run-bench

bench-docker:
	docker run --rm -v $(PWD):/workspace -w /workspace ghcr.io/fedemengo/googletest:1.13.0 make bench

run-bench:
	./scripts/bench.sh .

