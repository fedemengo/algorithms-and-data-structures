#include <iostream>
#include <cstring>
#include <ctime>
#include <cstdlib>
#include <queue>
using namespace std;

#define MOD 100
#define INF 2e9

typedef vector<vector<int>> graph;

void BFS(int s, graph &G, vector<unsigned> &dist){
	dist.resize(G.size(), INF);
	queue<int> Q;
	Q.push(s);
	dist[s] = 0;

	while(!Q.empty()){
		int u = Q.front(); Q.pop();
		for(int &v : G[u]){
			if(dist[v] == INF){
				dist[v] = dist[u] + 1;
				Q.push(v);
			}
		}
	}
}

int main(int argc, char *argv[]){

    srand(time(0));
    int V = atoi(argv[1]), sparsity = atoi(argv[2]), s = atoi(argv[3]);
    vector<unsigned> dist;
    graph G(V);

    for(auto &node : G){
        for(int i=0; i<V; ++i){
            if(rand()%2)
                node.push_back(i);
        }
    }
    
    BFS(s, G, dist);

    return 0;
}
