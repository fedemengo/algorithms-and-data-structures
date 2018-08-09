//O(NlogN) suffixarray - add a char at the end
struct suffarray{
  vi sa;
  string &s;
  void radix_sort(vi &rank, int k){
    vi count(max(256, (int)sa.size()));
    for(int i : sa) count[((i + k) < rank.size() ? rank[i+k]+1 : 1)]++;
    int last = 0;
    for(int &i : count) i = last += i;
    vi temp(sa.size());
    for(int i : sa) temp[count[(i + k < rank.size() ? rank[i + k] : 0)]++] = i;
    fill(count.begin(), count.end(), 0);
    for(int &i : rank) count[i+1]++;
    last = 0;
    for(int &i : count) i = last += i;
    for(int i : temp) sa[count[rank[i]]++] = i;
  }
  void update_ranks(vi &rank, int k){
    vi old(rank);
    int r = rank[sa[0]] = 0;
    for(int i = 1; i < rank.size(); i++)
      rank[sa[i]] = (old[sa[i]] == old[sa[i-1]] && (sa[i] + k < old.size() ?
      old[sa[i]+k] : 0) <= (sa[i-1]+k < old.size() ? old[sa[i-1]+k] : 0)) ? r : ++r;
  }
  suffarray(string &s) : sa(s.size()), s(s){
    int n = s.size();
    for(int i = 0; i < n; i++)
      sa[i] = i;
    vi rank(s.size());
    for(int i = 0; i < s.size(); i++)
      rank[i] = s[i];
    for(int k = 1; k <= n; k<<=1){
      radix_sort(rank, k);
      update_ranks(rank, k);
      if(rank[sa.back()] == s.size()-1) break;
    }
  }
};