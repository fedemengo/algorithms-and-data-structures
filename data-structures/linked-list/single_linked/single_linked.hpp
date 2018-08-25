#include <iostream>
#include <stack>
/*
    Insert in range [0, size)
    if insert at @size: push_back
    else insert at @index and slide the content

    TODO: Consider whether to allow iterator to be modified
 */

template <typename T>
class single_linked {
private:

    template <typename T_NODE>
    class node {
    public:
        T_NODE data;
        node<T_NODE> *next;

        node(T_NODE d) : data(d), next(nullptr) {}
    };

    template <typename T_NODE>
    class iterator {
    private:
        node<T_NODE> *ptr;
    public:
        iterator(node<T_NODE> *ptr) : ptr(ptr){}
        iterator &operator++() { 
            ptr = ptr->next; 
            return *this; 
        }
        iterator &operator++(int) {
            iterator *it = this;
            ptr = ptr->next; 
            return *it; 
        }
        bool operator!=(const iterator &other) { return ptr != other.ptr; }
        T &operator*() { return ptr->data; }
    };

    node<T> *&head() { return _head; }
    node<T> *&tail() { return _tail; }

    node<T> *_head;
    node<T> *_tail;
    int _size;

public:
    single_linked(){
        head() = nullptr;
        tail() = nullptr;
        _size = 0;
    }

    void push_back(T data){
        insert(_size, data);
    }

    void push_front(T data){
        insert(0, data);
    }

    void pop_back(){
        erase(_size-1);
    }

    void pop_front(){
        erase(0);
    }

	T front(){
		return _head->data;
	}

	T back(){
		return _tail->data;
	}

    node<T> *find(T data){
        node<T> *n = head();
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

    std::pair<node<T> *, node<T> *> get(int index){
        node<T> *n = head(), *prev = nullptr;
        while(index-- && n->next != nullptr){
            prev = n;
            n = n->next;
        }
        return {n, prev};
    }
 
    void erase(int index){
        if(_size == 0){
            throw std::invalid_argument("can't erase from empty list");
        }
        if(index < 0 || index > _size){
            throw std::out_of_range("index out of bounds"); 
        }
        std::pair<node<T> *, node<T> *> data = get(index);
        if(data.second == nullptr){
            head() = data.first->next;
        } else if(data.first->next == nullptr){
            tail() = data.second;
            data.second->next = nullptr;
        } else {
            data.second->next = data.first->next;
        }
        delete data.first;
        --_size;
    }

    void insert(int index, T data){
        if(index < 0 || index > _size + 1){
            throw std::out_of_range("index out of bounds"); 
        }
        node<T> *n = new node<T>(data);
        if(index == 0){
            n->next = head();
            head() = n;
            if(_size == 0){
                tail() = head();
            }
        } else if(index == _size){
            tail()->next = n;
            tail() = n;
        } else {
            std::pair<node<T> *, node<T> *> data = get(index);
            n->next = data.first;
            data.second->next = n;
        }
        ++_size;
    }

	void reverse(){
		std::stack<node<T> *> nodes;
		node<T> *n = _head;
		T data;
		int pos = 0;
		
		while(pos++ < _size / 2){
			nodes.push(n);
			n = n->next;
		}

		if (_size & 1) n = n->next;
		
		while(nodes.size()){
			data = n->data;
			n->data = nodes.top()->data;
			nodes.top()->data = data;
			nodes.pop();
			n = n->next;
		}
	}

    int size() { return _size; }

    iterator<T> begin() const { return iterator<T>(_head); }
    iterator<T> end() const { return iterator<T>(_tail->next); }

    T &operator[] (int i) { return this->get(i).first->data; }
    
    void print(){
        for(auto &x : *this){
            std::cout << x << " ";
        }
        std::cout << std::endl;
    }
};
