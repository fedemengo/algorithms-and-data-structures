#include <iostream>
/*
    Insert in range [0, size)
    if insert at @size: push_back
    else insert at @index and slide the content
 */

template <typename T>
class single_linked {
    class node {
    public:
        T data;
        node *next;

        node(T d) : data(d), next(nullptr) {}
    };

    class iterator {
    public:
        iterator(node *ptr) : ptr(ptr){}
        iterator &operator++() { 
            ptr = ptr->next; 
            return *this; 
        }
        iterator &operator++(int) {
            iterator *it = this;
            ptr = ptr->next; 
            return *it; 
        }
        bool operator!=(const iterator & other) { return ptr != other.ptr; }
        T &operator*() const { return ptr->data; }
    private:
        node* ptr;
    };

    node *head;
    node *tail;
    int _size;

public:
    single_linked(){
        head = nullptr;
        tail = nullptr;
        _size = 0;
    }

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
        node *n = head;
        if(n->data == data){
            return n;
        } else {
            while(n->next != nullptr){
                n = n->next;
            }
            if(n->data == data){
                return n;
            }
        }
        return nullptr;
    }

    std::pair<node *, std::pair<node *, node*>> get(int index){
        node *n = head, *prev = nullptr;
        while(index-- && n->next != nullptr){
            prev = n;
            n = n->next;
        }
        return {n, {prev, n->next}};
    }
 
    void remove(int index){
        if(_size == 0){
            throw std::invalid_argument("can't remove from empty list");
        }
        std::pair<node *, std::pair<node *, node*>> data = get(index);
        if(data.second.first == nullptr){
            head = data.second.second;
        } else if(data.second.second == nullptr){
            tail = data.second.first;
            data.second.first->next = nullptr;
        } else {
            data.second.first->next = data.second.second;
        }
        delete data.first;
        --_size;
    }

    void insert(int index, T data){
        node *n = new node(data);
        if(index == 0){
            n->next = head;
            head = n;
            if(_size == 0){
                tail = head;
            }
        } else if(index == _size){
            tail->next = n;
            tail = n;
        } else {
            std::pair<node *, std::pair<node *, node*>> data = get(index);
            n->next = data.first;
            data.second.first->next = n;
        }
        ++_size;
    }

    int size() { return _size; }

    //node *get_head() { return head; }
    //node *get_tail() { return tail; }

    iterator begin() const { return iterator(head); }
    iterator end() const { return iterator(tail->next); }

    T &operator[] (int i) { return this->get(i).first->data; }
    
    void print(){
        node *n = head;
        for(int i=0; i<_size; ++i, n = n->next){
            std:: cout << (*this)[i] << " ";
        }
        std::cout << std::endl;
    }
};
