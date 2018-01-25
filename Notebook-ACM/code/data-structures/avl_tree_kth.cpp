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
uchar height(node *n){
  return n ? n->height : 0;
}
int size(node *n){
  return n ? n->size : 0;
}
int bfactor(node *n){
  return height(n->right) - height(n->left);
}
void fix_height(node *n){
  uchar l = height(n->left);
  uchar r = height(n->right);
  n->height = max(l, r) + 1;
  n->size = size(n->left) + size(n->right) + 1;
}
node *rotate_right(node *n){
  node *left = n->left;
  n->left = left->right;
  left->right = n;
  fix_height(n);
  fix_height(left);
  return left;
}
node *rotate_left(node *n){
  node *right = n->right;
  n->right = right->left;
  right->left = n;
  fix_height(n);
  fix_height(right);
  return right;
}
node *balance(node *n){
  fix_height(n);
  int b = bfactor(n);
  if(b == 2){
    if(bfactor(n->right) < 0)
      n->right = rotate_right(n->right);
    return rotate_left(n);
  }
  else if(b == -2){
    if(bfactor(n->left) > 0)
      n->left = rotate_left(n->left);
    return rotate_right(n);
  }
  return n;
}
node *insert_kth(node *n, int k, int value){
  if(!n) return new node(value);
  if(k <= size(n->left))
    n->left = insert_kth(n->left, k, value);
  else if(k > size(n->left))
    n->right = insert_kth(n->right, k - size(n->left) - 1, value);
  return balance(n);
}
node *get_min(node *n){
  return n->left ? get_min(n->left) : n;
}
node *remove_min(node *n){
  if(n->left){
    n->left = remove_min(n->left);
    return balance(n);
  }
  return n->right;
}
node *get_kth(node *n, int k){
  if(!n)
    return 0;
  if(size(n->left) < k)
    return get_kth(n->right, k-size(n->left)-1);
  if(size(n->left) > k)
    return get_kth(n->left, k);
  if(size(n->left) == k)
    return n;
}
static int ans;
node *remove_kth(node *n, int k){
  if(k < size(n->left))
    n->left = remove_kth(n->left, k);
  else if(k > size(n->left))
    n->right = remove_kth(n->right, k - size(n->left) - 1);
  else{
    node *l = n->left, *r = n->right;
    ans = n->key;
    delete n;
    if(!r) return l;
    node *min = get_min(r);
    min->right = remove_min(r);
    min->left = l;
    return balance(min);
  }
  return balance(n);
}
node *remove_key(node *n, int k){
  if(!n) return 0;
  if(k < n->key)
    n->left = remove_key(n->left, k);
  else if(k > n->key)
    n->right = remove_key(n->right, k);
  else{
    node *l = n->left, *r = n->right;
    delete n;
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
  int size(){
    return _size;
  }
  void insert(int k, int value){
    _root = ::insert_kth(_root, k, value);
    _size++;
  }
  int remove(int k){
    _root = remove_kth(_root, k);
    return ans;
  }
  int get_nth(int n){
    return ::get_kth(_root, n)->key;
  }
};