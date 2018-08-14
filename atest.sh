#!/bin/bash

test-ds(){
    curr=`pwd`
    echo "Testing $1"
    cd $1
    rm a.out 2>/dev/null
    g++ test.cpp /usr/lib/libgtest.so
    ./a.out
	rm a.out
    echo ""
    cd $curr
}

explore(){
    
    if test -f "$1/test.cpp"
    then
        test-ds $1
    fi

    subfolder=()
    for dir in $1/*;
    do
        if test -d "$dir"
        then
            subfolder+=("${dir}")
        fi
    done

    for dir in ${subfolder[@]}
    do
        explore $dir
    done
}

if [[ "$#" -eq "0" ]]
then
    echo "Directory to test required"
else
    explore "$1"
fi
