#include <stdio.h>
#include <stdlib.h>
#include <stack>
#include <vector>

using namespace std;

void dump_int_vec(const vector<int>& vec) {
    if (vec.size() == 0) {
        printf("\n");
        return;
    }
    for (int i = 0; i < vec.size() - 1; ++i) {
        printf("%d ", vec[i]);
    }
    printf("%d\n", vec[vec.size() - 1]);
}

struct Param {
    int tot, n, m;
    Param(int _tot, int _n, int _m) : tot(_tot), n(_n), m(_m) {}
};

stack<Param> env_stack;
stack<int> addr_stack;

void call(const Param cur_env_param, const Param caller_param, const int ret_addr) {
    env_stack.push(cur_env_param);
    addr_stack.push(ret_addr);
    env_stack.push(caller_param);
    addr_stack.push(0);
}

int main() {
    int n, m;
    while (scanf("%d %d", &n, &m) != EOF) {
        vector<int> current;
        env_stack.push(Param(n, 1, m));
        addr_stack.push(0);
        while (!addr_stack.empty()) {
            int addr = addr_stack.top();
            addr_stack.pop();
            Param p = env_stack.top();
            env_stack.pop();
            switch (addr) {
            case 0:
                if (p.m == 0) {
                    dump_int_vec(current);
                    continue;
                }
                if (p.n == p.tot + 1) {
                    continue;
                }
                current.push_back(p.n);
                call(p, Param(p.tot, p.n + 1, p.m - 1), 1);
                continue;
            case 1:
                current.pop_back();
                call(p, Param(p.tot, p.n + 1, p.m), 2);
                continue;
            case 2:
                continue;
            }
        }
    }
    return 0;
}
