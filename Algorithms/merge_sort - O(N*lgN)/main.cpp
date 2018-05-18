#include <iostream>
#include <algorithm>
#include <stdlib.h>
#include <vector>
#include <utility>
#include <fstream>

#define MOD 100
using namespace std;

long long inversion = 0;

void merge(vector<int> &v, int p, int q, int r){
	int n1 = q-p, n2 = r-q, i = 0, j = 0, k = p;
	std::vector<int> L(v.begin()+p, v.begin()+q);
	std::vector<int> R(v.begin()+q, v.begin()+r);

	while(i < n1 && j < n2) {
		if(L[i] <= R[j]){
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

void merge_sort(vector<int> &v, int p, int r) {
	if(r - p > 1){
		int q = (p+r)/2;
		merge_sort(v, p, q);
		merge_sort(v, q, r);
		merge(v, p, q, r);
	}
}

int main(int argc, char *argv[]){

    srand(time(0));
    int N = atoi(argv[1]);
    vector<int> v(N);
    
    for(int i=0; i<N; ++i)
    	v[i] = rand() % MOD;

    merge_sort(v, 0, N);
    
    return 0;
}
