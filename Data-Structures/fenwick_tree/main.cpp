#include <vector>
#include "fenwick.hpp"
using namespace std;

int main(int argc, char const *argv[]){

	int N = atoi(argv[1]);
	vector<int> v(N);
	for(int &x: v) x = 1;

	fenwick_tree FT(v);


	return 0;
}
