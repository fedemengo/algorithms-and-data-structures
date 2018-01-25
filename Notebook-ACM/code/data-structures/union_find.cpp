struct union_find {
  vector<int> parent, rank;
  union_find(int N) : parent(N, 0), rank(N, 0) {
    for(int i=0; i<N; ++i) 
      parent[i] = i;
  }
  int find_set(int i) {
    return parent[i] == i ? i : (parent[i] = find(parent[i]));
  }
  bool is_same_set(int i, int j) {
    return find_set(i) == find_set(j);
  }
  bool unite(int i, int j) {
    if(!is_same_set(i, j)) {
      int x = find_set(i), y = find_set(j);
      if(rank[x] > rank[y]) p[y] = x;
      else p[x] = y;
      if(rank[x] == rank[y]) ++rank[y];
    }
  }
};
