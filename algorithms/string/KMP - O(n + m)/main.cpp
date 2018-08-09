#include <iostream>
#include <cstring>
#include <ctime>
#include <cstdlib>
#include <vector>
using namespace std;

#define MOD 100
#define INF 2e9

void KMPpreProcess(string &pattern, vector<char> &b){
	int i=0, j=-1;
	b[0] = -1;
	while(i<pattern.size()){
		while(j >= 0 && pattern[i] != pattern[j]) j = b[j];			// while different 
		++i; ++j;													// once equal advance both
		b[i] = j;													// and save new reset index
	}
}

void KMPsearch(string pattern, string text){
	vector<char> b(pattern.size());
	KMPpreProcess(pattern, b);
	int i=0, j=0;
	for(int i=0; i<text.size(); ++i){
		while(j >= 0 && text[i] != pattern[j]) j = b[j];
		++j;
		if(j == pattern.size()){
			cout << "found at " << i-j << "\n";
			j = b[j];
		}
	}
}

int main(int argc, char *argv[]){

    srand(time(0));
    int nodes = atoi(argv[1]), sparsity = atoi(argv[2]);

    string text, pattern;

    KMPsearch(pattern, text);
    
    return 0;
}