#include <iostream>
#include <algorithm>
#include <stdlib.h>
#include <vector>
#include <utility>
#include <fstream>

#define MOD 100
using namespace std;

void swap(int &a, int &b){int t = a; a = b; b = t;}

int partition(int v[], int p, int r){
	int index = rand() % (r-p) + p, x = v[index];
	swap(v[index], v[r-1]);

	int j=p;
	for(int i=p; i<r-1; ++i)
		if(v[i] <= x){
			swap(v[i], v[j]);
			++j;
		}
	
	swap(v[j], v[r-1]);
	return j;
}
// the pivot end to be at index "q", so we dont need to consider it again
void quick_sort(int v[], int p, int r){
	if(p < r-1){
		int q = partition(v, p, r);
		quick_sort(v, p, q);
		quick_sort(v, q+1, r);
	}
}

int main(int argc, char *argv[]){

    srand(time(0));
    int N = atoi(argv[1]);
    int v[N];
    
    for(auto &i:v){
        i = rand() % MOD;
    }

    quick_sort(v, 0, N);
    
    return 0;
}
