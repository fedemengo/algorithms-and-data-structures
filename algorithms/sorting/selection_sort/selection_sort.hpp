#include <vector>

void selection_sort(std::vector<int> &v){
    for(int i=0; i<v.size()-1; ++i){
        int min = i;
        for(int j=i+1; j<v.size(); ++j){
            if(v[j] < v[min])
                min = j;
        }
		std::swap(v[i], v[min]);
    }
}


