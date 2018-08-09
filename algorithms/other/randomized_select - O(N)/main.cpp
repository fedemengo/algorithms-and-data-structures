#include <iostream>
#include <algorithm>
#include <stdlib.h>
#include <vector>
#include <utility>
#include <fstream>
using namespace std;

const int MOD = (int)1e9;

int randomized_partition(int v[], int p, int r){
    int p_i = rand() % (r-p) + p, j = p;        // median of 3 improvement
    swap(v[p_i], v[r-1]);
    
    for(int i=p; i<r-1; ++i) {
        if(v[i] <= v[r-1]){
            swap(v[i], v[j]);
            ++j;
        }
    }
    swap(v[j], v[r-1]);
    return j;
}

int random_select(int v[], int p, int r, int index){
    if(p == r)
        return v[p];
    int q = randomized_partition(v, p, r);
    int k = q-p;
    if(index == k)
        return v[q];
    else if(index < k)
        return random_select(v, p, q, index);
    else
        return random_select(v, q, r, index-k);
}

int main(int argc, char *argv[]){
    
    struct rlimit limit_stack;
    limit_stack.rlim_cur = 67104768;
    limit_stack.rlim_max = 67104768;
    setrlimit(RLIMIT_STACK, &limit_stack);

    srand(time(0));
    int N = atoi(argv[1]), index = atoi(argv[2]);
    int v[N];
    
    for(auto &i:v)
        i = rand() % MOD;
    
    int element = random_select(v, 0, N, index);
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
