// fibonacci heap node
template <typename DATA, typename KEY>
class fibonacci_node {
public:
    // attributes
    fibonacci_node<DATA, KEY> *p;
    doubly_linked_list<fibonacci_node<DATA, KEY> *> child_list;
    fibonacci_node<DATA, KEY> *left;
    fibonacci_node<DATA, KEY> *right;
    int degree;
    bool mark;
    KEY key;
    DATA data;
    //methods
    fibonacci_node() {};
    fibonacci_node(DATA v, KEY k) : p(nullptr), left(this), right(this), degree(0), mark(false), key(k), data(v) { child_list.init(); }
    fibonacci_node(fibonacci_node *node) { if(node != nullptr) {key = node->key, data = node->data, delete node; } }
    ~fibonacci_node() {};
    bool operator< (const fibonacci_node x){ return key < x.key; }
    bool operator> (const fibonacci_node x){ return key > x.key; }

};