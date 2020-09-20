#include <stdio.h>
#include <string.h>

#define MAX_N 60002

typedef unsigned long long ull;

ull dp[2][MAX_N];

int main() {
    int n;
    scanf("%d", &n);
    dp[0][0] = 1;
    for (int i = 0; i < n; ++i) {
        int s = (i == 0) ? 1 : 0;
        for (int j = s; j <= n; ++j){
            ull tmp = 0;
            if (j > 0) {
                tmp += dp[i % 2][j - 1];
            }
            if (i > 0 && j < n) {
                tmp += dp[(i + 1) % 2][j + 1];
            }
            dp[i % 2][j] = tmp;
        }
    }
    printf("%lld\n", dp[(n + 1) % 2][1]);
    return 0;
}
