#!/usr/bin/env bash

testFolder(){
    prevwd=`pwd`
    cd "$1" && \
    printf "Testing ${1##*/}\n" && \
    g++ test.cpp -lgtest -lgtest_main && \
    ./a.out && \
	rm -rf a.out && \
    echo "" && \
    cd "$prevwd"
}

explore(){
    if test -f "$1/test.cpp"
    then
        testFolder "$1"
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
    echo "Directory to test required"
else
    explore "$1"
fi
