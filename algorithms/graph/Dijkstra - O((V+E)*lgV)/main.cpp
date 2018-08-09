#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <queue>
#include <utility>
#include <cstring>
#include <ctime>
#include <cstdlib>
using namespace std;

#define MOD 100
#define INF 2e9

ifstream fin("input.txt");
ofstream fout("output.txt");

struct edge {
	int node;
	long long weigth;
	bool operator()(const edge &a, const edge &b) {return a.weigth > b.weigth; }
};

typedef vector<vector<edge>> graph;

void Dijsktra(int s, graph &G, vector<unsigned> &dist){
	dist.resize(G.size(), INF);
	priority_queue<edge, vector<edge>, edge> PQ;
	PQ.push({s, dist[s] = 0});
	while(!PQ.empty()){
		edge u = PQ.top(); PQ.pop();
		if(u.weigth > dist[u.node]) continue;
		for(edge &v : G[u.node]){
			if(dist[v.node] > dist[u.node] + v.weigth){
				dist[v.node] = dist[u.node] + v.weigth;
				PQ.push({v.node, dist[v.node]});
			}
		}
	}
}

int main(int argc, char *argv[]){
	ios::sync_with_stdio(0);
	fin.tie(0);

	int V, E, s, d, v, u, w;
	vector<unsigned> dist;
	fin >> V >> E >> s >> d;
	graph G(V);

	for(int i=0; i<E; ++i){
		fin >> v >> u >> w;
		G[v].push_back({u, w});
	}

	Dijsktra(s, G, dist);
	
	fout << dist[d] << "\n";
    
    return 0;
}
