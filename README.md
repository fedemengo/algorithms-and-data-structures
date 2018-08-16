# Algorithms and Data Structures

Implementaion of some algorithms and data structures in C++.

## Structure of the repo

All material is organized in sub folder. In root there are the first two big topic **algorithms** and **data structure**. All source within the algorithms folder are usually just plain implemenation of the algorithm, whereas the files in the data structure folder usually constist of a `.hpp` file that contains the implementaion of the data structure (using template when possible) and a `test.cpp` file that is used to test the ds.

Inside the folders that group different algorithms/data structures related to each other there is a `README` file that gives some information on the content of the folder.

## Testing

To compile each test I use `g++ test.cpp /usr/lib/libgtest.so`. Other library should be linked if necessary (e.g `-lpthread`), just take a look at [Google Test](https://github.com/google/googletest).

For testing rapidily I used the `atest.sh` script ("atest" is just for fast tab-completion). To use it in any folder its location should be added to `PATH`, so `PATH="${PATH}:/path/to/folder/algorithms-and-data-structures"`. By passing a directory to test it will generate and run all test in its subfolder that contains a `test.cpp` file.

