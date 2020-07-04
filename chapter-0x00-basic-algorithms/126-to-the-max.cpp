#include <iostream>
#include <string.h>
#include <algorithm>

#define MAX_N 105

/* 朴素做法 ：2维前缀和 O(N^4)
 *
 * 首先考虑1维最大子段和：
 * 如果以元素arr[i]为结尾的子段中，最大的字段和为dp[i]，
 * 那么以元素arr[i + 1]为结尾的子段的最大子段和 dp[i + 1] ：
 *      dp[i] + arr[i + 1], if dp[i] > 0
 *      arr[i + 1], otherwise
 *
 * 将2维矩阵按列求出前缀和，枚举起始和结束的行index，即可化为1维问题，O(N^3)
 */

using namespace std;

int arr[MAX_N][MAX_N];
int dp[MAX_N];


int main() {
    int n;
    cin >> n;
    memset(arr, 0, sizeof(arr));
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            int tmp;
            cin >> tmp;
            // column prefix sum
            arr[i][j] = arr[i - 1][j] + tmp;
        }
    }

    int max_sum = -0x3f3f3f3f;
    
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j <= n; ++j) {
            memset(dp, 0, sizeof(dp));
            for (int k = 1; k <= n; ++k) {
                dp[k] = arr[j][k] - arr[i][k];
                if (dp[k - 1] > 0) {
                    dp[k] += dp[k - 1];
                }
                max_sum = max(max_sum, dp[k]);
            }
        }
    }

    cout << max_sum << endl;

    return 0;
}
