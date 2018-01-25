int get_random(){ return rand() << 15 | rand(); }
struct node{
  int priority = get_random();
  int size = 1;
  int value;
  node *l = 0, *r = 0;
  node(int v) : value(v){}
  ~node(){ delete l, r; }
  node* update(){
    size = 1 + (l ? l->size : 0) + (r ? r->size : 0); 
    return this;
  }
  int kth(int k){
    int ls = l ? l->size : 0;
    int rs = r ? r->size : 0;
    if(k < ls) return l->kth(k);
    if(k == ls) return value;
    if(k > ls) return r->kth(k - ls - 1);
  }
};
struct treap{
  node *root = 0;
  ~treap(){ delete root; }
  node *merge(node *l, node *r){
    if(!l) return r;
    if(!r) return l;
    if(l->priority < r->priority){
      l->r = merge(l->r, r);
      return l->update();
    } else {
      r->l = merge(l, r->l);
      return r->update();
    }
  }
  pair<node*, node*> split(node *n, int k){
    if(!n) return {0, 0};
    int lf = n->l ? n->l->size : 0;
    if(k < lf){
      auto f = split(n->l, k);
      n->l = f.second;
      f.second = n->update();
      return f;
    } else {
      auto f = split(n->r, k - lf - 1);
      n->r = f.first;
      f.first = n->update();
      return f;
    }
  }
  //k = position
  void insert(int k, int val){
    auto t = split(root, k-1);
    root = merge(t.first, merge(new node(val), t.second));
  }
  void erase(int k){
    auto t1 = split(root, k - 1);
    auto t2 = split(t1.second, 0);
    if(t2.first) delete(t2.first);
    t1.second = t2.second;
    root = merge(t1.first, t1.second);
  }
  int size(){ return root->size; }
  int operator[](int k){ return root->kth(k); }
};