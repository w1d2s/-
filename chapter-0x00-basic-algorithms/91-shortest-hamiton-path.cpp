#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int dist[22][22];
int dp[1 << 21][22];

int calc_hamiton_path(const int n) {
    memset(dp, 0x3f, sizeof(dp));
    dp[1][0] = 0;
    for (int i = 1; i < (1 << n); ++i) {
        for (int j = 0; j < n; ++j) {
            if ((i >> j) & 1) {
                int s = i ^ (1 << j);
                for (int k = 0; k < n; ++k) {
                    if ((s >> k) & 1) {
                        int tmp = dp[s][k] + dist[k][j];
                        if (tmp < dp[i][j]) {
                            dp[i][j] = tmp;
                        }
                    }
                }
            }
        }
    }
    return dp[(1 << n) - 1][n - 1];
}

int main() {
    int n;
    while (scanf("%d", &n) != EOF) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                scanf("%d", &dist[i][j]);
            }
        }
        int res = calc_hamiton_path(n);
        printf("%d\n", res);
    }
    return 0;
}

