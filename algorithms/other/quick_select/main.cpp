#include <iostream>
#include <algorithm>
#include <stdlib.h>
#include <vector>
#include <utility>
#include <fstream>
using namespace std;

const int MOD = (int)1e9;

int partition(int v[], int l, int r){
    int p = rand() % (r-l) + l, j = l;        // median of 3 improvement
    swap(v[p], v[r-1]);
    
    for(int i=l; i<r-1; ++i) {
        if(v[i] <= v[r-1]){
            swap(v[i], v[j]);
            ++j;
        }
    }
    swap(v[j], v[r-1]);
    return j;
}

int quick_select(int v[], int l, int r, int index){
    if(l == r)
        return v[l];
    int q = partition(v, l, r);
    int k = q-l;
    if(index == k)
        return v[q];
    else if(index < k)
        return quick_select(v, l, q, index);
    else
        return quick_select(v, q, r, index-k);
}

int main(int argc, char *argv[]){
    
    srand(time(0));
    int N = atoi(argv[1]), index = atoi(argv[2]);
    int v[N];
    
    for(auto &i:v)
        i = rand() % MOD;
    
    int element = quick_select(v, 0, N, index);
    time_t start, end;
    start = clock();
    cout << index << " -> " << element << "\n";
    end = clock();
    cout << (double)(end-start)/CLOCKS_PER_SEC << "\n";
    start = clock();
    sort(v, v+N);
    cout << index << " -> " << v[index] << "\n";
    end = clock();
    cout << (double)(end-start)/CLOCKS_PER_SEC << "\n";
    
    return 0;
}
