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

void dfs_exp_enum(int total, int n, vector<int>& current) {
    if (n == 0) {
        dump_int_vec(current);
        return;
    }
    // '不选x'分支 
    dfs_exp_enum(total, n - 1, current);
    // '选x'分支
    current.push_back(total - n + 1);
    dfs_exp_enum(total, n - 1, current);
    // 重要！恢复现场
    current.pop_back();
    return;
}

int main() {
    int n;
    while (scanf("%d", &n) != EOF) {
        vector<int> chosen;
        dfs_exp_enum(n, n, chosen);
    }
    return 0;
}


