#include <cstdlib>
#include <vector>
using namespace std;

class fenwick_tree {
private:
	vector<int> ft;
	int LSB(int x) { 
		return x & (-x); 
	}
public:
	fenwick_tree(vector<int> &s) : ft(s.size()+1, 0) {
		for(int i=1; i<ft.size(); ++i){		// range (1, N) inclusive
			ft[i] += s[i-1];
			if(i + LSB(i) < ft.size())
				ft[i + LSB(i)] += ft[i];
		}
	}
	fenwick_tree(int N) {
		ft.resize(N+1, 0);
	};
	~fenwick_tree(){};

	int rangeSum(int i) {
		int sum = 0;
		while(i){
			sum += ft[i];
			i -= LSB(i);
		}
		return sum;
	}

	int rangeSum(int l, int r) {
		return rangeSum(r) - (l == 1 ? 0 : rangeSum(l-1));
	}

	void add(int i, int value) {
		while(i < ft.size()){
			ft[i] += value;
			i += LSB(i);
		}
	}
};

int main(int argc, char const *argv[]){
	
	int N = atoi(argv[1]), a, b, c;
	vector<int> v(N);
	for(int &x: v) x = 1;

	fenwick_tree FT(v);


	//return 0;
}