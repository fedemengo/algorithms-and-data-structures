#include <vector>

void heapify(std::vector<int> &v, int best, int size){
	int prev = -1, left, right;
	while(best != prev) {
		prev = best;
		left = 2 * best + 1, right = 2 * best + 2;
		if(left < size && v[left] > v[best])
			best = left;
		if(right < size && v[right] > v[best])
			best = right;

		if(best != prev)
			std::swap(v[best], v[prev]);
	}
}

void heap_sort(std::vector<int> &v) {
	for(int i=v.size()/2; i>=0; --i)
		heapify(v, i, v.size());

	for(int s=v.size(); s>+0; --s) {
		int elem = v[0];
		v[0] = v[s-1];
		heapify(v, 0, s-1);
		v[s-1] = elem;
	}
}

