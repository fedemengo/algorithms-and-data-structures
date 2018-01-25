#include <vector>
#include <cstdlib>
#include <ctime>

typedef std::vector<std::pair<int, int>> edge;
typedef std::vector<edge> graph;

int main(int argc, char const *argv[]){
	
	srand(time(0));
	int N = atoi(argv[1]), E = atoi(argv[2]), i=0;
	graph G(N, edge(E));
	edge Edges;

	while(i < E){
		int u = rand() % N, v = rand() % N, w = rand() % 100;
		//G[u].push_back({v, w});
		edge.push_back({})
	}



	return 0;
}