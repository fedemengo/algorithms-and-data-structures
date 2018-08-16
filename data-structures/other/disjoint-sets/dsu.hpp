#include <vector>

class dsu {
private:
    std::vector<int> parent;
    std::vector<int> size;
public:
    dsu(int size) : parent(size), size(size, 0) {
        for(int i=0; i<size; ++i){
            parent[i] = i;
        }
    }

    int find_set(int x){
        // Path compression
        if(parent[x] != x){
            parent[x] = find_set(parent[x]);
        }
        return parent[x];
    }

    void unite(int x, int y){
        if(find_set(x) == find_set(y)){
            int set_x = find_set(x);
            int set_y = find_set(y);
            // Union by rank
            if(size[set_x] > size[set_y]){
                parent[set_y] = set_x;
            } else {
                parent[set_x] = set_y;
            } 
            if(size[set_x] == size[set_y]){
                size[set_y]++;
            }
        }
    }
};