#include <iostream>
#include <vector>
#include <stack>
#include <functional>

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

    void fix_remove(std::stack<skip_lnode<KEY, DATA> *> &update, skip_lnode<KEY, DATA> *curr){
        skip_lnode<KEY, DATA> *node = curr->next[0];
        int lv = 0;
        // update nodes from level 0 going up
        while(update.size()){
            // get next to update
            curr = update.top(); update.pop();
            // if next node is not "tail" update current node width. If it's tail the width is calculated during insertion
            if(curr->next[lv]){
                // merge current node width with next node width and remove current node
                curr->width[lv] += curr->next[lv]->width[lv] - 1;
                curr->next[lv] = curr->next[lv]->next[lv];
            }
            ++lv;
        }
        // clear the node and put it back in the pool
        node->clear();
        pool.push(node);
        --_size;
    }

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
    std::function<bool(KEY, KEY)> compare;

public:
    skip_list(std::function<bool(KEY, KEY)> cmp) : head(new skip_lnode<KEY, DATA>()), _size(0), pool(), compare(cmp) {
        srand(time(0));
        fill_pool();
    }
    
    void insert(KEY k, DATA d){
        // create new node
        skip_lnode<KEY, DATA> *prev = head, *n = get_node(k, d);
        // keep track of node to update
        std::stack<skip_lnode<KEY, DATA> *> update;
        // keep track of the right-move per level
        std::stack<int> skipped;
        int lv = MAX_LEVEL, right = 0, lv_width, lv_right;
        while(--lv >= 0){
            // if next node it's not the "tail"
            while(prev->next[lv] && compare(prev->next[lv]->key, k)){
                // update distance on the right
                right += prev->width[lv];
                // update the node
                prev = prev->next[lv];
            }
            // save node to update
            update.push(prev);
            // save the distance to the right moved on current level
            skipped.push(right);
        }
        do {
            prev = update.top(); update.pop();
            lv_right = skipped.top(); skipped.pop();
            
            ++lv;

            // get current node width
            if(prev->next[lv])
                lv_width = prev->next[lv]->width[lv];
            else
                lv_width = size() - lv_right + 1;

            // set new node width
            n->width[lv] = lv_right + lv_width - right;
            // update previous node width
            prev->width[lv] = right - lv_right + 1;

            // set new node in position
            n->next[lv] = prev->next[lv];
            prev->next[lv] = n;
        } while(rand() & 1 && lv < MAX_LEVEL-1);
        ++_size;
    }

    bool remove(KEY k){
        skip_lnode<KEY, DATA> *curr = head;
        std::stack<skip_lnode<KEY, DATA> *> update;
        int lv = MAX_LEVEL;

        while(--lv >= 0){
            while(curr->next[lv] && compare(curr->next[lv]->key, k))
                curr = curr->next[lv];
            // save nodes to update if the element to remove is present
            update.push(curr);
        }

        // if the node to be removed is present, proceed
        if(curr->next[0] && curr->next[0]->key == k){
            fix_remove(update, curr);
            return true;
        }
        return false;
    }

    void remove_at(int index){
        skip_lnode<KEY, DATA> *curr = head;
        std::stack<skip_lnode<KEY, DATA> *> update;
        int lv = MAX_LEVEL, pos = -1;

        while(--lv >= 0){
            while(curr->next[lv] && pos + curr->width[lv] < index){
                pos += curr->width[lv];
                curr = curr->next[lv];
            }
            // save nodes to update
            update.push(curr);
        }
        fix_remove(update, curr);
    }

    std::pair<KEY, DATA> find(KEY k){
        int lv = MAX_LEVEL;
        skip_lnode<KEY, DATA> *curr = head;
        // advance as much as possible
        while(--lv >= 0){
            while(curr->next[lv] && compare(curr->next[lv]->key, k))
                curr = curr->next[lv];
        }
        // the node should be the one after the current
        return {curr->next[0]->key, curr->next[0]->data};
    }

    std::pair<KEY, DATA> top(){
        return {head->next[0]->key, head->next[0]->data};
    }

	int size() { return _size; }

    //std::pair<KEY, DATA> &operator[] (int i)
    std::pair<KEY, DATA> operator[] (int i) {
        int lv = MAX_LEVEL, pos = -1;
        skip_lnode<KEY, DATA> *curr = head;
        while(--lv >= 0){
            while(curr->next[lv] != nullptr && pos + curr->width[lv] < i){
                pos += curr->width[lv];
                curr = curr->next[lv];
            }
        }
        return {curr->next[0]->key, curr->next[0]->data}; 
    }

    iterator<KEY, DATA> begin() const { return iterator<KEY, DATA>(head->next[0]); }
    iterator<KEY, DATA> end() const { return iterator<KEY, DATA>(nullptr); }
};
