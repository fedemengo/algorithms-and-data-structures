#include <stack>
#include <functional>

template <typename T>
class minmax_stack {
private:
    std::stack<T> s;
    std::stack<T> best;
    std::function<bool(T, T)> compare;

public:

    minmax_stack(std::function<bool(T, T)> cmp) : s(), best(), compare(cmp) {}

    ssize_t size() { return s.size(); }

    T top(){ return s.top(); }

    void pop() { s.pop(); best.pop(); }

    void push(T value){
        s.push(value);
        if(best.size() == 0){
            best.push(value);
        } else {
            T stack_top = value;
            if(compare(best.top(), stack_top))
                stack_top = best.top();
            best.push(stack_top);
        }
    }

    T minmax(){ return best.top(); }
};