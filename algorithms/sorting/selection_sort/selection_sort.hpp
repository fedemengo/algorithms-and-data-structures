#include <vector>

void selection_sort(std::vector<int> &v, int N){
    for(int i=0; i<N-1; ++i){
        int min = i;
        for(int j=i+1; j<N; ++j){
            if(v[j] < v[min])
                min = j;
        }
		std::swap(v[i], v[min]);
    }
}


