#include <vector>
#include <cmath>
#include <iostream>
#include <unordered_map>
#include <iostream>

/**
 *  usage example in SP's algorithm
 *  the KEY would be the distance to each node, initialized at INF
 *  the DATA would be an identifier for the node itself
 *
 *  NOTE: the method fill(size, default_value) and therefore the constructor (size, default_value)
 *  map each node to an INT in the range (0, size)
 *  to avoid that, use empty constructor and insert(key, data)
 *
 *  TODO: to speed up the construction, create SIZE nodes at once and retrieve them from a node "pool"
 *
 **/

// fibonacci heap
template <typename KEY, typename DATA>
class fibonacci_heap {
private:
    // doubly linked list template
    template <typename T>
    class doubly_linked_list {
    private:
        size_t _size;
    public:
        T head;
        
        doubly_linked_list() { init(); };
        
        void init() { head = nullptr, _size = 0; }
        
        void insert_node(T prev, T node) {
            if (prev != nullptr) {
                node->left = prev;
                node->right = prev->right;
                prev->right->left = node;
                prev->right = node;
            }
            ++_size;
        }
        
        void extract_node(T node) {     // remove node from list leaving untouched its "left" and "right" pointer
            if (_size == 1) head = nullptr;
            else if (node == head) head = node->right;
            node->right->left = node->left;
            node->left->right = node->right;
            --_size;
        }
        
        void remove_node(T node) {          // remove node from list and clear its pointer
            extract_node(node);
            node->left = node;
            node->right = node;
        }
        
        void push_back(T node) {            // append the node at the tail of the list
            if (empty()) insert_node(head = node, node);
            else insert_node(head->left, node);
        }
        
        bool empty() { return !_size; }
        
        int size() { return _size; }
        
        void clear(T &x) { head = nullptr, _size = 0, x = nullptr; }
    };

	template <typename KEY_NODE, typename DATA_NODE>
    class fibonacci_node {
    public:
        // attributes
        fibonacci_node<KEY_NODE, DATA_NODE> *p, *left, *right;
        doubly_linked_list<fibonacci_node<KEY_NODE, DATA_NODE> *> child_list;
        int degree;
        bool mark;
        KEY_NODE key;
        DATA_NODE data;

        //methods
        fibonacci_node(KEY_NODE k, DATA_NODE d) : p(nullptr), left(this), right(this), degree(0), mark(false), key(k), data(d), child_list() {}
        
        fibonacci_node(fibonacci_node *node) { if(node != nullptr) key = node->key, data = node->data; }
        
        bool operator< (const fibonacci_node x){ return key < x.key; }
        bool operator> (const fibonacci_node x){ return key > x.key; }
    };

    int nodes;
    fibonacci_node<KEY, DATA> *min_node;
    doubly_linked_list<fibonacci_node<KEY, DATA> *> root_list;
    std::unordered_map<DATA, fibonacci_node<KEY, DATA> *> addresses;
    fibonacci_node<KEY, DATA> *child;
    fibonacci_node<KEY, DATA> *extracted;

    void consolidate() {
        std::vector<fibonacci_node<KEY, DATA> *> pointer(max_degree(), nullptr);
        fibonacci_node<KEY, DATA> *node = min_node, *x, *y;

        for(int i=0; i<root_list.size(); ++i){
            node = (x = node)->right;   // x = node, node = x->right
            int d = x->degree;
            while (pointer[d]) {
                y = pointer[d];
                if (*x > *y)
                    std::swap(x, y);
                make_child(y, x);
                pointer[d] = nullptr;
                ++d, --i;
            }
            pointer[d] = x;
        }
        root_list.clear(min_node);
        for (auto &x: pointer) {
            if (x) {
                root_list.push_back(x);
                if (min_node == nullptr)
                    min_node = x;
                else if (*x < *min_node)
                    min_node = x;
            }
        }
    }
    
    void cut(fibonacci_node<KEY, DATA> *x, fibonacci_node<KEY, DATA> *y) {
        y->child_list.remove_node(x);
        --y->degree;
        root_list.push_back(x);
        x->p = nullptr;
        x->mark = false;
    }
    
    void cascading_cut(fibonacci_node<KEY, DATA> *y) {
        fibonacci_node<KEY, DATA> *z = y->p;
        while(z != nullptr){
            if(y->mark == false){
                y->mark = true;
                z = nullptr;
            } else {
                cut(y, z);
                z = (y = z)->p;
            }
        }
    }
    
    void make_child(fibonacci_node<KEY, DATA> *y, fibonacci_node<KEY, DATA> *x) {
        root_list.remove_node(y);
        x->child_list.push_back(y);
        ++x->degree;
        y->p = x;
        y->mark = false;
    }
    
    void insert(fibonacci_node<KEY, DATA> *node) {
        addresses[node->data] = node;
        root_list.push_back(node);
        if (min_node == nullptr)
            min_node = node;
        else if(*node < *min_node)
            min_node = node;
        ++nodes;
    }
    
    // upper_bound of number of root nodes in the root lists that will be present after consolidation
    int max_degree() { return (int)floor(log((double)nodes)/log((1.0+sqrt(5.0))/2.0))+1; }

public:
    fibonacci_heap() : nodes(0), min_node(nullptr), addresses() {}
    
    fibonacci_heap(int size, KEY default_key) : nodes(0), min_node(nullptr), addresses() { fill(size, default_key); }
    
    void fill(int size, KEY default_key){
        for(int node_id=0; node_id<size; ++node_id)
            insert(new fibonacci_node<KEY, DATA>(default_key, node_id));
    }
    
    bool empty() { return !nodes; }
    
    void insert(KEY k, DATA d) { insert(new fibonacci_node<KEY, DATA>(k, d)); }
    
    std::pair<KEY, DATA> extract_min(){
    	std::pair<KEY, DATA> x;
        extracted = min_node;
        if (extracted != nullptr) {
        	x = {extracted->key, extracted->data};
            while (extracted->child_list.size()) {
                child = extracted->child_list.head->right;
                extracted->child_list.remove_node(child);
                child->p = nullptr;
                root_list.push_back(child);
            }
            root_list.extract_node(extracted);
            if (extracted == extracted->right) {
                min_node = nullptr;
            } else {
                min_node = extracted->right;
                consolidate();
            }
            --nodes;
            addresses.erase(extracted->data);
            delete extracted;	
        }
        return x;
    }
    
    void decrease_key(KEY key, DATA data) {
        if(addresses.count(data) == 0) return;
        fibonacci_node<KEY, DATA> *node = addresses[data];
        if (key < node->key) {
            node->key = key;
            fibonacci_node<KEY, DATA> *parent = node->p;
            if (parent != nullptr && *node < *parent) {
                cut(node, parent);
                cascading_cut(parent);
            }
            if (*node < *min_node)
                min_node = node;
        }
    }
    
    int size() { return nodes; }
};


int main(int argc, char const *argv[]) {

    fibonacci_heap<int, std::string> FH({});

    return 0;
}
