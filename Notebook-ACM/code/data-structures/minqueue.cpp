class minqueue {
  deque<pair<int,int>> q;
  int l = 0, r = 0;
  void push(int val){
    while(q.size() && q.back().first >= val)
      q.pop_back();
    q.push_back({val, r++});
  }
  void pop(){
    if(q.front().second == l) 
      q.pop_front();
    l++;
  }
  int get_min(){ return q.front().first; }
};