#include <iostream>
#include <cstdlib>
#define INF (unsigned int)1e9

// data definition
class node {
public:
	unsigned int vertex;
	unsigned int weight;
	bool operator< (const node &x){ return weight < x.weight; }
	bool operator> (const node &x){ return weight > x.weight; }
};

class min_priority_queue{
private:
	node *v;
	int n_child;	// MUST BE A POWER OF 2
	int *indeces;
	int _size;
	void min_heapify(int index) {
		int child_index, smallest = index;
		for(int i=0; i<n_child; ++i){
			child_index = child(index, i+1);
			if(child_index < _size && v[child_index] < v[smallest]) smallest = child_index;
		}
		if(smallest != index){
			swap(index, smallest);
			min_heapify(smallest);
		}
	}
	void swap(int x, int y) {
		std::swap(v[x], v[y]);
		indeces[v[x].vertex] = x;
		indeces[v[y].vertex] = y;
	}
	int parent(int i) { return (int)((i-1) >> (n_child >> 1)); };
	int child(int i, int ith) { return (int)((i << (n_child >> 1)) + ith); };
public:
	min_priority_queue(int size, int n) : _size(0) {
		v = new node[size];
		indeces = new int[size];
		n_child = n;
	}
	~min_priority_queue() {
		delete[] v;
		delete[] indeces;
	}
	void decrease_key(int vertex, int value) {
		int index = indeces[vertex];
		if(v[index].weight <= value) return;
		node tmp = v[index];
		tmp.weight = value;
		while(index > 0 && v[parent(index)] > tmp){
			v[index] = v[parent(index)];			// ex parent became a child
			indeces[v[index].vertex] = index;		// update index of ex parent that has become a child
			index = parent(index);					// levels up
		}
		v[index] = tmp;
		indeces[v[index].vertex] = index;
	}
	void push(node x) {
		v[_size] = x;
		v[_size].weight = INF;
		indeces[x.vertex] = _size++;
		if(x.weight != INF)	
			decrease_key(x.vertex, x.weight);
	}
	node pop(){
		node n = v[0];
		v[0] = v[--_size];
		indeces[v[0].vertex] = 0;
		min_heapify(0);
		return n;
	}
	bool empty() { return _size == 0;}
	int size() { return _size; }
};

int main(int argc, char const *argv[]){
	
	unsigned int N = atoi(argv[1]);
	srand(time(0));

	min_priority_queue PQ(N, 4);

	for(int i=0; i<N; ++i){
		unsigned int v = i, w = rand() % (10*N) + 1;
		node x = (node){v, w};
		std::cout << "Insert: (" << v << ", " << w << ")\n";
		PQ.push(x);
	}

	std::cout << "\n";
	int t = 1000;
	while(t--){
		int v = rand() % N, k = rand() % 10000;
		PQ.decrease_key(v, k);
	}
	/*
	std::cout << "\n";

	unsigned int v, i, new_w;
	std::cin >> v >> new_w;
	for(int i=0; i<PQ.size(); ++i)
		PQ.decrease_key(i, (unsigned int)(rand() % (10*N) + 1));
	PQ.decrease_key(v, new_w);

	std::cout << "\n";

	int time = 0;
	while(PQ.size()){
		node x = PQ.pop();
		std::cout << "Extracted " << x.vertex << ", " << x.weight << "\n";
		for(int i=0; i<PQ.size(); ++i){
			PQ.decrease_key(i, (unsigned int)(rand() % (10*N) + 1));
		}
		++time;
	}
	*/

	while(PQ.size()){
		node x = PQ.pop();
		std::cout << "Extracted " << x.vertex << ", " << x.weight << "\n";
	}

	return 0;
}