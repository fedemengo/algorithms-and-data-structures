
#include <iostream>
#include <functional>
#include <stack>

template <typename KEY, typename DATA>
class skew_heap {
private:
	template <typename KEY_NODE, typename DATA_NODE>
	class skew_heap_node {
	public:
		KEY_NODE key;
		DATA_NODE data;
		skew_heap_node<KEY_NODE, DATA_NODE> *left;
		skew_heap_node<KEY_NODE, DATA_NODE> *right;

		skew_heap_node<KEY_NODE, DATA_NODE>(KEY_NODE k, DATA_NODE d) : key(k), data(d), left(nullptr), right(nullptr) {}

		bool operator< (const skew_heap_node<KEY_NODE, DATA_NODE> &parent){ return key < parent.key; }
		bool operator> (const skew_heap_node<KEY_NODE, DATA_NODE> &parent){ return key > parent.key; }
	};

	// merge on the right tree of both root
	void merge(skew_heap_node<KEY, DATA> *root2){
		// if current heap is empty, set the other heap root as the root
		if(root == nullptr){
			root = root2;
			return;
		}
		
		if(root2 == nullptr){
			return;
		}

		skew_heap_node<KEY, DATA> *right_root1, *right_root2;
		if(compare(root->key, root2->key)){
			// current root should be on top, the other heap should be
			// merge in the current root right tree
			right_root2 = root2;
		} else {
			// the other root goes on top, merge the current root
			// to the other root's right tree
			right_root2 = root;
			root = root2;
		}
		right_root1 = root->right;

		skew_heap_node<KEY, DATA> *curr_root = root;
		while(right_root1 != nullptr && right_root2 != nullptr){
			// exchange left and rigth subtree
			curr_root->right = curr_root->left;
			// right_root1 will always hold the value of the next node to merge because of thw swap
			if(!compare(right_root1->key, right_root2->key))
				std::swap(right_root1, right_root2);
		
			curr_root->left = right_root1;		// insert in the left subtree
			curr_root = curr_root->left;		// move the root down to the left
			right_root1 = right_root1->right;	// move down the next_right_root
		}

		if(right_root1 == nullptr){
			curr_root->right = right_root2;
		} else {
			curr_root->right = right_root1;
		}
	}

	skew_heap_node<KEY, DATA> *root;
	ssize_t _size;
	std::function<bool(KEY, KEY)> compare;

public:
	skew_heap(std::function<bool(KEY, KEY)> cmp) : root(nullptr), _size(0), compare(cmp) {}

	void push(KEY k, DATA d){
		skew_heap_node<KEY, DATA> *n = new skew_heap_node<KEY, DATA>(k, d);
		merge(n);
		++_size;
	}

	std::pair<KEY, DATA> top(){
		return {root->key, root->data};
	}

	void pop(){
		skew_heap_node<KEY, DATA> *heap1, *heap2, *top;
		top = root;

		heap1 = root->left;
		heap2 = root->right;
		root = heap1;
		merge(heap2);
		--_size;

		delete top;
	}

	void merge(skew_heap<KEY, DATA> &heap){
		merge(heap.root);
	}

	int size(){
		return _size;
	}
};
