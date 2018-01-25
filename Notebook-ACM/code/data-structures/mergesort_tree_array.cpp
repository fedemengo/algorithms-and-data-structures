typedef vector<int> vi;
vi merge(vi &a, vi &b){
  vi v;
  int l = 0, r = 0;
  v.reserve(a.size() + b.size());
  while(l + r < a.size() + b.size()){
    if(l == a.size())
      v.push_back(b[r++]);
    else if(r == b.size() || a[l] < b[r])
      v.push_back(a[l++]);
    else
      v.push_back(b[r++]);
  }
  return move(v);
}
int leftMost(vi &v, int x, int a = -1, int b = -1){
  if(a == -1) a = 0, b = v.size();
  if(a+1 == b) return a;
  int m = (a + b)/2;
  if(v[m] < x) return leftMost(v, x, m, b);
  return leftMost(v, x, a, m);
}
int rightMost(vi &v, int x, int a = -1, int b = -1){
  if(a == -1) a = 0, b = v.size();
  if(a == b) return a;
  int m = (a + b)/2;
  if(v[m] > x) return rightMost(v, x, a, m);
  return rightMost(v, x, m+1, b);
}
constexpr int right(int i){ return i*2 + 2; }
constexpr int left(int i){ return i*2 + 1; }
constexpr int dad(int i){ return (i-1)/2; }
struct mt_node{
  vi v;
  mt_node(){}
  void build(int i, vi &source, vector<mt_node> &tree){
    int pos = i - source.size() + 1;
    if(pos >= 0)
      v.push_back(source[pos]);
    else
      v = merge(tree[left(i)].v, tree[right(i)].v);
  }
  int count(int k){
    int l = leftMost(v, k);
    int r = rightMost(v, k);
    return max(0 , r-l-1);
  }
};
struct mergetree{
  vector<mt_node> v;
  mergetree(vi &source){
    v.resize((1<<(int)(ceil(log2(source.size())+1)))-1);
    for(int i = source.size()*2 - 2; i >= 0; i--)
      v[i].build(i, source, v);
  }
  const int nullQuery = 0;
  int qa, qb, qx;
  int count(int i, int l, int r){
    if(l >= qa && r <= qb) return v[i].count(qx);
    if(l > qb || r < qa) return nullQuery; 
    int m = (l+r)/2;
    return count(left(i), l, m) + count(right(i), m+1, r);
  }
  int query(int a, int b, int x){
    qa = a, qb = b, qx = x;
    int l = 0, r = v.size()/2;
    return count(0, l, r);
  }
};