#include <vector>
#include <functional>

template <typename T>
void selection_sort(std::vector<T> &v,
		std::function<bool(T, T)> compare = [](T e1, T e2){
			return e1 < e2;
		}){
    for(int i=0; i<v.size()-1; ++i){
        int min = i;
        for(int j=i+1; j<v.size(); ++j){
            if(compare(v[j], v[min]))
                min = j;
        }
		std::swap(v[i], v[min]);
    }
}


