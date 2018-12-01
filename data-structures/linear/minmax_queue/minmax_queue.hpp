#include <queue>
#include <functional>

template <typename T>
class minmax_queue {
private:
    std::queue<T> q;
    std::queue<T> best;
    std::function<bool(T, T)> compare;

public:
    minmax_queue(std::function<bool(T, T)> cmp) : compare(cmp) {}
    minmax_queue() : minmax_queue([](T e1, T e2) { return e1 < e2; }) {}

    void push(T e) {
        q.push(e);
        if(best.size() != 0 && compare(e, best.front())) {
            best = std::queue<T>();
            //while(best.size()) best.pop();
        }
        best.push(e);
    }
    
    T front() {
        return q.front();
    }

    T minmax() {
        return best.front();
    }

    void pop(){
        if(q.front() == best.front()) {
            best.pop();
        }
        q.pop();
    }

    ssize_t size() { return q.size(); }
};
