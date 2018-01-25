//persistent segment tree set up for kth element 
struct segtree{
	int val = 0;
	segtree *l = 0, *r = 0;
	int a, b;
	int merge(int a, int b){
		return a + b;
	}
	void update(){
		val = (l ? l->val : 0) + (r ? r->val : 0);
	}
	segtree(int a, int b) : a(a), b(b){
		if(a != b){
			int m = (a+b)/2;
			l = new segtree(a, m);
			r = new segtree(m+1, b);
		}
	}
	segtree(int a, int b, segtree *l, segtree *r, int val) :
		a(a), b(b), l(l), r(r), val(val) {}
	bool is_leaf(){
		return max(l, r) == 0;
	}
	segtree *update(int pos, int off){
		if(pos > b || pos < a) return this;
		if(a == b) return new segtree(a, b, 0, 0, val + off);
		segtree *x = l->update(pos, off);
		segtree *y = r->update(pos, off);
		return new segtree(a, b, x, y, merge(x->val, y->val));
	}
	int kth(int k){
		if(is_leaf() && k + 1 == val) return a;
		if(k + 1 <= val){
			int lq = l->kth(k);
			if(lq != -1) return lq;
			k -= l->val;
			return r->kth(k - l->val);
		}
		return -1;
	}
};
struct persistent_segtree{
	vector<segtree> roots;
	vi source, ranks;
	void compute_ranks(){
		vi indexes(source.size());
		for(int i = 0; i < source.size(); i++)
			indexes[i] = i;
		sort(indexes.begin(), indexes.end(), [&](int a, int b){
			return source[a] < source[b]; });
		for(int i = 0; i < source.size(); i++)
			ranks[indexes[i]] = i;
		sort(source.begin(), source.end());
	}
	//given array, builds a segtree on each prefix
	persistent_segtree (vi &source) : source(source), ranks(source.size()){
		compute_ranks();
		//we start with empty segment
		roots.reserve(source.size() + 1);
		roots.push_back(segtree(0, source.size() - 1));
		for(int i : ranks)
			roots.push_back(*(roots.back().update(i, 1)));
	}
	int kth(int a, int b, int k){
		//we notice that if we merge nodes together a magic happens!
		segtree *x = &roots[a], *y = &roots[b+1];
		while(x->a != x->b){
			//we use merged val information in our traversal until we get to a leaf
			int ql = y->l->val - x->l->val;
			if(ql >= k + 1) x = x->l, y = y->l;
			else x = x->r, y = y->r;
		}
		return source[x->a];
	}
};