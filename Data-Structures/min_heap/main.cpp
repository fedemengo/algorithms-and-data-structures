#include <iostream>
#include <algorithm>
#include <stdlib.h>
#include <vector>
#include <utility>
#include <fstream>
using namespace std;

class node {
public:
	int key;
	int value;
	bool operator< (const node &x){ return value < x.value; }
	bool operator> (const node &x){ return value > x.value; }
};

class min_heap {
private:
	const int INF = (int)1e9;
	size_t _size, _length;
	int n_child;	// MUST BE A POWER OF 2
	std::vector<node> v;
	std::vector<int> indeces;

	void min_heapify(int index){
		int child_index, smallest = index;
		for(int i=0; i<n_child; ++i){
			child_index = child(index, i+1);
			if(child_index < _size && v[child_index] < v[smallest]) smallest = child_index;
		}
		if(smallest != index){
			heap_swap(index, smallest);
			min_heapify(smallest);
		}
	}
	void heap_swap(int x, int y){
		std::swap(v[x], v[y]);
		indeces[v[x].key] = x;
		indeces[v[y].key] = y;
	}
	int parent(int i) { return (int)((i-1) >> (n_child >> 1)); };
	int child(int i, int ith) { return (int)((i << (n_child >> 1)) + ith); };
	void build_min_heap(){
		_size = _length;
		for(int i=_size/2; i>-1; --i)
			min_heapify(i);
	}
public:
	min_heap(int size, int child_number, int value) : _size(0), _length(size), n_child(child_number), v(std::vector<node>(size)), indeces(std::vector<int>(size)){ for(int i=0; i<size; ++i) push({i, value}); }
	~min_heap(){}
	void decrease_key(int key, int value){
		int index = indeces[key];
		if(v[index].value <= value) return;
		node tmp = v[index];
		tmp.value = value;
		while(index > 0 && v[parent(index)] > tmp){
			v[index] = v[parent(index)];
			indeces[v[index].key] = index;
			index = parent(index);
		}
		v[index] = tmp;
		indeces[v[index].key] = index;
	};
	void push(node x){
		v[_size] = x;
		v[_size].value = INF;
		indeces[x.key] = _size;
		++_size;
		//if(x.value != INF)
		decrease_key(x.key, x.value);
	}
	node top(){ return v[0]; }
	void pop(){
		--_size;
		v[0] = v[_size];
		indeces[v[0].key] = 0;
		min_heapify(0);
	}
	bool empty() { return _size == 0;}
	void heap_sort(bool inOrder){
		if(!inOrder)
			build_min_heap();
		for(int i=_length-1; i>-1; --i){
			node x = top(); pop();
			v[i] = x;
		}
	}
};

int main(int argc, char const *argv[]) {
	/* code */
	return 0;
}