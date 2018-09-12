/**
 *
 * Time Complexity O(V+E)
 *
 */

#include <vector>
#include <queue>

using graph = std::vector<std::vector<int>>;

bool dfs_visit(int s, graph &G, std::vector<bool> &visited, std::vector<bool> &exited){
	visited[s] = true;
	for(auto u : G[s]){
		if(visited[u] && !exited[u]){
			return true;
		}
		if(!visited[u] && dfs_visit(u, G, visited, exited))
			return true;
	}
	exited[s] = true;
	return false;
}

bool dfs(graph &G){
    std::vector<bool> visited(G.size(), false);
	std::vector<bool> exited(G.size(), false);

    for(int i=0; i<G.size(); ++i){
		if(!visited[i] && dfs_visit(i, G, visited, exited))
			return true;
	}
	return false;
}
