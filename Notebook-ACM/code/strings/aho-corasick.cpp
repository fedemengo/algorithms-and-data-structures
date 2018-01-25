//multiple pattern matching, care for "sonda"
struct node{
  node *parent, *fall, *output;
  char c = '$';
  bool ending = 0; //make this int for speed  
  unordered_map<char, node*> f;
  node(node *p, char c) : parent(p), c(c){}
  node(){}
};
struct aho_trie{
  node *root = new node();
  void insert(string s){
    node *curr = root;
    for(char c : s)
      curr = curr->f.count(c) ? curr->f[c] : (curr->f[c] = new node(curr, c));
  }
  void set_falls(){
    queue<node*> q;
    q.push(root);
    while(!q.empty()){
      node *curr = q.front(); q.pop();
      for(auto &x : curr->f)
        q.push(x.second);
      if(curr == root) continue;
      curr->fall = curr->parent->fall;
      while(curr->fall->f.count(curr->c) == 0 && curr->fall != root)
        curr->fall = curr->fall->fall;
      if(curr->fall != curr->parent && curr->fall->f.count(curr->c))
        curr->fall = curr->fall->f[curr->c];
      curr->output = curr->fall->ending ? curr->fall : curr->fall->output;
    }
  }
  int query(string s){
    node *stato = root;
    int ans = 0;
    for(char c : s){
      while(stato != root && stato->f.count(c) == 0)
        stato = stato->fall;
      if(stato->f.count(c))
        stato = stato->f[c];
      node *sonda = stato->output;
      while(sonda != root)
        ans++, sonda = sonda->output;
      ans += stato->ending;
    }
    return ans;
  }
  aho_trie(){ root->parent = root->fall = root->output = root; }
};