#include <cstdlib>
#include <vector>
using namespace std;

// TODO range update and point query

// point update and range query
class fenwick_tree {
private:
	vector<int> ft;
	int LSB(int x) { return x & (-x); }
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

	int range_sum(int index) {
		int sum = 0;
		while(index){
			sum += ft[index];
			index -= LSB(index);
		}
		return sum;
	}

	int range_sum(int left, int right) {
		return range_sum(right) - (left < 1 ? 0 : range_sum(left - 1));
	}

	void add(int index, int value) {
		while(index < ft.size()){
			ft[index] += value;
			index += LSB(index);
		}
	}
};