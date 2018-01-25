vi spfa(graph &g, int s){
  // check if node already in queue
  queue<int> q;
  q.push(s);
  vi dist(g.size(), inf);
  dist[s] = 0;
  while(!q.empty()){
    int current = q.front();
    q.pop();
    for(edge &e : g[curr])
      if(dist[e.to] > dist[curr] + e.weight){
        dist[e.to] = dist[curr] + e.weight;
        q.push(e.to);
      }
  } return dist;
}