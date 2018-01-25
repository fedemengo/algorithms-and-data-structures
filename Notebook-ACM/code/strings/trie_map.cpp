//trie with O(NlogA) operations
struct t_node{
  char c;
  map<char, t_node*> v;
  t_node (char c = 0) : c(c){}
};
//add with $ if perfect matching
struct trie{
  t_node root;
  void insert(string &s){
    t_node *current = &root;
    for(char c : s){
      if(current->v.count(c) == 0)
        current->v[c] = new t_node(c);
      current = current->v[c];
    }
  }
  bool find(string &s){
    t_node *current = &root;
    for(char c : s){
      if(current->v.count(c) == 0)
        return 0;
      current = current->v[c];
    }
    return 1;
  }
};