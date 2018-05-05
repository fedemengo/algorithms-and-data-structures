#include "bits/stdc++.h"
#include "../../Data-Structures/fibonacci_heap/fibo.cpp"
using namespace std;
const long long INF = 1e15;

vector<long long> dist;

void dijkstra(int s, vector<vector<pair<int, int>>> &G) {
    dist.resize(G.size(), INF);
    fibonacci_heap<long long, int> FH(G.size(), INF);
    
    dist[s] = 0;
    FH.decrease_key(dist[s], s);

    while(!FH.empty()){
        pair<long long, int> u = FH.extract_min();
        for(auto &v : G[u.second]) {
            if(dist[v.second] > dist[u.second] + v.first){
                dist[v.second] = dist[u.second] + v.first;
                FH.decrease_key(dist[v.second], v.second);
            }
        }
    }
}

int main(int argc, char *argv[]){

    int V, E, s, v, u, w;
	cin >> V >> E >> s;

    vector<vector<pair<int, int>>> G(V);
    for(int i=0; i<E; ++i){
        cin >> u >> v >> w;
        G[u].push_back({w, v});
    }
    dijkstra(s, G);

	for(long long &x : dist){
    	cout << x << "\n";
	}

    return 0;
}
