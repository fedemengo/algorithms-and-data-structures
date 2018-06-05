#include <bits/stdc++.h>

/*
    TODO
    HEAD insert, remove, select
    TAIL insert, remove, select
    INDX insert, remove, select
    search, list_delete
 */

template <typename T>
class linked_list {
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
    linked_list(){
        head = nullptr;
        tail = nullptr;
        _size = 0;
    }

    void push_back(T data){
        node *n = new node(data);
        if(head == nullptr){
            tail = head = n;
        } else {
            tail->next = n;
            tail = tail->next;
        }
        _size++;
    }

    void push_front(T data){
        node *n = new node(data);
        n->next = head;
        head = n;
        _size++;
    }

    void pop_back(){
        remove(_size-1);
    }

    void pop_front(){
        node *tmp = head;
        head = head->next;
        delete tmp;
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
        while(index-- && n != nullptr){
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
        _size--;
        delete data.first;
    }

    void insert(int index, T data){
        node *n = new node(data);
        if(index == 0){
            n->next = head;
            head = n;
        } else if(index == _size){
            tail->next = n;
            tail = n;
        } else {
            std::pair<node *, std::pair<node *, node*>> data = get(index);
            n->next = data.first;
            data.second.first = n;
        }
        _size++;
    }

    node *get_head() { return head; }

    node *get_tail() { return tail; }


    int size() { return _size; }

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

void print(linked_list<std::string> &l){
    for(auto &x : l){
        std::cout << std::setw(2) << x << " ";
    }
    std::cout << std::endl;
}

int main(int argc, char const *argv[]) {
    int N = atoi(argv[1]);
    srand(time(0));

    linked_list<std::string> list({});

    for(int i=0; i<N; ++i){
        std::string str = "hello";
        str.append(std::to_string(i));
        list.push_back(str);
    }

    list.print();

    while(list.size()){
        list.remove(rand() % list.size());
        //list.pop_back();
        print(list);
    }

    return 0;
}
