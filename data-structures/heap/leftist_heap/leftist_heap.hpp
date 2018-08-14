
#include <iostream>
#include <functional>
#include <stack>

template <typename KEY, typename DATA>
class leftist_heap {
private:
	template <typename KEY_NODE, typename DATA_NODE>
	class leftist_heap_node {
	public:
		KEY_NODE key;
		DATA_NODE data;
		leftist_heap_node<KEY_NODE, DATA_NODE> *left;
		leftist_heap_node<KEY_NODE, DATA_NODE> *right;
		int rank;

		leftist_heap_node<KEY_NODE, DATA_NODE>(KEY_NODE k, DATA_NODE d) : key(k), data(d), left(nullptr), right(nullptr), rank(1) {}

		bool operator< (const leftist_heap_node<KEY_NODE, DATA_NODE> &parent){ return key < parent.key; }
		bool operator> (const leftist_heap_node<KEY_NODE, DATA_NODE> &parent){ return key > parent.key; }
	};

	// merge on the right tree of both root
	void merge(leftist_heap_node<KEY, DATA> *root2){
		// if current heap is empty, set the other heap root as the root
		if(root == nullptr){
			root = root2;
			return;
		}
		
		if(root2 == nullptr){
			return;
		}

		leftist_heap_node<KEY, DATA> *right_root1, *right_root2;
		if(compare(root->key, root2->key)){
			// current root should be on top, the other heap should be
			// merged in the current root right tree
			right_root2 = root2;
		} else {
			// the other root goes on top, merge the current root
			// to the other root's right tree
			right_root2 = root;
			root = root2;
		}
		right_root1 = root->right;

		leftist_heap_node<KEY, DATA> *curr_root = root;
	
		while(right_root1 != nullptr && right_root2 != nullptr){
			// save the path in order to rebalance the structure later
			path.push(curr_root);
			// right_root1 will always hold the value of the next node to merge // right_root1 will always hold the value of the next node to merge
			if(!compare(right_root1->key, right_root2->key))
				std::swap(right_root1, right_root2);

			curr_root->right = right_root1;  	// position right_root1 in the right subtree of the current root
			curr_root = curr_root->right;		// move the root down to the right
			right_root1 = right_root1->right; 	// move down the next_right_root
		}

		// positioning the last node
		path.push(curr_root);
		if(right_root1 == nullptr){
			curr_root->right = right_root2;
		} else {
			curr_root->right = right_root1;
		}

		// rebalance
		while(!path.empty()){
			leftist_heap_node<KEY, DATA> *parent = path.top();
			path.pop();

			// if left is closer to a leaf, swap left with right
			if(parent->left == nullptr || parent->left != nullptr && parent->right != nullptr && parent->left->rank < parent->right->rank){
				std::swap(parent->left, parent->right);
			}

			// update parent rank
			if(parent->right != nullptr){
				parent->rank = parent->right->rank + 1;
			} else {
				parent->rank = 1;
			}
		}
	}

	leftist_heap_node<KEY, DATA> *root;
	std::stack<leftist_heap_node<KEY, DATA> *> path;
	ssize_t _size;
	std::function<bool(KEY, KEY)> compare;

public:
	leftist_heap(std::function<bool(KEY, KEY)> cmp) : root(nullptr), _size(0), compare(cmp) {}

	void push(KEY k, DATA d){
		leftist_heap_node<KEY, DATA> *n = new leftist_heap_node<KEY, DATA>(k, d);
		merge(n);
		++_size;
	}

	std::pair<KEY, DATA> top(){
		return {root->key, root->data};
	}

	void pop(){
		leftist_heap_node<KEY, DATA> *heap1, *heap2, *top;
		top = root;

		heap1 = root->left;
		heap2 = root->right;
		root = heap1;
		merge(heap2);
		--_size;

		delete top;
	}

	void merge(leftist_heap<KEY, DATA> &heap){
		merge(heap.root);
	}

	int size(){
		return _size;
	}
};
