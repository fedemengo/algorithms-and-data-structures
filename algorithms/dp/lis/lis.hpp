#include <algorithm>
#include <vector>

// Longest Increasing Subsequence in O(N*lgK), where K is the length of the sequence. Up to O(N*lgN)
int lis(std::vector<int> seq){
	std::vector<int> lis;
	std::vector<int>::iterator pos;
	lis.push_back(seq.back());
	for(int i=seq.size()-2; i>-1; --i){
		pos = lower_bound(lis.begin(), lis.end(), seq[i]);
		if(pos == lis.end()) // if the element is the largest in the subsequence 
			lis.push_back(seq[i]);		// increase the sequence
		else
			*pos = seq[i];	// decrease element already in the sequence
	}
	return lis.size();
}

