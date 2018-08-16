
#include <iostream>

template <typename T>
class xor_list {
private:

    template<typename T_NODE>
    class xor_lnode {
    public:
        T_NODE data;
        xor_lnode<T_NODE> *np;

        xor_lnode(T_NODE d) : data(d) {} 
    };

    template<typename T_NODE>
    class iterator {
    public:
        xor_lnode<T_NODE> *last;
        xor_lnode<T_NODE> *ptr;
        iterator(xor_lnode<T_NODE> *ptr) : last(nullptr), ptr(ptr) {}
        iterator &operator++() {
            xor_lnode<T_NODE> *old = ptr;
            ptr = XOR(ptr->np, last);
            last = old;
            return *this; 
        }
        iterator &operator++(int) {
            iterator *it = this;
            xor_lnode<T_NODE> *old = ptr;
            ptr = XOR(ptr->np, last);
            last = old;
            return *it; 
        }
        bool operator!=(const iterator &other) { return ptr != other.ptr; }
        T &operator*() { return ptr->data; }
    };

    static xor_lnode<T> *XOR(xor_lnode<T> *l, xor_lnode<T> *r) {
        return (xor_lnode<T> *)(((unsigned long int) l) ^ ((unsigned long int) r));
    }

    xor_lnode<T> *insert(xor_lnode<T> *l, xor_lnode<T> *r, T data) {
        xor_lnode<T> *node = new xor_lnode<T>(data);
        node->np = XOR(l, r);
        if (l != nullptr)
            l->np = XOR(XOR(l->np, r), node);
        if (r != nullptr)
            r->np = XOR(XOR(r->np, l), node);
        ++_size;
        return node;
    }

    xor_lnode<T> *remove(xor_lnode<T> *l, xor_lnode<T> * r, xor_lnode<T> *node) {
        if (l != nullptr)
            l->np = XOR(XOR(l->np, r), node);
		if (r != nullptr)
			r->np = XOR(XOR(r->np, l), node);
        delete node;
        --_size;
        return l;
    }

    xor_lnode<T> *head, *tail;
    ssize_t _size;

public:
    xor_list() : head(nullptr), tail(nullptr), _size(0) {}

    void push_front(T data) {
        head = insert(nullptr, head, data);
        if (tail == nullptr) {
            tail = head;
        }
    }

    void push_back(T data) {
        tail = insert(tail, nullptr, data);
        if (head == nullptr) {
            head = tail;
        }
    }

    T pop_front() {
        T d = head->data;
        head = remove(head->np, nullptr, head);
        return d;
    }

    T pop_back() {
        T d = tail->data;
        tail = remove(tail->np, nullptr, tail);
        return d;
    }

    std::pair<xor_lnode<T> *, std::pair<xor_lnode<T> *, xor_lnode<T> *>> find(T data) {
        for(auto it = begin(); it != end(); it++) {
            if (*it == data) {
                return {it.ptr, {it.last, XOR(it.ptr->np, it.last)}};
            }
        }
        return {nullptr, {nullptr, nullptr}};
    }

    std::pair<xor_lnode<T> *, std::pair<xor_lnode<T> *, xor_lnode<T> *>> get(int index) {
        auto it = begin();
        while(index--) {
            it++;
        }
        return {it.ptr, {it.last, XOR(it.ptr->np, it.last)}};
    }
    
    void insert(int index, T data) {
        if (index == 0)
            push_front(data);
        else if (index == size())
            push_back(data);
        else {
            auto node = get(index);
            insert(node.second.first, node.first, data);
        }
    }

    void remove(int index) {
		if (index == 0)
			pop_front();
		else if (index == size()-1)
			pop_back();
		else {
			auto node = get(index);
			remove(node.second.first, node.second.second, node.first);
		}
	}

	void swap() {
		std::swap(head, tail);
	}
	
	int size() {
        return _size;
    }

    iterator<T> begin() const { return iterator<T>(head); }
    iterator<T> end() const { return iterator<T>(nullptr); }
};
