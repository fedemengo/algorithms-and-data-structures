typedef unsigned char uchar;
typedef unsigned int uint;
struct node{
  int key;
  uchar height;
  int size;
  node *left, *right;
  node(int k){
    size = 1;
    height = 1;
    key = k;
    left = right = 0;
  }
};
uchar height(node *n){ return n ? n->height : 0; }
int size(node *n){ return n ? n->size : 0; }
//right - left
int bfactor(node *n){ return height(n->right) - height(n->left); }
//supposes that children are already fixed
void fix_height(node *n){
  uchar l = height(n->left);
  uchar r = height(n->right);
  n->height = max(l, r) + 1;
  n->size = size(n->left) + size(n->right) + 1;
}
//it essentially means that we are taking node n and moving it to\
 his right sub-tree so we need to take the guy on his left and make\
  him become the new root this also means that the new root would become\
  losing his old right child. that right child is so given to his \
  "now-right-child-b4-father" as left child. node bfactor return bfactor(n) + 1
node* rotate_right(node *n){
  node *left = n->left; // copy of the new father so we can lose pointers
  n->left = left->right; //n steals his new-father right-child
  left->right = n; //we make left father of his old father
  // fix those nodes height, start from the bottom
  fix_height(n);
  fix_height(left);
  //we may now return the father in charge of this AVL-freakin' tree
  return left;
}
//same as above, but symmetrical\
  bfactor of node return is bfactor(n) - 1
node* rotate_left(node *n){
  node *right = n->right;
  n->right = right->left;
  right->left = n;
  fix_height(n);
  fix_height(right);
  return right;
}
node* balance(node *n){
  fix_height(n);
  int b = bfactor(n);
  if(b == 2){
//now we need to check if n's right child is left balanced:\
  in that case, a left rotation wouldn't balance the tree because\
  we'll give too much weight to the left child.\
  in this case, we need to perform a right rotation on that child\
  so that we spread it's weight unbalance on his children
    if(bfactor(n->right) < 0)
      n->right = rotate_right(n->right);
    return rotate_left(n);
  }
  else if(b == -2){
    //as above, we rotate to the right but before check for child balance:\
      we don't like it as +1
    if(bfactor(n->left) > 0)
      n->left = rotate_left(n->left);
    return rotate_right(n);
  }
  return n;
}
node *insert(node *n, int k){
  //if we reach the end of the tree
  if(!n) return new node(k);
  //insert left
  if(k <= n->key) n->left = insert(n->left, k);
  else n->right = insert(n->right, k);
  //as we inserted a node, we may need to rebalance
  return balance(n);
}
node *get_min(node *n){ return n->left ? get_min(n->left) : n; }
node *remove_min(node *n){
  if(n->left){
    n->left = remove_min(n->left);
    return balance(n);
  }
  return n->right;
}
node *find(node *n, int k){
  if(!n) return 0;
  if(n->key < k) return find(n->left, k);
  if(n->key > k) return find(n->right, k);
  return n;
}
//0 based
node *get_kth(node *n, int k){
  if(!n) return 0;
  if(size(n->left) < k)
    return get_kth(n->right, k-size(n->left)-1);
  if(size(n->left) > k)
    return get_kth(n->left, k);
  if(size(n->left) == k)
    return n;
}
//removes given key from tree
node *remove_key(node *n, int k){
  if(!n) return 0;
  if(k < n->key)
    n->left = remove_key(n->left, k);
  else if(k > n->key)
    n->right = remove_key(n->right, k);
  else{
  //if found, we have to replace it with the next element\
    which is min of right subtree
    node *l = n->left, *r = n->right;
    //destroys the struct :(
    delete n;
    //if we have no right-child, just return left one
    if(!r) return l;
    node *min = get_min(r);
    min->right = remove_min(r);
    min->left = l;
    return balance(min);
  }
  return balance(n);
}
struct avl{
  node* _root = 0;
  int _size = 0;
  int size(){ return _size; }
  void insert(int k){
    _root = ::insert(_root, k);
    _size++;
  }
  void remove(int k){ _root = remove_key(_root, k); }
  bool contains(int k){ return find(_root, k); }
  int get_nth(int n){ return ::get_kth(_root, n)->key; }
};