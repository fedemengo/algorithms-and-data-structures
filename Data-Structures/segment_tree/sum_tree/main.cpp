#include <cstdlib>
#include <vector>
#include <iostream>
using namespace std;

class sum_tree {
private:
	vector<int> st, lazy;
	int null_value;
	int N, qlow, qhigh, upval;
	int left(int index){ return (index<<1)+1; }
	int right(int index){ return (index<<1)+2; }
	int parent(int index){ return (index-1)>>1; }

	void lazy_update(int index, int low, int high){
		if(lazy[index] != 0){
			st[index] += lazy[index];
			if(low != high){
				lazy[left(index)] = lazy[index] >> 1;
				lazy[right(index)] = lazy[index] >> 1;
			}
			lazy[index] = 0;
		}
	}
	void build_rec(int index, int low, int high, vector<int> &source){
		if(low == high){
			st[index] = source[low];
		} else {
			int mid = (low+high)>>1;
			build_rec(left(index), low, mid, source);
			build_rec(right(index), mid+1, high, source);
			st[index] = st[left(index)] + st[right(index)];
		}
	}
	int range_sum_rec(int index, int low, int high){
		lazy_update(index, low, high);
		if(qlow > high || low > qhigh){
			return null_value;
		} else if(qlow <= low && high <= qhigh){
			return st[index];
		} else {
			int mid = (low + high) >> 1;
			return range_sum_rec(left(index), low, mid) + range_sum_rec(right(index), mid+1, high);
		}
	}
	void range_add_rec(int index, int low, int high){
		lazy_update(index, low, high);
		if(qlow > high || low > qhigh){
			return;
		} else if(qlow <= low && high <= qhigh){
			int value = upval*(high-low+1);
			st[index] += value;
			if(low != high){
				lazy[left(index)] += (value >> 1);
				lazy[right(index)] += (value >> 1);
			}
		} else {
			int mid = (low + high) >> 1;
			range_add_rec(left(index), low, mid);
			range_add_rec(right(index), mid+1, high);
			st[index] = st[left(index)] + st[right(index)];
		}
	}
	/*void range_update_rec(int index, int low, int high){
		lazy_update(index, low, high);
		if(lazy[index] != 0){
			st[index] += lazy[index];
			if(low != high){
				lazy[left(index)] = (lazy[index]>>1) - lazy[left(index)];
				lazy[right(index)] = (lazy[index]>>1) - lazy[right(index)];
			}
			lazy[index] = 0;
		}
		if(qlow > high || low > qhigh){
			return;
		} else if(qlow <= low && high <= qhigh){
			int value = upval*(high-low+1);
			st[index] = value;
			if(low != high){
				lazy[left(index)] = (value>>1) - lazy[left(index)];
				lazy[right(index)] = (value>>1) - lazy[right(index)];
			}
		} else {
			int mid = (low + high) >> 1;
			range_update_rec(left(index), low, mid);
			range_update_rec(right(index), mid+1, high);
			st[index] = st[left(index)] + st[right(index)];
		}
	}*/
public:
	sum_tree(vector<int> &source) : st(vector<int>((source.size()<<2))), lazy(vector<int>((source.size()<<2), 0)), null_value(0), N(source.size()) {
		build_rec(0, 0, N-1, source);
	};
	~sum_tree(){};
	int range_sum(int low, int high){
		qlow = low, qhigh = high;
		return range_sum_rec(0, 0, N-1);
	}
	void range_add(int low, int high, int value){
		qlow = low, qhigh = high, upval = value;
		range_add_rec(0, 0, N-1);
	}
	void range_update(int low, int high, int value){
		qlow = low, qhigh = high, upval = value;
		//range_update_rec(0, 0, N-1);
	}
};

int main(int argc, char *argv[]){
	
	srand(time(0));
	int N = atoi(argv[1]);
	vector<int> v(N);

	for(int &x: v) x = rand() % 5;
	for(int x: v) printf("%d ", x); printf("\n");

	sum_tree ST(v);
	
	int a = 1, b, c, d;
	while(a){
		cin >> a;
		switch(a){
			case 1:
				cin >> b >> c;
				printf("%d\n", ST.range_sum(b, c));
				break;
			case 2:
				cin >> b >> c >> d;
				ST.range_add(b, c, d);
				break;
			/*case 3:
				cin >> b >> c >> d;
				ST.range_update(b, c, d);
				break;*/
		}
	}
}