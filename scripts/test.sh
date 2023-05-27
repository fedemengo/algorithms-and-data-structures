#!/usr/bin/env bash

testFolder(){
    prevwd=`pwd`
    cd "$1" && \
    printf "Testing ${1}\n" && \
    g++ test.cpp -lgtest -lgtest_main && \
    ./a.out
    CODE=$?
    if [[ "$CODE" -ne "0" ]]; then
        printf "Test ${1} failed with code ${CODE}\n"
        CODE=1
    fi

	rm -rf a.out && \
    echo "" && \
    cd "$prevwd"

    return $CODE
}

GLOBAL_CODE=0
subfolder=()
visited=$(mktemp -d)

explore(){
    touch "$1/.tested"
    if test -f "$1/test.cpp"; then
        testFolder "$1"
        GLOBAL_CODE=$((GLOBAL_CODE + $?))
    fi

    for dir in "$1"/*;
    do
        if [[ -d "$dir" && ! -e "$dir/.tested" ]]; then
            subfolder+=("${dir}")
        fi
    done

    for dir in "${subfolder[@]}"
    do
        if [[ ! -e "$dir/.tested" ]]; then
            explore "$dir"
        fi
    done
}

if [[ "$#" -eq "0" ]]
then
    echo "Directory to test required"
else
    explore "$1"
fi

find "$1" -name ".tested" -delete

if [[ "$GLOBAL_CODE" -ne "0" ]]; then
    echo "Some tests failed: $GLOBAL_CODE failed"
    exit 1
fi

