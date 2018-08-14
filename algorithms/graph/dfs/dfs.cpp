/**
 *
 * Time Complexity O(V+E)
 *
 */

#include <iostream>
#include <cstring>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <queue>
using namespace std;

#define MOD 100
#define INF 2e9

using graph = vector<vector<int>>;

queue<int> order;

void dfs_visit(int s, graph &G, vector<bool> &visited){
	visited[s] = true;
    order.push(s);
	for(int u : G[s]){
		if(!visited[u]){
			dfs_visit(u, G, visited);
		}
	}
}

void dfs(graph &G){
    vector<bool> visited(G.size(), false);
    for(int i=0; i<G.size(); ++i){
		if(!visited[i]){
			dfs_visit(i, G, visited);
		}
	}
}

void test_equal(queue<int> &q, int x1) {
    int x2 = q.front();
    q.pop();

	if(x1 != x2){
		throw std::invalid_argument("Expected node " + std::to_string(x1) + " but got " + std::to_string(x2));
	}
}

int main(int argc, char *argv[]){

    vector<unsigned> dist;
    graph G(5);

    G[0].push_back(1);
    G[0].push_back(2);
    G[0].push_back(4);
    G[1].push_back(2);
    G[1].push_back(3);
    G[1].push_back(1);
    G[2].push_back(0);
    G[2].push_back(2);
    G[2].push_back(3);
    G[3].push_back(1);
    G[3].push_back(3);
    G[3].push_back(4);
    G[4].push_back(2);
    G[4].push_back(3);

    dfs(G);

    try {

        test_equal(order, 0);        
        test_equal(order, 1);        
        test_equal(order, 2);        
        test_equal(order, 3);        
        test_equal(order, 4);        
        
        std::cout << "OK" << std::endl;
	} catch (std::exception &e) {
		std::cout << "ERROR" << std::endl;
		std::cout << e.what() << std::endl;
	}

    return 0;
}
