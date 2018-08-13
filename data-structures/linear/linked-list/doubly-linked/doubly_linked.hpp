#include <iostream>
/*
    TODO
    HEAD insert, remove, select
    TAIL insert, remove, select
    INDX insert, remove, select
    search, list_delete
 */

template <typename T>
class doubly_linked {

    template <typename T_NODE>
    class node {
    public:
        T_NODE data;
        node<T_NODE> *next;
        node<T_NODE> *prev;

        node(T_NODE d) : data(d), next(nullptr), prev(nullptr) {}
        node() : next(this), prev(this) {}
    };

    template <typename T_NODE>
    class iterator {
    private:
        node<T_NODE> *ptr;
    
	public:
        iterator(node<T_NODE> *ptr) : ptr(ptr){}
        // iterator pre increment 
        iterator &operator++() { 
            ptr = ptr->next; 
            return *this; 
        }
        // iterator post increment
        iterator &operator++(int) {
            iterator *it = this;
            ptr = ptr->next; 
            return *it; 
        }

        iterator &operator--() { 
            ptr = ptr->prev; 
            return *this; 
        }
        iterator &operator--(int) {
            iterator *it = this;
            ptr = ptr->prev; 
            return *it; 
        }
        bool operator!=(const iterator & other) { return ptr != other.ptr; }
        T &operator*() const { return ptr->data; }
    };

    node<T> *&head() { return dummy->next; }
    node<T> *&tail() { return dummy->prev; }

    node<T> *dummy;
    int _size;

public:
    doubly_linked(){
        dummy = new node<T>();
        _size = 0;
    }

    ~doubly_linked() { delete dummy; }
    
    void push_back(T data){
        insert(_size, data);
    }

    void push_front(T data){
        insert(0, data);
    }

    void pop_back(){
        remove(_size-1);
    }

    void pop_front(){
        remove(0);
    }

    node<T> * find(int data){
        node<T> *n = head();
        if(n->data == data){
            return n;
        } else {
            while(n->next != dummy){
                n = n->next;
            }
            if(n->data == data){
                return n;
            }
        }
        return nullptr;
    }

    node<T> *get(int index){
        node<T> *n = head();
        while(index-- && n->next != dummy){
            n = n->next;
        }
        return n;
    }

    void remove(int index){
        if(_size == 0){
            throw std::invalid_argument("can't remove from empty list");
        }
        if(index < 0 || index > _size){
            throw std::out_of_range("index out of bounds"); 
        }
        node<T> *n;
        if(index == 0){
            n = head();
            n->next->prev = dummy;
            head() = n->next;
        } else if(index == _size-1) {
            n = tail();
            n->prev->next = dummy;
            tail() = n->prev;
        } else {
            n = get(index);
            n->prev->next = n->next;
            n->next->prev = n->prev;
        }
        delete n;
        --_size;
    }

    void insert(int index, T data){
        if(index < 0 || index > _size + 1){
            throw std::out_of_range("index out of bounds"); 
        }
        node<T> *n = new node<T>(data);
        if(index == 0){
            n->next = head();
            n->prev = dummy;
            head()->prev = n;
            head() = n;
        } else if(index == _size){
            n->prev = tail();
            n->next = dummy;
            tail()->next = n;
            tail() = n;
        } else {
            node<T> *tmp = get(index);
            n->prev = tmp->prev;
            n->prev->next = n;
            tmp->prev = n;
            n->next = tmp;
        }
        ++_size;
    }

    int size() { return _size; }

    iterator<T> begin() const { return iterator<T>(dummy->next); }
    iterator<T> end() const { return iterator<T>(dummy); }

    T &operator[] (int i) { return this->get(i)->data; }
    
    void print(){
        for(auto &x : *this){
            std:: cout << x << " ";
        }
        std::cout << std::endl;
    }
};
