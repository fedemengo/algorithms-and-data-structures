#include <vector>

long long comparison = 0;

int median3(std::vector<int> &v, int p, int r){
	//int start = p, middle = p+(r-p)/2, end = r-1;
	int start = p, middle = (p+r)/2, end = r;
	if(v[start] >= v[middle] && v[start] >= v[end]){
		if(v[middle] >= v[end])
			return middle;
		else
			return end;
	} else if(v[middle] >= v[start] && v[middle] >= v[end]){
		if(v[end] >= v[start])
			return end;	
	} else if(v[middle] >= v[start])
		return middle;
	return start;
}

struct pivot {
	int start;	// skip equal elements
	int end;
};

int partition_lomuto(std::vector<int> v, int p, int r){
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

pivot partition(std::vector<int> &v, int p, int r){
	int index = median3(v, p, r);
	std::swap(v[p], v[index]);
	int j = p+1, pivot = v[p];
	for(int i=p+1; i<r; ++i){
		if(v[i] < pivot){
			std::swap(v[i], v[j]);
			++j;
		}
	}
	std::swap(v[j-1], v[p]);
	int k;
	for(k = j; k<v.size() && v[k] == pivot; ++k);
	return {j-1, k};	// {j-1, j};
}

void insertion_sort(std::vector<int> &v, int p, int r){
	for(int i=p + 1; i<r; ++i){
		int key = v[i];
        int j = i-1;
        while(j > p-1 && key < v[j]){
            v[j+1] = v[j];
            --j;
        }
        v[j+1] = key;
	}
}

// the pivot end to be at index "q", so we dont need to consider it again
void quicksort(std::vector<int> &v, int p, int r){
	if(r - p < 20){
		insertion_sort(v, p, r);
	} else {
		pivot q = partition(v, p, r);
		quicksort(v, p, q.start);
		quicksort(v, q.end, r);
	}
}

void quick_sort(std::vector<int> &v) {
	quicksort(v, 0, v.size());
}
