#include <queue>
#include <cmath>
#include <iostream>
#include <unordered_map>

// fibonacci heap
template <typename DATA, typename KEY>
class fibonacci_heap {
private:
    // attributes
    int nodes;
    fibonacci_node<DATA, KEY> *min_node;                            // pointer to min_node inside root_list
    doubly_linked_list<fibonacci_node<DATA, KEY> *> root_list;      // list of root_nodes
    std::unordered_map<KEY, fibonacci_node<DATA, KEY> *> *addresses;        // hash table to map each node's address using its data as key for the hash
    fibonacci_node<DATA, KEY> *child;
    fibonacci_node<DATA, KEY> *extracted;
    // methods
    void consolidate() {
        std::vector<fibonacci_node<DATA, KEY> *> pointer(max_degree(), nullptr);
        fibonacci_node<DATA, KEY> *node = min_node, *x, *y;

        for(int i=0; i<root_list.size(); ++i){
            node = (x = node)->right;
            int d = x->degree;
            while (pointer[d]) {
                y = pointer[d];
                if (*x > *y)
                    std::swap(x, y);
                make_child(y, x);
                pointer[d] = nullptr;
                ++d;
                --i;
            }
            pointer[d] = x;
        }
        root_list.clear_list(min_node);
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
    void cut(fibonacci_node<DATA, KEY> *x, fibonacci_node<DATA, KEY> *y) {
        y->child_list.remove_node(x);
        --y->degree;
        root_list.push_back(x);
        x->p = nullptr;
        x->mark = false;
    }
    void cascading_cut(fibonacci_node<DATA, KEY> *y) {
        fibonacci_node<DATA, KEY> *z = y->p;
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
    void make_child(fibonacci_node<DATA, KEY> *y, fibonacci_node<DATA, KEY> *x) {       // link root y to root x, x remains a root, y does not
        root_list.remove_node(y);
        x->child_list.push_back(y);
        ++x->degree;
        y->p = x;
        y->mark = false;
    }
    // upper_bound of number of root nodes in the root lists that will be present after consolidation
    int max_degree() { return (int)floor(log((double)nodes)/log((1.0+sqrt(5.0))/2.0))+1; }
public:
    // methods
    fibonacci_heap(int size, int value) : nodes(0), min_node(nullptr), addresses(new std::unordered_map<int, fibonacci_node<DATA, KEY> *>(size)) {
        for(int i=0; i<size; ++i) insert(new fibonacci_node<DATA, KEY>(i, value)); 
    }
    fibonacci_heap(int size) : nodes(0), min_node(nullptr), addresses(new std::unordered_map<int, fibonacci_node<DATA, KEY> *>(size)) {}
    ~fibonacci_heap() { delete addresses; };
    void fill(int size, int value){ for(int i=0; i<size; ++i) insert(new fibonacci_node<DATA, KEY>(i, value)); }
    bool empty() { return !nodes; }
    void insert(DATA d, KEY k) {                            // insert(new fibonacci_node(key, data))
        fibonacci_node<DATA, KEY> *node = new fibonacci_node<DATA, KEY>(d, k);
        (*addresses)[node->data] = node;                    // [node->data] = node;
        root_list.push_back(node);
        if (min_node == nullptr)
            min_node = node;
        else if(*node < *min_node)
            min_node = node;
        ++nodes;
    }
    fibonacci_node<DATA, KEY> extract_min(){
        extracted = min_node;                               // save min node
        if (extracted != nullptr) {                     // if min node exists (the heap is not empty)
            while (extracted->child_list.size()) {      // move all its children to rootlist since min node will be removed
                child = extracted->child_list.head->left;
                extracted->child_list.remove_node(child);
                child->p = nullptr;
                root_list.push_back(child);
            }
            root_list.extract_node(extracted);          // extract from root_list leaving pointers as they were
            if (extracted == extracted->right) {            // if it was the only node and it has no children
                min_node = nullptr;
            } else {                                    // else there are still node
                min_node = extracted->right;                // temporary set min node to the righ siblings
                consolidate();
            }
            --nodes;
            addresses->erase(extracted->data);
        }
        fibonacci_node<DATA, KEY> x(extracted);             // construct copy of node and delete it
        return x;
    }
    void decrease_key(int data, int key) {
        fibonacci_node<DATA, KEY> *x = (*addresses)[data];
        if (key < x->key) {
            x->key = key;
            fibonacci_node<DATA, KEY> *y = x->p;
            if (y != nullptr && *x < *y) {
                cut(x, y);
                cascading_cut(y);
            }
            if (*x < *min_node)
                min_node = x;
        }
    }
};