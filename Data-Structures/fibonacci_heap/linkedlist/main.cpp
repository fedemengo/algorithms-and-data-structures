#include <iostream>

// doubly linked list template
template <typename T>
class doubly_linked_list {
private:
    size_t _size;
public:
    T head;
    doubly_linked_list() : head(nullptr), _size(0) {};
    ~doubly_linked_list() {};
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
    void clear_list(T &x) { head = nullptr, _size = 0, x = nullptr; }
};