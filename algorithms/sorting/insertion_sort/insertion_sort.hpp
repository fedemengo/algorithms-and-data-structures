#include <vector>
#include <functional>

template<typename T>
void insertion_sort(std::vector<T> &v, 
		std::function<bool(T, T)> compare = [](T e1, T e2){
			return e1 < e2;
		}){
	
	for(int i=1; i<v.size(); ++i){
        T key = v[i];
        int j = i-1;
        while(j >= 0 && compare(key, v[j])){
            v[j+1] = v[j];
            --j;
        }
        v[j+1] = key;
    }
}

