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

    class node {
    public:
        T data;
        node *next;
        node *prev;

        node(T d) : data(d), next(nullptr), prev(nullptr) {}
        node() : next(this), prev(this) {}
    };

    class iterator {
    public:
        iterator(node *ptr) : ptr(ptr){}
        
        iterator &operator++() { 
            ptr = ptr->next; 
            return *this; 
        }
        iterator &operator--() { 
            ptr = ptr->prev; 
            return *this; 
        }
        bool operator!=(const iterator & other) { return ptr != other.ptr; }
        T &operator*() const { return ptr->data; }
    private:
        node *ptr;
    };

    node *dummy;
    int _size;

public:
    doubly_linked(){
        dummy = new node();
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

    node* find(int data){
        node *n = dummy->next;
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

    node *get(int index){
        node *n = dummy->next;
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
        node *n;
        if(index == 0){
            n = dummy->next;
            dummy->next->next->prev = dummy;
            dummy->next = dummy->next->next;
        } else if(index == _size-1) {
            n = dummy->prev;
            n->prev->next = dummy;
            dummy->prev = n->prev;
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
        node *n = new node(data);
        if(index == 0){
            n->next = dummy->next;
            n->prev = dummy;
            dummy->next->prev = n;
            dummy->next = n;
        } else if(index == _size){
            dummy->prev->next = n;
            dummy->prev->next->prev = dummy->prev;
            dummy->prev = n;
            dummy->prev->next = dummy;
        } else {
            node *tmp = get(index);
            n->prev = tmp->prev;
            n->prev->next = n;
            tmp->prev = n;
            n->next = tmp;
        }
        ++_size;
    }

    int size() { return _size; }

    iterator begin() const { return iterator(dummy->next); }
    iterator end() const { return iterator(dummy); }

    T &operator[] (int i) { return this->get(i)->data; }
    
    void print(){
        for(node *n = dummy->next; n != dummy; n = n->next){
            std:: cout << n->data << " ";
        }
        std::cout << std::endl;
    }
};
