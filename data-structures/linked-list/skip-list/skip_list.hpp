#include <iostream>
#include <vector>
#include <stack>

template <typename KEY, typename DATA>
class skip_list {
private:

    template<typename KEY_NODE, typename DATA_NODE>
    class skip_lnode {
    public:
        KEY_NODE key;
        DATA_NODE data;
        std::vector<skip_lnode<KEY_NODE, DATA_NODE> *> next;
        std::vector<int> width;

        skip_lnode() : next(MAX_LEVEL), width(MAX_LEVEL, 1) {}
        skip_lnode(KEY_NODE k, DATA_NODE d) : skip_lnode() {
            key = k;
            data = d;
        }

        void clear(){ next.clear(); }
    };

    template<typename KEY_NODE, typename DATA_NODE>
    class iterator {
    public:
        skip_lnode<KEY_NODE, DATA_NODE> *ptr;
        iterator(skip_lnode<KEY_NODE, DATA_NODE> *ptr) : ptr(ptr) {}
        iterator &operator++() {
            ptr = ptr->next[0];
            return *this; 
        }
        iterator &operator++(int) {
            iterator *it = this;
            ptr = ptr->next[0];
            return *it; 
        }
        bool operator!=(const iterator &other) { return ptr != other.ptr; }
        DATA_NODE &operator*() { return ptr->data; }
    };

    skip_lnode<KEY, DATA> *get_node(KEY k, DATA d){
        if(pool.size() == 0)
            fill_pool();
        skip_lnode<KEY, DATA> *prev = pool.top();
        pool.pop();
        prev->key = k;
        prev->data = d;
        return prev;
    }

    void fill_pool(){
        while(pool.size() < POOL_SIZE){
            pool.push(new skip_lnode<KEY, DATA>());
        }
    }

    static const int POOL_SIZE = 1000;
    static const int MAX_LEVEL = 16;
    skip_lnode<KEY, DATA> *head;
    ssize_t _size;
    std::stack<skip_lnode<KEY, DATA> *> pool;
    std::stack<skip_lnode<KEY, DATA> *> update;

public:
    skip_list() : head(new skip_lnode<KEY, DATA>(-1, "")), _size(0), pool(), update() {
        srand(time(0));
        fill_pool();
    }

    void print(){
        std::cout << "PRINT" << std::endl;
        for(int i=0; i<MAX_LEVEL; ++i){
            skip_lnode<KEY, DATA> *prev = head;
            std::cout << "LEVEL " << i << std::endl;
            while(prev != nullptr){
                if(prev->next[i]){
                    std::cout << " " << prev->key << ":" << prev->width[i] << " -";
                    for(int j=prev->key; j<prev->next[i]->key-1; ++j)
                        std::cout << " -----";
                }
                else
                    std::cout << " " << prev->key << ":prev";
                prev = prev->next[i];
            }
            std::cout << std::endl;
        }
    }
    
    void insert(KEY k, DATA d){
        skip_lnode<KEY, DATA> *prev = head, *n = get_node(k, d);
        std::stack<int> skipped;
        int lv = MAX_LEVEL, right = 0, lv_width, lv_right;
        while(--lv >= 0){
            while(prev->next[lv] && prev->next[lv]->key < k){
                right += prev->width[lv];
                prev = prev->next[lv];
            }
            update.push(prev);
            skipped.push(right);
        }
        do {
            prev = update.top(); update.pop();
            lv_right = skipped.top(); skipped.pop();
            
            ++lv;

            if(prev->next[lv])
                lv_width = prev->next[lv]->width[lv];
            else
                lv_width = size() - lv_right + 1;

            n->width[lv] = lv_right + lv_width - right;
            prev->width[lv] = right - lv_right + 1;

            n->next[lv] = prev->next[lv];
            prev->next[lv] = n;

        } while(rand() & 1 && lv < MAX_LEVEL-1);
        ++_size;
    }

    bool remove(KEY k){
        skip_lnode<KEY, DATA> *prev = head, *node = nullptr;
        int lv = MAX_LEVEL;
        while(--lv >= 0){
            while(prev->next[lv] && prev->next[lv]->key < k)
                prev = prev->next[lv];
            if(prev->next[lv] && prev->next[lv]->key == k){
                node = prev->next[lv];
                prev->next[lv] = prev->next[lv]->next[lv];
            }
        }
        if(node != nullptr){
            node->clear();
            pool.push(node);
            --_size;
            return true;
        }
        return false;
    }

    std::pair<KEY, DATA> find(KEY k){
        int lv = MAX_LEVEL;
        skip_lnode<KEY, DATA> *prev = head;
        while(--lv >= 0){
            while(prev->next[lv] && prev->next[lv]->key < k)
                prev = prev->next[lv];
        }
        prev = prev->next[0];
        return {prev->key, prev->data};
    }

    std::pair<KEY, DATA> min(){
        return {head->next[0]->key, head->next[0]->data};
    }

	int size() { return _size; }

    //std::pair<KEY, DATA> &operator[] (int i)
    std::pair<KEY, DATA> operator[] (int i) {
        int lv = MAX_LEVEL, pos = -1;
        skip_lnode<KEY, DATA> *prev = head;
        while(--lv >= 0){
            while(prev->next[lv] != nullptr && pos + prev->width[lv] < i){
                pos += prev->width[lv];
                prev = prev->next[lv];
            }
        }
        return {prev->next[0]->key, prev->next[0]->data}; 
    }

    iterator<KEY, DATA> begin() const { return iterator<KEY, DATA>(head->next[0]); }
    iterator<KEY, DATA> end() const { return iterator<KEY, DATA>(nullptr); }
};
