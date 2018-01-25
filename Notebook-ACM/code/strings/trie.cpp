template <class T>
struct trie {
  struct node {
    map<T, node*> children;
    int prefixes, words;
    node() { prefixes = words = 0; } };
  node* root;
  trie() : root(new node()) {  }
  template <class I>
  void insert(I begin, I end) {
    node* cur = root;
    while (true) {
      cur->prefixes++;
      if (begin == end) { cur->words++; break; }
      else {
        T head = *begin;
        typename map<T, node*>::const_iterator it;
        it = cur->children.find(head);
        if (it == cur->children.end()) {
          pair<T, node*> nw(head, new node());
          it = cur->children.insert(nw).first;
        } begin++, cur = it->second; } } }
  template<class I>
  int countMatches(I begin, I end) {
    node* cur = root;
    while (true) {
      if (begin == end) return cur->words;
      else {
        T head = *begin;
        typename map<T, node*>::const_iterator it;
        it = cur->children.find(head);
        if (it == cur->children.end()) return 0;
        begin++, cur = it->second; } } }
  template<class I>
  int countPrefixes(I begin, I end) {
    node* cur = root;
    while (true) {
      if (begin == end) return cur->prefixes;
      else {
        T head = *begin;
        typename map<T, node*>::const_iterator it;
        it = cur->children.find(head);
        if (it == cur->children.end()) return 0;
        begin++, cur = it->second; } } } };

//######################################################################
struct t_node {  //trie with O(NlogA) operations
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
      if(current->v.count(c) == 0) return 0;
      current = current->v[c];
    }
    return 1;
  }
};
