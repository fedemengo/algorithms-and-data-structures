#include<bits/stdc++.h>
using namespace std;
const int RUN = 128;
#define MOD 1000

void insertion_sort(vector<int> &v, int left, int right){
    for(int i=left+1; i<right; ++i){
        int key = v[i];
        int j = i-1;
        while(j >= left && key < v[j]){
            v[j+1] = v[j];
            --j;
        }
        v[j+1] = key;
    }
}

void merge(vector<int> &v, int p, int q, int r){
    int n1 = q-p, n2 = r-q, i = 0, j = 0, k = p;
    std::vector<int> L(v.begin()+p, v.begin()+q);
    std::vector<int> R(v.begin()+q, v.begin()+r);

    while(i < n1 && j < n2) {
        if(L[i] <= R[j]){
            v[k] = L[i++];
        } else {
            v[k] = R[j++];
        }
        ++k;
    }
    while(i < n1) 
        v[k++] = L[i++];
    while(j < n2)
        v[k++] = R[j++];
}

void tim_sort(vector<int> &v){

    for (int i=0; i <v.size(); i+=RUN)
        insertion_sort(v, i, min((i+RUN), (int)(v.size())));
 
    // start merging from size RUN (or 32). It will merge
    // to form size 64, then 128, 256 and so on ....
    for (int size = RUN; size < v.size(); size<<=1){
        // pick starting point of left sub array. We
        // are going to merge arr[left..left+size-1]
        // and arr[left+size, left+2*size-1]
        // After every merge, we increase left by 2*size
        for (int left = 0; left < v.size(); left += (size<<1)){
            // find ending point of left sub array
            // mid+1 is starting point of right sub array
            int mid = left + size;
            int right = max(mid, min((left + (size<<1)), (int)(v.size())));          // added max
            // merge sub array arr[left.....mid] &
            // arr[mid+1....right]
            merge(v, left, mid, right);
        }
    }
}
 
// Driver program to test above function
int main(int argc, char *argv[]){
    srand(time(0));
    vector<int> v(atoi(argv[1]));

    for(int &x : v)
        x = rand() % MOD;
    vector<int> u(v);

    time_t start = clock();
    sort(u.begin(), u.end());
    printf("std::sort = %lf\n", (double)(clock()-start)/(double)CLOCKS_PER_SEC);

    start = clock();
    tim_sort(v);
    printf("tim_sort = %lf\n", (double)(clock()-start)/(double)CLOCKS_PER_SEC);

    for(int i=0; i<v.size(); ++i)
        if(v[i] != u[i]){
            printf("diomerda\n"); break;
        }
 
    return 0;
}