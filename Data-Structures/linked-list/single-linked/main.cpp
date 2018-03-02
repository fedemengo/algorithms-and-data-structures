#include <bits/stdc++.h>

/*
    TODO
    HEAD insert, remove, select
    TAIL insert, remove, select
    INDX insert, remove, select
    search, list_delete
 */

class linked_list {

    class node {
    public:
        node *next;
        int value;

        node(int v){
            next = nullptr;
            value = v;
        }
        ~node(){}
    };

    int size;
    node *H;

public:
    linked_list(int size){
        size = 0;
        H = nullptr;
    }
    ~linked_list(){}

    void insert(int value){
        if(H == nullptr){
            H = new node(value);
        } else {
            node *n = H;
            while(n->next != nullptr){
                n = n->next;
            }
            node *temp = new node(value);
            n->next = temp;
        }
        size++;
    }

    bool search(int value){
        node *n = H;
        while(n->next != nullptr){
            if(n->value == value){
                return true;
            }
            n = n->next;
        }
        return false;
    }

    void remove(int value){
        if(H->value == value){
            node *tmp = H;
            H = H->next;
            delete tmp;
        } else {
            node *n = H;
            while(n->next != nullptr){
                if(n->next->value == value){
                    node *tmp = n->next;
                    n->next = n->next->next;
                    delete tmp;
                }
            }
        }
    }

    void print(){
        node *n = H;
        do {
            printf("%2d ", n->value);
            n = n->next;
        } while (n != nullptr);
        printf("\n");
    }
};


int main(int argc, char const *argv[]) {

    int N = atoi(argv[1]);

    linked_list list(0);

    for(int i=0; i<N; ++i){
        list.insert(i);
    }

    printf("ok\n");

    list.print();

    return 0;
}
