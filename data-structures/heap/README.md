# Heap

## Binary Heap

It's implemented using an array. A function passed to the constructor determine the relative order of the elements (use as min-heap, max-heap..). 

By default it's a binary heap but it's possible to specify the number of childer for each node (given the implementaion must be a power of 2). 

To use the internal `update_key` an **unordered_map** is used to index a node given its data content. When considering the running time of every operation that use `update_key` another O(α) should be kept in mind (in general it's constant).

### Operations

- Push - O(log N)
- Top - O(1)
- Pop - O(log N)
- Heapsort - O(Nlog N)

## Fibonacci Heap

A function passed to the constructor determine the relative order of the elements (use as min-fibonacci-heap, max-fibonacci-heap..). 

To use the internal `update_key` an **unordered_map** is used to index a node given its data content. When considering the running time of every operation that use `update_key` another O(α) should be kept in mind (in general it's constant). 

A pool of instantiate nodes is used to lower the overhead of dynamic node creation. Every time a node is extracted it is cleared and put back in the pool.

### Operations

- Insert - O(log N)
- Get - O(1)
- Remove - O(log N)
- Update key - O(1)
- Merge - O(1)

## Priority Queue

Implementation based on binary heap. It exposes the `update_key` method

### Operations

- Push - O(log N)
- Top - O(1)
- Pop - O(log N)
- Update key - O(log N)
