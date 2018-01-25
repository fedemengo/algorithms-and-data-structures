void floyd_warshall(vvi &adjMatrix, vvi &dist){
  for(int i = 0; i < adjMatrix.size(); i++) {
    dist[i][i] = 0;
    for(int j = 0; j < adjMatrix.size(); j++)
      if (adjMatrix[i][j] != -1)
        dist[i][j] = adjMatrix[i][j];
      else if(i != j)
        dist[i][j] = INF;
  }
  for (int i = 0; i < adjMatrix.size(); i++){
    for (int j = 0; j < adjMatrix.size(); j++) if (j != i){
      for (int k = 0; k < adjMatrix.size(); k++) {
        dist[j][k] = min(dist[j][k], dist[j][i] + dist[i][k]);
      }
    }
  }
}