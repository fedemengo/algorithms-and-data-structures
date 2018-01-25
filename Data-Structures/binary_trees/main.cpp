#include <iostream>
#include <cstring>
#include <ctime>
#include <cstdlib>
using namespace std;

#define MOD 100
#define INF 2e9

typedef struct _node{
	struct _node *parent;
	struct _node *left;
	struct _node *right;
	int key;
	void *data;
} node;

typedef struct _bt{
	node *root;
} *bynary_tree;

bynary_tree init(){
	struct _bt *T = new struct _bt;
	T->root = NULL;
	return T;
}

node *alloc(int key, void *data){
	node *new_node = new node;
	new_node->parent = NULL;
	new_node->left = NULL;
	new_node->right = NULL;
	new_node->key = key;
	new_node->data = data;
	return new_node;
}

node *tree_min(node *current_node){
	while(current_node->left != NULL)
		current_node = current_node->left;
	return current_node;
}

node *tree_max(node *current_node){
	while(current_node->right != NULL)
		current_node = current_node->right;
	return current_node;
}

void in_oder_tree_walk(node *current_node){
	if(current_node != NULL){
		in_oder_tree_walk(current_node->left);
		cout << current_node->key << "\n";
		in_oder_tree_walk(current_node->right);
	}
}

node *tree_search(node *current_node, int key){
	if(current_node->key == key)
		return current_node;
	else if(current_node->key > key)
		return tree_search(current_node->left, key);
	else
		return tree_search(current_node->right, key);
}

node *tree_successor(node *current_node){
	if(current_node->right != NULL)
		return tree_min(current_node->right);
	node *y = current_node->parent;
	while(y != NULL && current_node != y->right){
		current_node = y;
		y = y->parent;
	}
	return y;
}

void tree_insert(bynary_tree T, int key, void *data){
	node *new_node = alloc(key, data);
	node *y = NULL;
	node *x = T->root;

	while(x != NULL){
		y = x;								// save parent position
		if(new_node->key > x->key)
			x = x->right;
		else								// find the right place for the new node
			x = x->left;
	}
	new_node->parent = y;					// set parent for the new node
	if(y == NULL)
		T->root = new_node;					// set new child for parent
	else if(new_node->key > y->key)			
		y->right = new_node;
	else
		y->left = new_node;
}

void tree_transplant(bynary_tree T, node *old_node, node *new_node){
	if(old_node->parent == NULL)
		T->root = new_node;
	else if(old_node == old_node->parent->left)
		old_node->parent->left = new_node;
	else 
		old_node->parent->right = new_node;
	if(new_node != NULL)
		new_node->parent = old_node->parent;
}

void tree_delete(bynary_tree T, node *current_node){
	if(current_node != NULL){
		if(current_node->left == NULL){
			tree_transplant(T, current_node, current_node->right);
		} else if(current_node->right == NULL){
			tree_transplant(T, current_node, current_node->left);
		} else {
			node *successor = tree_successor(current_node);
			if(successor->parent != current_node){
				tree_transplant(T, successor, successor->right);
				successor->right = current_node->right;
				successor->right->parent = successor;
			}
			tree_transplant(T, current_node, successor);
			successor->left = current_node->left;
			successor->left->parent = successor;
		}
		delete current_node;
	}
}

void delete_tree(node *current){
	if(current != NULL){
		delete_tree(current->left);
		delete_tree(current->right);
		//cout << "delete " << current->key << "\n";
		current->left = NULL;
		current->right = NULL;
		delete current;
	}
}

void drop_tree(bynary_tree T){
	delete_tree(T->root);
	T->root = NULL;
}

int main(int argc, char *argv[]){

    srand(time(0));
    int N = atoi(argv[1]);
    int v[N];

    bynary_tree T = init();
    
    for(auto &i:v)
        i = rand() % MOD;

    for(int i=0; i<N; ++i){
    	cout << v[i] << "\n";
    	tree_insert(T, v[i], NULL);
    }
    cout << "\n";
    in_oder_tree_walk(T->root);
    cout << "\n";
    tree_delete(T, T->root->right);
    in_oder_tree_walk(T->root);

    drop_tree(T);
    cout << T->root << "\n";
    in_oder_tree_walk(T->root);
    delete T;

    return 0;
}
