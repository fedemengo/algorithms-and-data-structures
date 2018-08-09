//ignore the $ sign?
vi lcp_kasai(suffarray &x){
  vi &sa = x.sa;
  string &s = x.s;
  int n = sa.size();
  vi rev(n), lcp(n);
  for(int i = 1; i < n; i++)
    rev[sa[i]] = i;
  for(int i = 1, k = 0; i < n; i++){
    if(rev[i] == n-1) continue;
    int next = sa[rev[i]+1];
    while(i+k < n && next+k < n && s[i+k] == s[next+k])
      k++;
    lcp[rev[i]] = k;
    if(k) k--;
  }
  return lcp;
}
