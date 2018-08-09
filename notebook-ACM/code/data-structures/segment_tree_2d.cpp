#define LEFT(i) ((i)*2+1)
#define RIGHT(i) ((i)*2+2)
#define ROOT(i) (((i)-1)/2)
constexpr int closest_pow(int n){ return 1<<(int)ceil(log2(n)); }
/* versione per RMQ (maximum)
  0 based - per modificarlo per le somme, fare attenzione a tutte le funzioni
  UTILIZZO 1D -> [0 based RMQ]
    NB : point update e range add ATTUALMENTE NON si devono mischiare,
      se si decide di utilizzare la lazy propagation usiamo dei range
      add per simulare le point update O mettiamo mano al codice
    rangemax(l, r) = massimo nel range l, r
    update(i, k) = l'indice i diventa k
    range_add(l, r, k) = tutti i valori tra l e r inclusi aumentano di k */
struct rmqtree{
  vector<int> v,u;
  int off, a, b, nullvalue = INT_MIN;
  void update_node(int i){
    v[i] = max(v[LEFT(i)], v[RIGHT(i)]);
  }
  void lazyupdate(int i){
      v[i] += u[i];
      if(i<v.size()/2){
        u[RIGHT(i)] += u[i];
        u[LEFT(i)] += u[i];
      }
      u[i] = 0;
  }
  void build(vi &source){
    v.resize(closest_pow(source.size())*2 - 1, nullvalue);
    u.resize(v.size(),0);
    for(int i=0;i< source.size();i++)
      v[i+v.size()/2]= source[i];
    for(int i=v.size()/2 - 1;i>=0;i--)
      update_node(i);
  }
  rmqtree(vi &source){ build(source); }
  rmqtree(){}
  int rmq(int i,int l ,int r){
    lazyupdate(i);
    if(l>=a && r<=b) return v[i];
    if(r<a || l>b) return nullvalue;
    int m = (l+r)/2;
    return max(rmq(LEFT(i),l,m), rmq(RIGHT(i),m+1,r));
  }
  int rangemax(int qa,int qb){
    a = qa, b = qb;
    return rmq(0,0,v.size()/2);
  }
  void update_up(int i){
    update_node(i);
    if(i!=0) update_up(ROOT(i));
  }
  void update(int i, int k){
    int x = v.size()/2 + i;
    v[x] = k;
    update_up(ROOT(x));
  }
  void range_add(int i,int l,int r){
    lazyupdate(i);
    if(l>=a && r<=b){
      int x=off;
      v[i]+=x;
      if(l!=r)
        u[LEFT(i)] += x/2, u[RIGHT(i)]+= x/2;
      return; 
    }
    if(r<a || l>b) return;
    int m = (l+r)/2;
    range_add(LEFT(i),l,m);
    range_add(RIGHT(i),m+1,r);
    update_node(i);
  }
  void range_up(int qa,int qb,int k){
    a=qa,b=qb, off=k;
    range_add(0, 0, v.size()/2);
  }
};

rmqtree merge(rmqtree &t1, rmqtree &t2){
  vi ans(t1.v.size()/2 + 1);
  for(int i = 0; i < ans.size(); i++)
    ans[i] = max(t1.v[i+t1.v.size()/2], t2.v[i+t2.v.size()/2]);
  return rmqtree(ans);
}
/* UTILIZZO 2D -> [0 based RMQ]
    la lazy propagation non c'è quindi neanche range update.
    volendo, si possono fare range update su una singola riga
    ma serve modificare un minimo il codice
    point_update(r, c, k) = setta a Q il valore [r][c] 
    rangemax(r1, c1, r2, c2) = il max nel quadrato [r1, c1], [r2, c2] */
struct rmq2d{
  vector<rmqtree> v;
  int null_value = INT_MIN;
  void build(vvi &source){
    int n1 = closest_pow(source.size())*2 - 1;
    int n2 = closest_pow(source.front().size())*2 - 1;
    v.resize(n1);
    for(int i = n1/2; i < v.size(); i++)
      v[i].build(source[i - n1/2]);
    for(int i = n1/2 - 1; i >= 0; i--)
      v[i] = merge(v[LEFT(i)], v[RIGHT(i)]);
  }
  rmq2d(vvi &source){
    build(source);
  }
  rmq2d(){}
  int qr1, qr2, qc1, qc2, qk;
  int rmq(int i, int l, int r){   
    if(l >= qr1 && r <= qr2)
      return v[i].rangemax(qc1, qc2);
    if(r < qr1 || l > qr2)
      return null_value;
    int m = (l+r)/2;
    return max(rmq(LEFT(i), l, m), rmq(RIGHT(i), m + 1, r));
  }
  int rangemax(int r1, int c1, int r2, int c2){
    qr1 = r1, qc1 = c1;
    qr2 = r2, qc2 = c2;
    if(qr1 > qr2)
      swap(qr1, qr2);
    if(qc1 > qc2)
      swap(qc1, qc2);
    return rmq(0, 0, v.size()/2);
  }
  void update_node(int i, int j){
    if(i < v.size())
      v[i].v[j] = max(v[LEFT(i)].v[j], v[RIGHT(i)].v[j]);     
  }
  void update_up(int r, int c){
    v[r].update(qc1, qk);
    if(r) update_up(ROOT(r), c);
  }
  void update(int i, int l, int r){
    if(qr1 > r || qr1 < l) return;
    if(l == r){
      v[i].update(qc1, qk);
      update_up(ROOT(i), qc1+v[i].v.size()/2);
    } else update(LEFT(i), l, (l+r)/2), update(RIGHT(i), (l+r)/2 + 1, r);
  }
  void point_update(int r, int c, int k){
    qr1 = r, qc1 = c, qk = k;
    update(0, 0, v.size()/2);
  }
};
