//Andrew monotonechain + some geometry things 
struct point {
  int x, y;
  bool operator ==(point &other){ return x == other.x && y == other.y;}
};
/* < 0 -> counterclockwise, = 0 -> collinear, > 0 -> clockwise */
ll orientation(point &a, point &b, point &c){
  return (b.y - a.y) * (ll)(c.x - b.x) - (b.x - a.x) * (ll)(c.y - b.y);
}
struct segment {
  point a, b;
  bool contains(point &p){
    if(orientation(a, b, p) != 0)
      return 0;
    bool x = p.x >= a.x && p.x <= b.x;
    bool y = p.y >= min(a.y, b.y) && p.y <= max(a.y, b.y);
    // bool x = unsigned(p.x - a.x) <= b.x - a.x;
    // bool y = unsigned(p.y - a.y) <= b.y - a.y;
    return x && y;
  }
  bool operator& (segment &s){
    return intersect(s);
  }
  bool intersect(segment &s){
    ll o1 = orientation(a, b, s.a);
    ll o2 = orientation(a, b, s.b);
    ll o3 = orientation(s.a, s.b, a);
    ll o4 = orientation(s.a, s.b, b);
    o1 = o1 > 0 ? 1 : (o1 < 0 ? -1 : 0);
    o2 = o2 > 0 ? 1 : (o2 < 0 ? -1 : 0);
    o3 = o3 > 0 ? 1 : (o3 < 0 ? -1 : 0);
    o4 = o4 > 0 ? 1 : (o4 < 0 ? -1 : 0);
    //if they obv intersect
    if(o1 != o2 && o3 != o4) return 1;
    return contains(s.a) || contains(s.b) || s.contains(a) || s.contains(b);
  }

  segment(point p1, point p2) : a(p1), b(p2){
    if(a.x > b.x)
      swap(a, b);
  }
};
//make a vector of point and voila
struct convex_hull : vector<point>{
  vector<point> &hull = *this;
  vector<segment> segs;
  convex_hull (vector<point> &v){
    point lowest = *min_element(v.begin(), v.end(),
      [](point &a, point &b){return tie(a.y, a.x) < tie(b.y, b.x);});
    sort(v.begin(), v.end(), [&lowest](point &a, point &b){
      ll o = orientation(lowest, a, b);
      if(o == 0) return a.x < b.x;
      return o < 0;
    });

    hull.push_back(v[0]), hull.push_back(v[1]);
    for(int i = 2; i < v.size(); i++){
      //we try to insert v[i]
      while(hull.size() >= 2){
        point &a = hull[hull.size() - 2], &b = hull.back();
        if(orientation(a, b, v[i]) >= 0)
          hull.pop_back();
        else
          break;
      }
      hull.push_back(v[i]);
    }
    segs.reserve(hull.size());
    segs.push_back(segment(hull.front(), hull.back()));
    for(int i = 0; i + 1 < hull.size(); i++)
      segs.push_back(segment(hull[i], hull[i+1]));
    sort(segs.begin(), segs.end(), [](segment &a, segment &b){
      return tie(a.a.x, a.b.x) < tie(b.a.x, b.b.x);
    });
  }
  //we also count point on the borders
  bool contains(point &p){
    int l = - 1, r = segs.size()-1, m;
    while(l <= r){
      segment &s = segs[m = (l + r)/2 + 1];
      if(p.x < s.a.x) l = m;
      if(p.x > s.b.x) r = m - 1;
    }
    segment line(p, {p.x, INF});
    vector<segments> xx;
    for(int i = lb + 1; i < segs.size() && segs[i].b.x <= p[x]; i++)
      if(segs[i].intersect(line)) xx.push_back(segs[i]);
    return 0;
  }
};