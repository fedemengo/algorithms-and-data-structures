#include <iostream>
#include <algorithm>
#include <stdlib.h>
#include <vector>
#include <utility>
#include <fstream>
#include <queue>
using namespace std;

const long long INF = 1e15;
vector<long long> dist;

struct edge {
    int node;
    long long weigth;
    bool operator()(const edge &a, const edge &b) {return a.weigth > b.weigth; }
};

typedef vector<vector<edge>> graph;

void SPFA(int s, graph &G, vector<long long> &dist){
    dist.resize(G.size(), INF);
    queue<edge> Q;
    Q.push({s, dist[s] = 0});
    
    vector<bool> inQueue(G.size(), false);
    inQueue[s] = true;
    
    while (!Q.empty()) {
        edge u = Q.front(); Q.pop();
        inQueue[u.node] = false;
        for(edge &v: G[u.node]){
            if(dist[v.node] > dist[u.node] + v.weigth){
                dist[v.node] = dist[u.node] + v.weigth;
                if(!inQueue[v.node]){
                    Q.push({v.node, dist[v.node]});
                    inQueue[v.node] = true;
                }
            }
        }
    }
}

int main(int argc, char *argv[]){
    
    srand(time(0));
    int V = atoi(argv[1]), sparsity = atoi(argv[2]), s = 0;
    
    graph G(V);
    vector<long long> dist;

    for(auto &node : G){
        for(int i=0; i<V; ++i){
            if(rand()%2)
                node.push_back({i, rand()%50});
        }
    }
       
    SPFA(s, G, dist);
    
    return 0;
}
