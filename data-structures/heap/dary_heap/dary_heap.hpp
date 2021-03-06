
#include <iostream>
#include <vector>
#include <unordered_map>
#include <functional>

/**
 * 
 *  the KEY should be comparable, it's used to arrange elements
 *  the DATA it's additional data carried by each element, for
 *  this reason each element's DATA should be different from one another
 *  while it's reasonable to have the same KEY for multiple elements
 *
 **/

template <typename KEY, typename DATA>
class dary_heap {
private:
	template <typename KEY_NODE, typename DATA_NODE>
	class node {
	public:
		bool init;
		KEY_NODE key;
		DATA_NODE data;

		node(KEY_NODE k, DATA_NODE d) : init(false), key(k), data(d) {}

		bool operator< (const node &x){ return key < x.key; }
		bool operator> (const node &x){ return key > x.key; }
	};

	template <typename KEY_NODE, typename DATA_NODE>
	class iterator {
	private:
		int index;
		node<KEY_NODE, DATA_NODE> *ptr;
	public:
		iterator(node<KEY_NODE, DATA_NODE> *ptr) : index(0), ptr(ptr){}
		iterator &operator++() {
			ptr = v[index++];
			return *this; 
		}
		iterator &operator++(int) {
			iterator *it = this;
			ptr = v[index++];
			return *it; 
		}
		bool operator!=(const iterator &other) { return ptr != other.ptr; }
		std::pair<KEY_NODE, DATA_NODE> &operator*() { return {ptr->key, ptr->data}; }
	};

	int _size;
	size_t _length;
	int n_child;
	std::vector<node<KEY, DATA> *> v;
	std::unordered_map<DATA, int> indeces;
	std::function<bool(KEY, KEY)> compare;

	void heapify(int index){
		int child_index, largest = index;
		for(int i=0; i<n_child; ++i){
			child_index = child(index, i+1);
			if(child_index < _size && compare(v[child_index]->key, v[largest]->key)) 
				largest = child_index;
		}
		if(largest != index){
			heap_swap(index, largest);
			heapify(largest);
		}
	}

	void heap_swap(int x, int y){
		std::swap(v[x], v[y]);
		indeces[v[x]->data] = x;
		indeces[v[y]->data] = y;
	}

	int parent(int i) { return (int)((i-1) / n_child); }
	int child(int i, int ith) { return (int)(i * n_child + ith); };

	void build_heap(){
		_size = length;
		for(int i=_size/2; i>-1; --i)
			heapify(i);
	}

protected:
	void update_key(KEY new_key, DATA data){
		int index = indeces[data];
		if(v[index]->init && compare(v[index]->key, new_key)) 
			return;

		node<KEY, DATA> *tmp = v[index];
		tmp->key = new_key;
		tmp->init = true;
		while(index > 0 && !compare(v[parent(index)]->key, tmp->key)){
			v[index] = v[parent(index)];
			indeces[v[index]->data] = index;
			index = parent(index);
		}
		v[index] = tmp;
		indeces[v[index]->data] = index;
	}

public:
	dary_heap(int D, std::function<bool(KEY, KEY)> cmp) : _size(0), _length(0), n_child(D), v(), indeces(), compare(cmp) {}

	void push(KEY key, DATA data){
		node<KEY, DATA> *x = new node<KEY, DATA>(key, data);
		if(_size < v.size()){
			v[_size] = x;
		} else {
			v.push_back(x);
		}
		v[_size]->data = data;
		indeces[x->data] = _size;
		++_size;
		update_key(x->key, x->data);
	}

	std::pair<KEY, DATA> top(){ 
		return {v[0]->key, v[0]->data}; 
	}

	void pop(){
		--_size;
		indeces.erase(v[0]->data);
		v[0] = v[_size];
		v.pop_back();
		indeces[v[0]->data] = 0;
		heapify(0);
	}

	int size() { return _size; }

	int length() { return _length; }

	void heap_sort(){
		//build_heap(); build only if passing a vector
		while(_size > 0) {
			--_size;
			++_length;
			node<KEY, DATA> *x = v[0];
			indeces.erase(v[0]->data);
			v[0] = v[_size];
			indeces[v[0]->data] = 0;
			heapify(0);
			v[_size] = x;
		}
	}

	iterator<KEY, DATA> begin() const { return iterator<KEY, DATA>(v.begin()); }
	iterator<KEY, DATA> end() const { return iterator<KEY, DATA>(v.end()); }

	std::pair<KEY, DATA> operator[] (int i) { return {v[i]->key, v[i]->data}; }
};
