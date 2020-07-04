#include <stack>

class MinStack {
public:
    /** initialize your data structure here. */
    MinStack() {
        
    }
    
    void push(int x) {
        val_stack.push(x);
        if (min_stack.empty() || x < min_stack.top()) {
            min_stack.push(x);
        } else {
            int cur_min = min_stack.top();
            min_stack.push(cur_min);
        }
    }
    
    void pop() {
        val_stack.pop();
        min_stack.pop();
    }
    
    int top() {
        return val_stack.top();     
    }
    
    int getMin() {
        return min_stack.top();     
    }
private:
    std::stack<int> val_stack;
    std::stack<int> min_stack;
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack obj = new MinStack();
 * obj.push(x);
 * obj.pop();
 * int param_3 = obj.top();
 * int param_4 = obj.getMin();
 */
