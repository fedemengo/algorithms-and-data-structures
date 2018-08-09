 #include <bits/stdc++.h>
using namespace std;

template <typename T>
struct op_struct{
	T (*ptr)(T &, T &);
	T null;
	char *id;
};

template <typename T> 
T _sum(T &x, T &y){
	return x + y;
}

template <typename T> 
T _min(T &x, T &y){
	return x < y ? x : y;
}
template <typename T> 
T _max(T &x, T &y){
	return x > y ? x : y;
}

template <typename T>
class segment_tree {
private:
	int N, qlow, qhigh;
	T nullvalue, update_value;
	std::vector<T> v, lazy;
	T (*operation)(T &x, T &y);
	char *op_id;
	int left(int index) {return (index << 1) + 1;}
	int right(int index) {return (index << 1) + 2;}
	int parent(int index) {return (index-1) >> 1;}
	//int size(int s) { return (1<<(int)(ceil(log2(s)+1)))-1; }
	void build(int index, int low, int high, std::vector<T> &source){
		if(low == high){
			v[index] = source[low];
		} else {
			build(left(index), low, (low + high) >> 1, source);
			build(right(index), ((low + high) >> 1) + 1, high, source);
			v[index] = operation(v[left(index)], v[right(index)]);
		}
	}
	void lazy_update(int index){
		// lazy update
		if(lazy[index] != 0){
			//printf("lazyy\n");
			v[index] += lazy[index];
			if(index < N){
				if(op_id == "sum"){
					lazy[left(index)] += (lazy[index]>>1);
					lazy[right(index)] += (lazy[index]>>1);
				} else {
					lazy[left(index)] += lazy[index];
					lazy[right(index)] += lazy[index];
				}
			}
			lazy[index] = 0;
		}
	}
	T range_rec(int index, int low, int high){
		lazy_update(index);
		if(qlow > high || qhigh < low){	// no overlap, the node doesn't contain useful information
			return nullvalue;	// NEED TO FIX NULL VALUE FOR EACH OPERATION
		} else if(qlow <= low && qhigh >= high){	// total overlap (this interval is entirely contained iside the query, the query will result in the value of this node and some lateral interval
			return v[index];
		} else {
			int mid = (low + high) >> 1;
			T range1 = range_rec(left(index), low, mid);
			T range2 = range_rec(right(index), mid+1, high);
			return operation(range1, range2);
		}
	}
	void add_range_rec(int index, int low, int high){
		lazy_update(index);
		if(qlow > high || qhigh < low){
			return;
		} else if(qlow <= low && high <= qhigh){	// total overlap
			if(op_id == "sum"){
				int range_sum = (high-low+1)*update_value;		// update parent
				v[index] += range_sum;							// update parent
				if(low != high){								
					lazy[left(index)] += (range_sum>>1);		// lazy update left
					lazy[right(index)] += (range_sum>>1);		// lazy update right
				}
			} else {		// MIN and MAX
				v[index] += update_value;						
				if(low != high){
					lazy[left(index)] += update_value;
					lazy[right(index)] += update_value;
				}
			}
		} else {
			int mid = (low + high) >> 1;
			add_range_rec(left(index), low, mid);
			add_range_rec(right(index), mid+1, high);
			v[index] = operation(v[left(index)], v[right(index)]);
		}
	}
	void update_rec(int index, int low, int high){
		//printf("%d %d -> index = %d\n", low, high, index);
		lazy_update(index);
		if(low == high){
			v[index] = update_value;
		} else {
			int mid = (low + high) >> 1;
			if(qlow <= mid)
				update_rec(left(index), low, mid);
			else
				update_rec(right(index), mid+1, high);
			v[index] = operation(v[left(index)], v[right(index)]);
		}
	}
public:
	// simply use size as 4n
	segment_tree(std::vector<T> &source, struct op_struct<T> &op) : N(source.size()), v(std::vector<T>((int)(source.size()<<2), -1)), lazy(std::vector<T>((int)(source.size()<<2), 0)), nullvalue(op.null), operation(op.ptr), op_id(op.id) { 
		build(0, 0, N-1, source);
		printf("%s\n", op_id);
	};
	~segment_tree(){};

	T range(int q_low, int q_high){
		qlow = q_low, qhigh = q_high;
		return range_rec(0, 0, N-1);
	}
	void add_range(int low, int high, T &value){
		qlow = low, qhigh = high, update_value = value;
		add_range_rec(0, 0, N-1);
	}
	void update(int low, T &value){
		qlow = low, update_value = value;
		update_rec(0, 0, N-1);
	}
	void print(){
		for(auto x: v)
			printf("%d ", x);
		printf("\n");
		for(auto x: lazy)
			printf("%d ", x);
		printf("\n\n");
	}
};

#define MOD 15
int main(int argc, char *argv[]){

	srand(time(0));
	int N = atoi(argv[1]), a = 0, b = 2, val;
	vector<int> s(N);
	//vector<int> s = {14, 3, 5, 6};

	for(int &x: s){
		x = rand() % MOD;
		printf("%d ", x);
	}
	printf("\n");
	
	op_struct<int> sum = {_sum, 0, (char *)"sum"};
	op_struct<int> min = {_min, INT_MAX, (char *)"min"};
	op_struct<int> max = {_max, INT_MIN, (char *)"max"};
	//int (*sum)(int &, int &) = _sum;
	segment_tree<int> ST(s, min);
	
	cout << "RANGE\n";
	cin >> a >> b;
	printf("%d\n", ST.range(a, b));
	cout << "ADD RANGE\n";
	cin >> a >> b >> val;
	ST.add_range(a, b, val);		// add val to range of element
	cout << "RANGE\n";
	cin >> a >> b;
	printf("%d\n", ST.range(a, b));
	cout << "UPDATE VALUE\n";
	cin >> a >> val;
	ST.update(a, val);				// update val of single element
	cout << "RANGE\n";
	cin >> a >> b;
	printf("%d\n", ST.range(a, b));

    return 0;
}
