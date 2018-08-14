Algorithms and Data Structures
-------------------------------------------------

Implementation of some algorithms and data structures in **C++**.

Below a list of what I'd like to add (pretty much anything)

### Testing

To compile each test I use

`g++ test.cpp /usr/lib/libgtest.so`

Other library are needed if they are not linked automatically (e.g `-lpthread`)

For testing rapidily I used the `atest.sh` script ("atest" is just for fast tab-completion). To use it in any folder its location should be added to `PATH`, so `PATH="${PATH}:/path/to/folder/algorithms-and-data-structures"`.

### Data Structure

- List
	- [x] Linked list
	- [x] XOR list
	- [ ] Skiplist

- Heap
	- [x] Binary Heap
	- [x] Priority Queue
	- [x] Fibonacci Heap
	- [ ] Binomial Heap
	- [x] Leftist Heap
	- [ ] Skew Heap
	- [ ] d-Heap
	- [ ] Brodal Heap
	- [ ] Pairing Heap
	- [ ] Weak Heap

- Tree
	- [ ] Mergesort Tree
	- [ ] Wavelettree
	- [ ] Van Emde Boas

- Binary Search Tree
	- [ ] B-Tree
	- [ ] AVL Tree
	- [ ] Treap
	- [ ] AA
	- [ ] Scapegoat Tree
	- [ ] Red-Black Tree
	- [ ] Splay Tree

- Trie
	- [ ] C-Trie
	- [ ] eerTree
	- [ ] Suffix
	- [ ] Ternary Search
	- [ ] X-fast, Y-fast

- Data partitioning Tree
	- [x] Fenwick Tree (frequency and cumulative frequency)
	- [ ] Segment Tree
	- [ ] k-d Tree
	- [ ] Quad Tree

- [ ] Hash Table
- [ ] Sparse Table
- [x] Disjoint-Sets
- [ ] SQRT Decomposition
- [ ] Heavy-Light Decomposition
- [ ] Fractional Cascading

### Algorithms

- Graph
	- [x] SSSP (Dijkstra, SPFA)
	- [ ] APSP (Floyd-Warshall)
	- [ ] SCC
	- [ ] Topological sort
	- [ ] MST (Prim, Kruskal)
	- [ ] Euler tour
	- [ ] Max Flow (Edmonds-Karp, Dinic)
	- [ ] Ford-Fulkerson
	- [ ] LCA (binary jumps)
	- [ ] Bipartite Graph
	- [ ] Vertex cover
	- [ ] TSP
	- [ ] 2SAT
- String
	- [ ] Polynomial Hashing
	- [ ] KMP
	- [ ] Z Algorithm
	- [ ] Manacher
	- [ ] Aho Corasick
	- [ ] Suffix Automatom
	- [ ] Suffix Tree
	- [ ] Suffix Array
	- [ ] LCP Array
	- [ ] LCS
	- [ ] String matching 2D
	- [ ] String hashing

- Geometry
	- [ ] Convex Hull
	- [ ] Closest Pair
