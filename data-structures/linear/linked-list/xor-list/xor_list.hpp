
#include <iostream>

template <typename T>
class xor_list {
private:

    template<typename T_NODE>
    class xor_list_node {
    public:
        T_NODE data;
        xor_list_node<T_NODE> *np;

        xor_list_node(T_NODE d) : data(d) {} 
    };

    template<typename T_NODE>
    class iterator {
    private:
        xor_list_node<T_NODE> *last;
        xor_list_node<T_NODE> *ptr;
    public:
        iterator(xor_list_node<T_NODE> *ptr) : last(nullptr), ptr(ptr){}
        iterator &operator++() {
            xor_list_node<T_NODE> *old = ptr;
            ptr = XOR(ptr->np, last);
            last = ptr;
            return *this; 
        }
        iterator &operator++(int) {
            iterator *it = this;
            xor_list_node<T_NODE> *old = ptr;
            ptr = XOR(ptr->np, last);
            last = ptr;
            return *it; 
        }
        bool operator!=(const iterator &other) { return ptr != other.ptr; }
        T &operator*() { return ptr->data; }
    };

    static xor_list_node<T> *XOR(xor_list_node<T> *l, xor_list_node<T> *r) {
        return (xor_list_node<T> *)(((unsigned long int) l) ^ ((unsigned long int) r));
    }

    xor_list_node<T> *insert(xor_list_node<T> *l, xor_list_node<T> *r, T data) {
        xor_list_node<T> *node = new xor_list_node<T>(data);
        node->np = XOR(l, r);
        if(l != nullptr)
            l->np = XOR(XOR(l->np, r), node);
        if(r != nullptr)
            r->np = XOR(XOR(r->np, l), node);
        ++_size;
        return node;
    }

    xor_list_node<T> *remove(xor_list_node<T> *node_np, xor_list_node<T> *node) {
        if(node_np != nullptr)
            node_np->np = XOR(node_np->np, node);
        delete node;
        --_size;
        return node_np;
    }

    xor_list_node<T> *head, *tail;
    ssize_t _size;

public:
    xor_list() : head(nullptr), tail(nullptr), _size(0) {}

    void push_front(T data) {
        head = insert(nullptr, head, data);
        if(tail == nullptr){
            tail = head;
        }
    }

    void push_back(T data) {
        tail = insert(tail, nullptr, data);
        if(head == nullptr){
            head = tail;
        }
    }

    T pop_front(){
        T d = head->data;
        head = remove(head->np, head);
        return d;
    }

    T pop_back(){
        T d = tail->data;
        tail = remove(tail->np, tail);
        return d;
    }

    int size() {
        return _size;
    }

    iterator<T> begin() const { return iterator<T>(head); }
    iterator<T> end() const { return iterator<T>(nullptr); }
};
