#include <vector>
#include <functional>

template<typename T>
void heapify(std::vector<T> &v, int best, int size, std::function<bool(T, T)> compare){
	int prev = -1, left, right;
	while(best != prev) {
		prev = best;

		left = 2 * best + 1, right = 2 * best + 2;
		if(left < size && compare(v[best], v[left]))
			best = left;
		if(right < size && compare(v[best], v[right]))
			best = right;

		if(best != prev)
			std::swap(v[best], v[prev]);
	}
}

template<typename T>
void heap_sort(std::vector<T> &v, std::function<bool(T, T)> compare = [](T e1, T e2){ return e1 < e2; }) {
	for(int i=v.size()/2; i>=0; --i)
		heapify(v, i, v.size(), compare);

	int s = v.size();
	while(s--) {
		T elem = v[0];
		v[0] = v[s];
		heapify(v, 0, s, compare);
		v[s] = elem;
	}
}

