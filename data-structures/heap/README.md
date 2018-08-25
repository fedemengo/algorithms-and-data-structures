# Heap

## Binary Heap

<div align="center">

![binary heap](https://upload.wikimedia.org/wikipedia/commons/thumb/8/86/Binary_tree_in_array.svg/370px-Binary_tree_in_array.svg.png)
</div>

It's implemented using an array. A function passed to the constructor determine the relative order of the elements (use as min-heap, max-heap..). 

By default it's a binary heap but it's possible to specify the number of childer for each node (given the implementaion must be a power of 2). 

To use the internal `update_key` an **unordered_map** is used to index a node given its data content. When considering the running time of every operation that use `update_key` another O(α) should be kept in mind (in general it's constant).

### Operations

- `push` - O(log N)
- `top` - O(1)
- `pop` - O(log N)
- `heapsort` - O(Nlog N)

## Fibonacci Heap

<div align="center">

![fibo heap](https://i.imgur.com/XmQmTSz.png)
</div>

A function passed to the constructor determine the relative order of the elements (use as min-fibonacci-heap, max-fibonacci-heap..). 

To use the internal `update_key` an **unordered_map** is used to index a node given its data content. When considering the running time of every operation that use `update_key` another O(α) should be kept in mind (in general it's constant). 

A pool of instantiate nodes is used to lower the overhead of dynamic node creation. Every time a node is extracted it is cleared and put back in the pool.

### Operations

- `insert` - O(1)
- `get` - O(1)
- `remove` - O(log N)*
- `update_key` - O(1)*
- `merge` - O(1)

\* Amortized time

## Leftist Heap

<div align="center">

![leftist](https://i.imgur.com/pUay6Ja.png)
</div>

For this structure holds both the heap property and also the leftist property: `n->left->rank >= n->right->rank` and `n->left == nullptr` only if `n->right == nullptr`. In each node the shorted path to a leaf in left subtree is at least as long as the one in the right subtree.

A function passed to the constructor is used to determine the relative order of the element.

All operations are based on `merge`. When pushing, merge the new node with the heap, when popping, merge the root's left tree with the root's right tree.

### Operations

- `push` - O(log N)
- `top` - O(1)
- `pop` - O(log N)
- `merge` - 0(log N)

## Skew Heap

Implementation based on leftist heap but instead of rebalancing the structure on every merge operation (used for  both pushing and popping), rotate `left` and `right` subtree for each node in the merge path.

A function passed to the constructor is used to determine the relative order of the element.

All operations are based on `merge`. When pushing, merge the new node with the heap, when popping, merge the root's left tree with the root's right tree.

### Operations

- `push` - O(log N)
- `top` - O(1)
- `pop` - O(log N)
- `merge` - 0(log N)

## Priority Queue

Implementation based on binary heap. It exposes the `update_key` method

### Operations

- `push` - O(log N)
- `top` - O(1)
- `pop` - O(log N)
- `update_key` - O(log N)
