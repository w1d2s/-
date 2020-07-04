#include <iostream>
#include <stack>
#include <vector>

/* 操作都在光标位置处发生，且操作后光标位置至多移动1：
 * “对顶栈” + 一个数组保存k及之前位置的最大前缀和。
 */

class Editor {
public:
    explicit Editor(int n): 
        prefix_sum(0), cur_pos(0), max_sum_arr(std::vector<int>(n + 5, 0)) {}

    void ins(int x) {
        ++cur_pos;

        if (left_stack.empty()) {
            max_sum_arr[cur_pos] = x;
        } else {
            int cur_max_prefix_sum = max_sum_arr[cur_pos - 1];
            if (x + prefix_sum > cur_max_prefix_sum) {
                max_sum_arr[cur_pos] = x + prefix_sum;
            } else {
                max_sum_arr[cur_pos] = cur_max_prefix_sum;
            }
        }
        
        left_stack.push(x);
        prefix_sum += x;
    }

    void del() {
        if (!left_stack.empty()) {
            auto item = left_stack.top();
            left_stack.pop();
            prefix_sum -= item;
            --cur_pos;
            //std::cout << prefix_sum << std::endl;
        }
    }

    void move_left() {
        if (!left_stack.empty()) {
            auto item = left_stack.top();
            left_stack.pop();
            right_stack.push(item);
            prefix_sum -= item;
            --cur_pos;
            //std::cout << prefix_sum << std::endl;
        }
    }

    void move_right() {
        if (!right_stack.empty()) {
            auto item = right_stack.top();
            right_stack.pop();
            ins(item);
            //std::cout << prefix_sum << std::endl;
        }
    }

    int query(int k) {
        return max_sum_arr[k];
    }

private:
    // (int, int) for (number, max prefix sum at this point)
    std::stack<int> left_stack;
    std::stack<int> right_stack;
    std::vector<int> max_sum_arr;
    int cur_pos;
    int prefix_sum;
};

int main() {
    int n;
    std::cin >> n;
    Editor e(n);
    for (int i = 0; i < n; ++i) {
        char op;
        int x;
        int sum;
        std::cin >> op;
        switch (op) {
            case 'I':
                std::cin >> x;
                e.ins(x);
                break;
            case 'D':
                e.del();
                break;
            case 'L':
                e.move_left();
                break;
            case 'R':
                e.move_right();
                break;
            case 'Q':
                std::cin >> x;
                sum = e.query(x);
                std::cout << sum << std::endl;
                break;
            default:
                break;
        }
    }
    return 0;
}
