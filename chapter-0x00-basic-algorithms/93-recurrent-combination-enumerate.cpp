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
// 取到第n个数，还剩m个需要取
void dfs_comb_enum(const int total, int n, int m, vector<int>& current) {
    if (m == 0) {
        dump_int_vec(current);
        return;
    }
    if (n == total + 1) {
        return;
    }
    // '选第n个数'分支
    current.push_back(n);
    dfs_comb_enum(total, n + 1, m - 1, current);
    current.pop_back();
    // '不选第n个数'分支
    dfs_comb_enum(total, n + 1, m, current);
}

int main() {
    int n, m;
    while (scanf("%d %d", &n, &m) != EOF) {
        vector<int> chosen;
        dfs_comb_enum(n, 1, m, chosen);
    }
    return 0;
}
