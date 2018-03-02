#include <iostream>
#include <algorithm>
#include <stdlib.h>
#include <vector>
#include <utility>
#include <fstream>

#define MOD 100
using namespace std;

typedef struct _node{
	int value;
	struct _node *np;
} node;

typedef node *list;

list init(){
	return NULL;
}

node *new_node(int value, node *prev){
	node *new_node = new node;
	new_node->value = value;
	new_node->np = NULL;
	return (node *)((unsigned long int)(prev) ^ (unsigned long int)(new_node));
}

void append_node(list *L, int value){
	node *curr = *L;
	node *prev = NULL;
	if(curr == NULL){
		*L = new_node(value, prev);
	} else {
		while(curr->np != NULL){
			node *save = curr;
			curr = (node *)((unsigned long int)(prev) ^ (unsigned long int)(curr->np));
			prev = curr;

		}
		curr->np = new_node(value, prev);;
	}
}

void print_list(list L, node *prev){
	node *curr = (node *)((unsigned long int)(prev) ^ (unsigned long int)(L));
	node *save = NULL;
	do {
		save = curr;
		cout << curr->value << "\n";
		curr = (node *)((unsigned long int)(prev) ^ (unsigned long int)(curr->np));
		prev = curr;
	} while(curr != save);
};

int main(int argc, char *argv[]){

    srand(time(0));
    int N = atoi(argv[1]);
    int v[N];

    list L = init();

    for(int i=0; i<N; ++i){
    	int v = rand() % MOD;
    	cout << "Inserting " << v << "\n";
		append_node(&L, v);
    }
    print_list(L, NULL);
    
    return 0;
}
