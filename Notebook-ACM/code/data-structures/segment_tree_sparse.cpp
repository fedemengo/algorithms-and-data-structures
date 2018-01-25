//remember to update merge, nullvalue
struct segment{
  const int nullValue = 0;  // EDIT HERE
  int merge(int a, int b){ return a+b; }
  int l, r, val;
  segment *left, *right;
  segment(int _l, int _r){
    l = _l, r = _r;
    left = right = 0;
    val = nullValue;
  }
  int size(){ return r-l+1; }
  int query(int a, int b){
    if(l >= a && r <= b) return val;
    if(r < a || l > b) return nullValue;
    return merge(left ? left->query(a, b) : nullValue,
          right ? right->query(a, b) : nullValue);
  }
  void update(int pos, int k){
    if(l > pos || r < pos) return;
    if(size() == 1){
      val += k;
      return;
    }
    int m = (l+r)/2;
    if(left == 0)
      left = new segment(l, m);
    if(right == 0)
      right = new segment(m+1, r);
    left->update(pos, k);
    right->update(pos, k);
    sync();
  }
  void sync(){ val = merge(right->val, left->val); }
};

//use this in main
struct sparsetree{
  segment *root;
  sparsetree(int range){
    root = new segment(0, range);
  }
  int rsq(int l, int r){
    return root->query(l, r);
  }
  void update(int i, int k){
    root->update(i, k);
  }
};