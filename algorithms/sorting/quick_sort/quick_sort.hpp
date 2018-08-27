#include <vector>
#include <functional>

long long comparison = 0;

template<typename T>
int median3(std::vector<T> &v, int l, int r, std::function<bool(T, T)> compare){
	int m = (l+r)/2;
	int max = compare(v[m], v[l]) && compare(v[r], v[l]) ? l : compare(v[r], v[m]) ? m : r;
	int min = compare(v[l], v[m]) && compare(v[l], v[r]) ? l : compare(v[m], v[r]) ? m : r;
	
	return l ^ m ^ r ^ max ^ min;
}

struct pivot {
	int start;	// skip equal elements
	int end;
};

template<typename T>
int partition_lomuto(std::vector<T> v, int p, int r){
	int index = rand() % (r-p) + p, x = v[index];
	std::swap(v[index], v[r-1]);

	int j=p;
	for(int i=p; i<r-1; ++i)
		if(v[i] <= x){
			std::swap(v[i], v[j]);
			++j;
		}
	
	std::swap(v[j], v[r-1]);
	return j;
}

template<typename T>
pivot partition(std::vector<T> &v, int p, int r, std::function<bool(T, T)> compare){
	int index = median3(v, p, r, compare);
	std::swap(v[p], v[index]);
	int j = p+1;
	T pivot = v[p];
	for(int i=p+1; i<r; ++i){
		if(compare(v[i], pivot)){
			std::swap(v[i], v[j]);
			++j;
		}
	}
	std::swap(v[j-1], v[p]);
	int k;
	for(k = j; k<v.size() && v[k] == pivot; ++k);
	return {j-1, k};	// {j-1, j};
}

template<typename T>
void insertion_sort(std::vector<T> &v, int p, int r, std::function<bool(T, T)> compare){
	for(int i=p + 1; i<r; ++i){
		T key = v[i];
        int j = i-1;
        while(j > p-1 && compare(key, v[j])){
            v[j+1] = v[j];
            --j;
        }
        v[j+1] = key;
	}
}

// the pivot end to be at index "q", so we dont need to consider it again
template<typename T>
void quicksort(std::vector<T> &v, int p, int r, std::function<bool(T, T)> compare){
	if(r - p < 20){
		insertion_sort(v, p, r, compare);
	} else {
		pivot q = partition(v, p, r, compare);
		quicksort(v, p, q.start, compare);
		quicksort(v, q.end, r, compare);
	}
}

template<typename T>
void quick_sort(std::vector<T> &v, 
		std::function<bool(T, T)> compare = [](T e1, T e2){ 
			return e1 < e2; 
		}) {
	quicksort(v, 0, v.size(), compare);
}
