/**
 *
 * Time Complexity O(V+E)
 *
 */

#include <vector>
#include <queue>
#include <stack>
#include <cmath>

using graph = std::vector<std::vector<int>>;

class LCA {
private:
	int t;
	graph G;
	std::vector<std::pair<int, int>> timestaps;
	std::vector<std::vector<int>> ancests;

	void dfs_visit(int s, std::vector<bool> &visited){
		visited[s] = true;
		timestaps[s].first = t++;
		
		for(int u: G[s]){
			if(!visited[u]){
				ancests[u][0] = s;
				dfs_visit(u, visited);
			}
		}
		timestaps[s].second = t++;
	}

	void dfs(int root) {
		std::vector<bool> visited(G.size(), false);

		for(int i=root; i<G.size(); ++i) {
			if(!visited[i]) {
				ancests[i][0] = -1;
				dfs_visit(i, visited);
			}
		}
	}

	void ancestors(){
		bool done = false;
		// up to log n iterations
		for(int i=1; !done; ++i){
			done = true;
			// n iterations
			for(int j=0; j<G.size(); ++j){
				if(i <= ancests[j].size() && ancests[j][i-1] != -1 && i <= ancests[ancests[j][i-1]].size()){
					done = false;
					ancests[j].push_back(ancests[ancests[j][i-1]][i-1]);
				}
			}
		}
	}

	bool is_ancestor(int a, int c){
		return (a == -1) || (timestaps[a].first < timestaps[c].first && timestaps[a].second > timestaps[c].second);
	}

public:
	LCA(graph &g, int root) : t(0), G(g), timestaps(g.size()), ancests(g.size(), std::vector<int>(1, -1)) {
		dfs(root);
		ancestors();
	}

	int lca(int a, int b){
		if(is_ancestor(a, b)) return a;
		if(is_ancestor(b, a)) return b;

		// up to log n iterations
		for(int i=ancests[b].size(); i>0; i--){
			if(!is_ancestor(ancests[b][i-1], a)){
				b = ancests[b][i-1];
			}
		}
		return ancests[b][0];
	}
};
