struct link {
  int node;
  long long weight;
  bool operator()(link &a, link &b) { return a.weight > b.weight; }
};
void dijkstra(int s, vector<vector<link>> &G) {
  vector<int> dist(G.size(), INF);    // local/global
  priority_queue<link, vector<link>, link> PQ;
  PQ.push({s, 0});
  dist[s] = 0;
  while(!PQ.empty()){
    link u = PQ.top(); PQ.pop();
    if(u.weight > dist[u.node]) continue;
    for(link &v : G[u.node]) {
      if(dist[v.node] > dist[u.node] + v.weight){
        dist[v.node] = dist[u.node] + v.weight;
        PQ.push({v.node, dist[v.node]});
      }
    }
  }
}