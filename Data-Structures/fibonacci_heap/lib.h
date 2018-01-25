#include <cmath>			// log2() and floor()
#include <unordered_map>	// to map the address for every node
#include <vector>			// vector
// node
class node {
public:
	int vertex;
	int weight;
};

// doubly linked list template
template <typename T>
class doubly_linked_list {
private:
	size_t _size;
public:
	T head;
	doubly_linked_list() : head(nullptr), _size(0) {};
	~doubly_linked_list() {};
	void init() { head = nullptr, _size = 0; }
	void insert_node(T prev, T node) {
		if (prev != nullptr) {
			node->left = prev;
			node->right = prev->right;
			prev->right->left = node;
			prev->right = node;
		}
		++_size;
	}
	void extract_node(T node) {		// remove node from list leaving untouched its "left" and "right" pointer
		if (_size == 1)	head = nullptr;
		else if (node == head) head = node->right;
		node->right->left = node->left;
		node->left->right = node->right;
		--_size;
	}
	void remove_node(T node) {			// remove node from list and clear its pointer
		extract_node(node);
		node->left = node;
		node->right = node;
	}
	void push_back(T node) {			// append the node at the tail of the list
		if (empty()) insert_node(head = node, node);
		else insert_node(head->left, node);
	}
	bool empty() { return !_size; }
	int size() { return _size; }
	void clear_list(T &x) { head = nullptr, _size = 0, x = nullptr; }
};

// fibonacci heap node
class fib_node {
public:
	// attributes
	fib_node *p;
	doubly_linked_list<fib_node *> child_list;
	fib_node *left;
	fib_node *right;
	int degree;
	bool mark;
	int key;
	int vertex;
	//methods
	fib_node(int v, int k) : p(nullptr), left(this), right(this), degree(0), mark(false), key(k), vertex(v) { child_list.init(); }
	fib_node(fib_node *node) { if(node != nullptr) {key = node->key, vertex = node->vertex, delete node; } else {key = -1, vertex = -1; } }
	~fib_node() {};
	bool operator< (const fib_node x){ return key < x.key; }
	bool operator> (const fib_node x){ return key > x.key; }

};

// fibonacci heap
class fibonacci_heap {
private:
	// attributes
	fib_node *min_node;							// pointer to min_node inside root_list
	fib_node *extracted;
	fib_node *child;
	doubly_linked_list<fib_node *> root_list;		// list of root_nodes
	std::unordered_map<int, fib_node *> *addresses;		// hash table to map each node's address using its vertex as key for the hash
	int nodes;
	// methods
	void consolidate() {
		std::vector<fib_node *> pointer(max_degree(), nullptr);
		fib_node *node = min_node, *x, *y;

		for(int i=0; i<root_list.size(); ++i){
			node = (x = node)->right;
			int d = x->degree;
			while (pointer[d]) {
				y = pointer[d];
				if (*x > *y)
					std::swap(x, y);
				make_child(y, x);
				pointer[d] = nullptr;
				++d;
				--i;
			}
			pointer[d] = x;
		}
		root_list.clear_list(min_node);
		for (auto &x: pointer) {
			if (x) {
				root_list.push_back(x);
				if (min_node == nullptr)
					min_node = x;
				else if (*x < *min_node)
					min_node = x;
			}
		}
	}
	void cut(fib_node *x, fib_node *y) {
		y->child_list.remove_node(x);
		--y->degree;
		root_list.push_back(x);
		x->p = nullptr;
		x->mark = false;
	}
	void cascading_cut(fib_node *y) {
		fib_node *z = y->p;
		while(z != nullptr){
			if(y->mark == false){
				y->mark = true;
				z = nullptr;
			} else {
				cut(y, z);
				z = (y = z)->p;
			}
		}
	}
	void make_child(fib_node *y, fib_node *x) {		// link root y to root x, x remains a root, y does not
		root_list.remove_node(y);
		x->child_list.push_back(y);
		++x->degree;
		y->p = x;
		y->mark = false;
	}
	// upper_bound of number of root nodes in the root lists that will be present after consolidation
	int max_degree() { return (int)floor(log((double)nodes)/log((1.0+sqrt(5.0))/2.0))+1; }
public:
	// methods
	fibonacci_heap(int size, int value) : min_node(nullptr), nodes(0), addresses(new std::unordered_map<int, fib_node *>(size)) { for(int i=0; i<size; ++i) insert(new fib_node(i, value)); }
	~fibonacci_heap() { delete addresses; };
	bool empty() { return !nodes; }
	void insert(fib_node *node) {							// insert(new fib_node(key, vertex))
		(*addresses)[node->vertex] = node;			// [node->vertex] = node;
		root_list.push_back(node);
		if (min_node == nullptr)
			min_node = node;
		else if(*node < *min_node)
			min_node = node;
		++nodes;
	}
	fib_node extract_min(){
		extracted = min_node;								// save min node
		if (extracted != nullptr) {						// if min node exists (the heap is not empty)
			while (extracted->child_list.size()) {		// move all its children to rootlist since min node will be removed
				child = extracted->child_list.head->left;
				extracted->child_list.remove_node(child);
				child->p = nullptr;
				root_list.push_back(child);
			}
			root_list.extract_node(extracted);			// extract from root_list leaving pointers as they were
			if (extracted == extracted->right) {			// if it was the only node and it has no children
				min_node = nullptr;
			} else {									// else there are still node
				min_node = extracted->right;				// temporary set min node to the righ siblings
				consolidate();
			}
			--nodes;
			addresses->erase(extracted->vertex);
		}
		fib_node x(extracted);				// construct copy of node and delete it
		return x;
	}
	void decrease_key(int vertex, int key) {
		fib_node *x = (*addresses)[vertex];
		if (key < x->key) {
			x->key = key;
			fib_node *y = x->p;
			if (y != nullptr && *x < *y) {
				cut(x, y);
				cascading_cut(y);
			}
			if (*x < *min_node)
				min_node = x;
		}
	}
};

typedef std::vector<node> edges;
typedef std::vector<edges> graph;