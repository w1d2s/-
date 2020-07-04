#include <stdio.h>
#include <stdlib.h>
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

void dfs_perm_enum(const int total, int n, 
                int state, vector<int>& current) {
    if (n == total + 1) {
        dump_int_vec(current);
        return;
    }
    for (int i = 1; i <= total; ++i) {
        if ((state >> i) & 1) {
            continue;
        }
        current.push_back(i);
        dfs_perm_enum(total, n + 1, state | (1 << i), current);
        current.pop_back();
    }
}

int main() {
    int n;
    while (scanf("%d", &n) != EOF) {
        vector<int> permutation;
        dfs_perm_enum(n, 1, 0, permutation);
    }
    return 0;
}
