#include <iostream>
#include <algorithm>
#include <stdlib.h>
#include <vector>
#include <utility>
#include <fstream>
using namespace std;

#define MOD 100

void selection_sort(vector<int> &v, int N){
    for(int i=0; i<N-1; ++i){
        int min = i;
        for(int j=i+1; j<N; ++j){
            if(v[j] < v[min])
                min = j;
        }
        swap(v[i], v[min]);
    }
}

int main(int argc, char *argv[]){

    srand(time(0));
    int N = atoi(argv[1]);
    vector<int> v(N);
    
    for(int &x : v)
        x = rand() % MOD;
    
    selection_sort(v, N);
    
    for(int& i:v)
        cout << i << " ";
    cout << "\n";
    
    return 0;
}
