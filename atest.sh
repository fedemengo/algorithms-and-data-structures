#!/bin/bash

testFolder(){
    curr=`pwd`
    cd "$1"
    echo "Testing ${1##*/}"
	rm a.out 2>/dev/null
    g++ test.cpp -lgtest
    ./a.out
	rm a.out
    echo ""
    cd "$curr"    
}

explore(){
    
    if test -f "$1/test.cpp"
    then
        testFolder "$1"
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
    echo "Directory to test required"
else
    explore "$1"
fi
