#include <iostream>
#include <cstring>
#include <ctime>
#include <cstdlib>
#include <queue>
using namespace std;

#define MOD 100
#define INF 2e9

typedef vector<vector<int>> graph;

void DFS(int s, graph &G, vector<bool> &visited){
	visited[s] = true;
	for(int u : G[s]){
		if(!visited[u]){
			DFS(u, G, visited);
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
    
    vector<bool> visited(G.size(), false);
	for(int i=0; i<G.size(); ++i){
		if(!visited[i])
			DFS(i, G, visited);
	}

    return 0;
}
