#include <iostream>
#include <algorithm>
#include <stdlib.h>
#include <vector>
#include <utility>
#include <fstream>
using namespace std;

#define MOD 100

long long comparison = 0;

int median3(vector<int> &v, int p, int r){
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

pivot partition(vector<int> &v, int p, int r){
	int index = median3(v, p, r);
	swap(v[p], v[index]);
	int j = p+1, pivot = v[p];
	for(int i=p+1; i<r; ++i){
		if(v[i] < pivot){
			swap(v[i], v[j]);
			++j;
		}
	}
	swap(v[j-1], v[p]);
	int k;
	for(k = j; k<v.size() && v[k] == pivot; ++k);
	return {j-1, k};	// {j-1, j};
}

// the pivot end to be at index "q", so we dont need to consider it again
void quick_sort(vector<int> &v, int p, int r){
	if(p < r-1){
		pivot q = partition(v, p, r);
		quick_sort(v, p, q.start);
		quick_sort(v, q.end, r);
	}
}

int main(int argc, char *argv[]){

    srand(time(0));
    int N = atoi(argv[1]);
    vector<int> v(N);
    
    for(auto &i : v)
        i = rand() % MOD;
    vector<int> w(v);

    time_t start = clock();
    sort(w.begin(), w.end());
	printf("std::sort = %lf\n", (double)(clock()-start)/(double)CLOCKS_PER_SEC);
    start = clock();
    quick_sort(v, 0, N);
    printf("quick_sort = %lf\n", (double)(clock()-start)/(double)CLOCKS_PER_SEC);

    printf("%lld\n", comparison);
    
    return 0;
}
