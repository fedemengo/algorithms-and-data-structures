#include <cstring>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <utility>
#include <vector>
#include <queue>
#include <stack>
#include <unordered_map>
#include <unordered_set>
using namespace std;

#define MOD 100
#define INF 2e9

struct edge {
	int node;
	long long weigth;
	bool operator()(const edge &a, const edge &b) {return a.weigth > b.weigth; }
};

typedef vector<vector<edge>> graph;

ifstream fin("input.txt");
ofstream fout("output.txt");

int MST_prim(int s, graph &G){
	vector<bool> tested(G.size(), false);
	priority_queue<edge, vector<edge>, edge> PQ;
	
	PQ.push({s, 0});	// original Prim MST doesn't allow to choose a source
	int MSTweight = 0;

	while(!PQ.empty()){
		edge u = PQ.top(); PQ.pop();
		if(!tested[u.node]){
			tested[u.node] = true;
			MSTweight += u.weigth;
			for(edge v: G[u.node]){
				if(!tested[v.node]){
					PQ.push(v);
				}
			}
		}
	}
	return MSTweight;
}

int main(int argc, char *argv[]){

	ios::sync_with_stdio(0);
	//cin.tie(0);
	fin.tie(0);

	int V, E;
	fin >> V >> E;
	graph G(V);

	while(E--){
		int source, dest, weight;
		fin >> source >> dest >> weight;
		G[source].push_back({dest, weight});
		G[dest].push_back({dest, weight});
	}
    
	fout << MST_prim(1, G) << "\n";

    return 0;
}
