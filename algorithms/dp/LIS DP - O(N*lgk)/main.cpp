#include <cstring>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

#define MOD 100
#define INF 2e9

ifstream fin("input.txt");
ofstream fout("output.txt");

int N, *LIS, *v;

// Longest Increasing Subsequence in O(N*lgK), where K is the length of the sequence. Up to O(N*lgN)
int dp(){
	int *pos, length = 1;
	LIS[0] = v[N-1];
	for(int i=N-2; i>-1; --i){
		pos = lower_bound(LIS, LIS + length, v[i]);
		if(pos == LIS+length) // if the element is the largest in the subsequence 
			LIS[++length-1] = v[i];		// increase the sequence
		else
			*pos = v[i];	// decrease element already in the sequence
	}
	return length;
}

int main(){
	ios::sync_with_stdio(0);
	fin.tie(0);
	fin >> N;
	v = new int[N+1];
	LIS = new int[N+1];
	for(int i=0; i<N; ++i)	fin >> v[i];
	//time_t start = clock();
	cout << dp() << "\n";
	//cout << "time " << (double)(clock()-start)/CLOCKS_PER_SEC << "\n";
    return 0;
}
