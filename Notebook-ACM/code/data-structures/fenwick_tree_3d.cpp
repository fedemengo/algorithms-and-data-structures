constexpr int lsb(int n){
	return n&(-n);
}
//da usare 1 based
struct fenwick{
	vector<int> v;
	fenwick(int n){
		v.resize(n+1, 0);
	}
	fenwick(vector<int> &source){
		v.resize(source.size() + 1, 0);
		for(int i = 0; i < source.size(); i++){
			v[i+1] += source[i];
			if(i+1 + lsb(i+1) < v.size())
				v[i+1 + lsb(i+1)] += v[i+1];
		}
	}
	int pf(int i){
		int ans = 0;
		for(; i; i-=lsb(i))
			ans += v[i];
		return ans;
	}
	int rsq(int l, int r){
		return pf(r) - pf(l-1);
	}
	void update(int i, int k){
		for(; i < v.size(); i += lsb(i))
			v[i] += k;
	}
};

//da usare 1 based
struct fenwick2d{
	vector<fenwick> v;
	fenwick2d(int n, int m){
		v.resize(n+1, fenwick(m));
	}
	int pf(int r, int c){
		int ans = 0;
		for(int i = r; i > 0; i -= lsb(i))
			ans += v[i].pf(c);
		return ans;
	}
	int rsq(int r1, int c1, int r2, int c2){
		return pf(r2, c2) - pf(r1-1, c2)
				 - pf(r2, c1-1) + pf(c1-1, r1-1);
	}
	void update(int r, int c, int k){
		for(int i = r; i < v.size(); i += lsb(i))
			v[i].update(c, k);
	}
};

//da usare 1 based
struct fenwick3d{
	vector<fenwick2d> v;
	fenwick3d(int x, int y, int z){
		v.resize(x+1, fenwick2d(y, z));
	}
	int pf(int x, int y, int z){
		int ans = 0;
		for(int i = x; i > 0; i -= lsb(i))
			ans += v[i].pf(y, z);
		return ans;
	}
	int rsq(int x1, int y1, int z1, int x2, int y2, int z2){
		return pf(x2, y2, z2) - pf(x1-1, y2, z2)
				 - pf(x2, y1-1, z2) - pf(x2, y2, z1-1)
				 + pf(x2, y1-1, z1-1) + pf(x1-1, y2, z1-1)
				 + pf(x1-1, y1-1, z2) - pf(x1-1, y1-1, z1-1);
	}
	void update(int x, int y, int z, int k){
		for(int i = x; i < v.size(); i+=lsb(i))
			v[i].update(y, z, k);
	}
};