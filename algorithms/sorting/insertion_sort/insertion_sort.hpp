#include <vector>

void insertion_sort(std::vector<int> &v){
	for(int i=1; i<v.size(); ++i){
        int key = v[i];
        int j = i-1;
        while(j >= 0 && key < v[j]){
            v[j+1] = v[j];
            --j;
        }
        v[j+1] = key;
    }
}

