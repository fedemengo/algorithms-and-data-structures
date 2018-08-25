#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <fstream>
using namespace std;

#define MOD 100
const int INF = 2e9;

class dsu {
private:
    std::vector<int> parent;
    std::vector<int> size;
	unsigned long long _sets;
public:
    dsu(int size) : parent(size), size(size, 0) {
        for(int i=0; i<size; ++i){
            parent[i] = i;
        }
		_sets = size;
    }

    int find(int x){
        // Path compression
        if(parent[x] != x){
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

	int sets() { return _sets; }

    void unite(int x, int y){
		int set_x = find(x);
		int set_y = find(y);
        if(set_x != set_y){
            // Union by rank
            if(size[set_x] > size[set_y]){
                parent[set_y] = set_x;
            } else {
                parent[set_x] = set_y;
            } 
            if(size[set_x] == size[set_y]){
                size[set_y]++;
            }
			_sets--;
        }
    }
};

class edge {
public:
	int wgt;
	int src;
	int dst;
	
	edge(): wgt(-1), src(-1), dst(-1) {}
	edge(int w, int s, int d): wgt(w), src(s), dst(d) {}
	
	friend istream &operator>> (istream &in, edge &e) {
		in >> e.src >> e.dst >> e.wgt;
		--e.src;
		--e.dst;
		return in;
	}
};

int mst(int V, vector<edge> &edges, vector<pair<int,int>> &v){
	dsu djsets(V);
	v.reserve(V);
	int w = 0;
	while(djsets.sets() > 1){
		vector<edge> best(V, {INF, -1, -1});
		for(auto &e: edges){
			if(djsets.find(e.src) == djsets.find(e.dst))
				continue;
			if(best[djsets.find(e.src)].wgt >  e.wgt)
				best[djsets.find(e.src)] = e;
			if(best[djsets.find(e.dst)].wgt >  e.wgt)
				best[djsets.find(e.dst)] = e;
		}
		for(auto &x: best){
			if(x.wgt != INF && djsets.find(x.src) != djsets.find(x.dst)){
				djsets.unite(x.src, x.dst);
				v.push_back({x.src, x.dst});
				w += x.wgt;
			}
		}
	}
	return w;
}

int main(int argc, char *argv[]){
	freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

	int V, E;
	cin >> V >> E;

    vector<edge> edges(E);
	vector<pair<int,int>> v;
	for(edge &e: edges){
		cin >> e;
	}

	cout << mst(V, edges, v) << endl;

	for(auto &x: v)
		cout << x.first + 1 << " " << x.second + 1 << endl;

    return 0;
}
