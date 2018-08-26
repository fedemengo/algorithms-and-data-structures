#!/bin/bash

benchFolder(){
    curr=`pwd`
    echo "Benchmark in ${1##*/}"
    cd "$1"
	rm a.out 2>/dev/null
    g++ benchmark.cpp -lbenchmark
    ./a.out
	rm a.out
    echo ""
    cd "$curr"
}

explore(){

	if test -f "$1/benchmark.cpp"
    then
        benchFolder "$1"
    fi

	rm -rf "$1/.vscode" 2>/dev/null
    
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
