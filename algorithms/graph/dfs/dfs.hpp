/**
 *
 * Time Complexity O(V+E)
 *
 */

#include <vector>
#include <queue>
#include <stack>

using graph = std::vector<std::vector<int>>;

void dfs_visit(int s, graph &G, std::vector<bool> &visited, std::queue<int> &order){
	visited[s] = true;
    order.push(s);
	for(auto u : G[s]){
		if(!visited[u]){
			dfs_visit(u, G, visited, order);
		}
	}
}

void dfs_rec(graph &G, std::queue<int> &order){
    std::vector<bool> visited(G.size(), false);
    for(int i=0; i<G.size(); ++i){
		if(!visited[i]){
			dfs_visit(i, G, visited, order);
		}
	}
}

void dfs_iter(graph &G, std::queue<int> &order){
	std::stack<int> nodes;
	std::vector<bool> visited(G.size(), false);

	for(int i=G.size(); i>0; --i)
		nodes.push(i-1);

	while(nodes.size()){
		int n = nodes.top(); nodes.pop();
		if(visited[n])
			continue;
		
		visited[n] = true;
		order.push(n);

		for(int i=G[n].size(); i>0; --i)
			nodes.push(G[n][i-1]);
	}
}
