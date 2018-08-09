struct fenwick_tree {
  int LSB(int x) { return x & (-x); }
  vector<int> ft;
  fenwick_tree(int N) : ft(N+1, 0) {}
  fenwick_tree(vector<int> &s) : ft(s.size()+1, 0) {
    for(int i=1; i<ft.size(); ++i) {
      ft[i] += s[i-1];
      if(i + LSB(i) < ft.size())
        ft[i + LSB(i)] += ft[i];
    }
  }
  int range_sum(int i) {
    int sum = 0;
    for(; i; i-=LSB(i))
      sum += ft[i];
    return sum;
  }
  int range_sum(int l, int r) {   // fenwick 1 to N, range sum [l, r]
    return range_sum(r) - (l == 1 ? 0 : range_sum(l - 1));
  }
  void add(int i, int k) {
    for(; i<ft.size(), i+=LSB(i))
      ft[i] += k;
  }
};
