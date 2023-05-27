#!/usr/bin/env bash

benchFolder(){
    prevwd=`pwd`
    cd "$1" && \
    echo "Benchmark in ${1##*/}" && \
    g++ benchmark.cpp -lbenchmark -lbenchmark_main && \
    ./a.out | tee benchmarks && \
	rm -rf a.out && \
    echo "" && \
    cd "$prevwd"
}

explore(){
	if test -f "$1/benchmark.cpp"
    then
        benchFolder "$1"
    fi

	subfolder=()
    for dir in "$1"/*;
    do
        if test -d "$dir"
        then
            subfolder+=("${dir}")
        fi
    done

    for dir in "${subfolder[@]}"
    do
        explore "$dir"
    done
}

if [[ "$#" -eq "0" ]]
then
    echo "Directory to benchmark required"
else
    explore "$1"
fi
