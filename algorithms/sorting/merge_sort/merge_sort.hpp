#include <vector>
#include <functional>

long long inversion = 0;

template<typename T>
void mergesort(std::vector<T> &v, int p, int r, std::function<bool(T, T)> compare){
	
	if(r - p > 1){
		int q = (p+r)/2;
		mergesort(v, p, q, compare);
		mergesort(v, q, r, compare);

		// merge procedure
		int n1 = q-p, n2 = r-q, i = 0, j = 0, k = p;
		std::vector<T> L(v.begin()+p, v.begin()+q);
		std::vector<T> R(v.begin()+q, v.begin()+r);

		while(i < n1 && j < n2) {
			if(compare(L[i], R[j])){	// should be !compare(R[i], L[i]) for inversions
				v[k] = L[i++];
			} else {
				inversion += L.size() - i;
				v[k] = R[j++];
			}
			++k;
		}
		while(i < n1) v[k++] = L[i++];
		while(j < n2) v[k++] = R[j++];
	}
}

template<typename T>
void merge_sort(std::vector<T> &v,
		std::function<bool(T, T)> compare = [](T e1, T e2){
			return e1 < e2;
		}){
	mergesort(v, 0, v.size(), compare);
}
