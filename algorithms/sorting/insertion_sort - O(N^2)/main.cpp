#include <iostream>
#include <algorithm>
#include <stdlib.h>
#include <vector>
#include <utility>
#include <fstream>
using namespace std;

#define MOD 100

void insertion_sort(vector<int> &v, int N){
    for(int i=1; i<N; ++i){
        int key = v[i];
        int j = i-1;
        while(j > -1 && key < v[j]){
            v[j+1] = v[j];
            --j;
        }
        v[j+1] = key;
    }
}

int main(int argc, char *argv[]){
    
    srand(time(0));
    int N = atoi(argv[1]);
    vector<int> v(N);
    
    for(int &x : v)
        x = rand() % MOD;
    
    insertion_sort(v, N);
    
    for(int& i:v)
        cout << i << " ";
    cout << "\n";
    
    return 0;
}
