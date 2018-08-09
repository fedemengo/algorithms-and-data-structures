//da usare 1 based!
struct fenwick_op{
	fenwick fw1, fw2;
	fenwick_op(int n){
		fw1.resize(n+2), fw2.resize(n+1);
	}
	int pf(int a){
		return fw1.pf(a)*a + fw2.pf(a);
	}
	int rsq(int a, int b){
		return pf(b) - pf(a-1);
	}
	//one of the best things i realized so far
	int range_update(int a, int b, int k){
		fw1.update(a, k), fw1.update(b+1, -k);
		fw2.update(a, -k*(a-1)), fw2.update(b+1, k*(b+1));
	}
};