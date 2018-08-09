#include <iostream>
#include <cstring>
#include <ctime>
#include <cstdlib>
#include <vector>
using namespace std;

#define MOD 100
#define INF 2e9

typedef vector<int> graph;

graph *directed_Graph(int nodes, int sparsity);
void print_graph(int nodes, graph *G);

graph *transpose(graph *G, int nodes){
	graph *Gt = new graph[nodes];
	for(int i=0; i<nodes; ++i){
		for(int j=0; j<G[i].size(); ++j){
			Gt[G[i][j]].push_back(i);
		}
	}
	return Gt;
}

vector<int> topo_order;
int *SCC;
int SCC_id = 0;

void Kosaraju_SCC_DFS(int source, graph *G, bool *visited, bool record){
	visited[source] = true;
	for(int i=0; i<G[source].size(); ++i){
		if(!visited[G[source][i]]){
			Kosaraju_SCC_DFS(G[source][i], G, visited, record);
		}
	}
	if(record) 
		topo_order.push_back(source);
	else 
		SCC[source] = SCC_id;
}

void Kosaraju(int nodes, graph *G, graph *Gt){
	SCC = new int[nodes];
	bool *visited = new bool[nodes];
	for(int i=0; i<nodes; ++i)
		visited[i] = false;

	for(int i=0; i<nodes; ++i)
		if(!visited[i])
			Kosaraju_SCC_DFS(i, G, visited, true);

	for(int i=0; i<nodes; ++i)
		visited[i] = false;

	for(int i=nodes-1; i>-1; --i){
		if(!visited[topo_order[i]]){
			++SCC_id;
			Kosaraju_SCC_DFS(topo_order[i], Gt, visited, false);
		}
	}
}

int main(int argc, char *argv[]){

    srand(time(0));
    int nodes = atoi(argv[1]), sparsity = atoi(argv[2]);

    graph *G = directed_Graph(nodes, sparsity);
    graph *Gt = transpose(G, nodes);

    Kosaraju(nodes, G, Gt);

    print_graph(nodes, G);
    cout << "\n";
    print_graph(nodes, Gt);
    cout << "\n";

    for(int i=0; i<nodes; ++i){
    	cout << "Node " << i << " belongs to SCC #" << SCC[i] << "\n";
    }
    
    return 0;
}

graph *directed_Graph(int nodes, int sparsity){
	graph *G = new graph[nodes];
	for(int i=0; i<nodes; ++i){
		for(int j=0; j<nodes; ++j){
			if(!(rand() % sparsity)){
				G[i].push_back(j);
			}
		}
	}
	return G;
}

void print_graph(int nodes, graph *G){
	for(int i=0; i<nodes; ++i){
        cout << "Node " << i << ": ";
        for(int j=0; j<G[i].size(); ++j){
                cout << G[i][j];
                if(j < G[i].size()-1){
                        cout << ", ";
                }
        }
        cout << "\n";
    }
}