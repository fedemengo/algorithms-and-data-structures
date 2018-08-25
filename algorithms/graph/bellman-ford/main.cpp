#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <queue>
#include <utility>
#include <cstring>
#include <ctime>
#include <cstdlib>
#include <queue>
#include "../../stuff/graph_gen/graph_gen.cpp"
using namespace std;

#define INF 2e9

typedef pair<int, int> node;
typedef pair<node, int> edge;

void Bellman_Ford(int source, int vertices, vector<edge> edges, int *&dist){
	dist = new int[vertices];
	fill_n(dist, vertices, INF);
	dist[source] = 0;

	for(int i=0; i<vertices-1; ++i){
		for(int j=0; j<edges.size(); ++j){
			int u = edges[j].first.first, v = edges[j].first.second, w = edges[j].second;
			if(dist[v] > dist[u] + w){
				dist[v] = dist[u] + w;
			}
		}
	}
}

void Bellman_Ford_queue(int source, int vertices, Wgraph *G, int *&dist){
    queue<int> Q;

    dist = new int[vertices];
    fill_n(dist, vertices, INF);

    bool *in_queue = new bool[vertices];
    fill_n(in_queue, vertices, false);

    Q.push(source);
    dist[source] = 0;
    in_queue[source] = true;

    while(!Q.empty()){
        int v = Q.front(); Q.pop();
        for(int i=0;i<G[v].size(); ++i){
            int u = G[v][i].first, w = G[v][i].second;
            if(dist[u] > dist[v] + w)
                dist[u] = dist[v] + w;
        }
    }
}



int main(int argc, char *argv[]){

	srand(time(0));
   	int nodes = atoi(argv[1]), sparsity = atoi(argv[2]), source = atoi(argv[3]), *dist;
    Wgraph *G = UNdirected_weighted_Graph(nodes, sparsity, 100);
    vector<edge> E;
    for(int i=0; i<nodes; ++i){
    	for(int j=0; j<G[i].size(); ++j){
    		E.push_back({{i, G[i][j].first}, G[i][j].second});
    	}
    }
    Bellman_Ford(source, nodes, E, dist);

    for(int i=0; i<nodes; ++i){
    	cout << "dist from " << source << ": " << dist[i] << "\n";
    }
    
    return 0;
}
