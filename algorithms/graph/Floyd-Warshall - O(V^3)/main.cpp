#include <iostream>
#include <cstring>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <vector>
using namespace std;

#define MOD 100
#define INF 1e9

ifstream fin("input.txt");
ofstream fout("output.txt");

typedef vector<vector<int>> graphMatrix;

void Floyd_Warshall(graphMatrix &G){	
	for(int k=0; k<G.size(); ++k){
		for(int i=0; i<G.size(); ++i){
			for(int j=0; j<G.size(); ++j)
				G[i][j] = min(G[i][j], G[i][k] + G[k][j]);
		}
	}
}

int main(int argc, char *argv[]){
	ios::sync_with_stdio(0);
	fin.tie(0);

	int V, E, s, d, v, u, w;
	vector<unsigned> dist;
	fin >> V >> E >> s >> d;
	
	graphMatrix G(V, vector<int>(V, INF));

	for(int i=0; i<E; ++i){
		fin >> v >> u >> w;
		G[v][u] = w;
		//G[u][v] = w;
	}

    Floyd_Warshall(G);
    
    return 0;
}
