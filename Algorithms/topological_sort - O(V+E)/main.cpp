#include <fstream>
#include <cstring>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <deque>
using namespace std;

#define MOD 100
#define INF 2e9

ifstream fin("input.txt");
ofstream fout("output.txt");

typedef std::vector<vector<int>> graph;

void DFS(int s, graph &G, vector<bool> &visited, deque<int> &topo_order){
	visited[s] = true;
	for(int i=0; i<G[s].size(); ++i){
		if(!visited[G[s][i]]){
			DFS(G[s][i], G, visited, topo_order);
		}
	}
	topo_order.push_front(s);
}

void topological_sort(graph &G, deque<int> &topo_order){
	vector<bool> visited(G.size(), false);
	for(int i=0; i<G.size(); ++i){
		if(!visited[i]){
			DFS(i, G, visited, topo_order);
		}
	}
}

int main(int argc, char *argv[]){
    int V = atoi(argv[1]), E = atoi(argv[2]), v, u;
	vector<unsigned> dist;
	fin >> V >> E;
	graph G(V);

	deque<int> topo_order;

	for(int i=0; i<E; ++i){
		fin >> v >> u;
		G[v].push_back(u);
	}

    topological_sort(G, topo_order);

    for(auto x: topo_order)
    	fout << x << " ";
    fout << "\n";

    return 0;
}
