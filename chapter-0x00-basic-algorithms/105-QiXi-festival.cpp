#include <stdio.h>
#include <string.h>
#include <algorithm>

#define MAX_N 100010

/* 本题需要注意把复杂问题分解为简单模型：
 * 1. 行、列可以分开计算，因为同一行之间的互换，只影响
 *    列之间的数量分布，不影响这一行的数量；列同理，
 *    即可由二维转化为两个一维问题。
 * 2. 转化为一维问题后，考虑纸牌均分问题，注意最小交换数的证明。
 * 3. 由于1和k之间可以互换，考虑环形纸牌均分问题，朴素做法枚举
 *    环的断点，而进一步分析可以转化为104-货仓选址问题。
 * 注意体会思考如何利用问题特有性质将复杂问题分解为简单模型。
 */

int row_cnt[MAX_N];
int col_cnt[MAX_N];

long long row_prefix_sum[MAX_N];
long long col_prefix_sum[MAX_N];

void cal_normalized_prefix_sum(int* A, long long* S, const int len, const int mean) {
    if (len > 0) {
        S[0] = A[0] - mean;
        for (int i = 1; i < len; ++i) {
            S[i] = S[i - 1] + A[i] - mean;
        }
    }
}

long long cal_min_dist_to_median(long long* S, const int len) {
    if (len > 0) {
        std::sort(S, S + len);
        long long dist = 0;
        if (len % 2 == 1) {
            int mid = (len - 1) / 2;
            for (int i = 0; i < mid; ++i) {
                dist += S[mid] - S[i];
            }
            for (int i = mid + 1; i < len; ++i) {
                dist += S[i] - S[mid];
            }
        } else {
            int mid = len / 2 - 1;
            long long median = (S[mid] + S[mid + 1]) / 2;
            for (int i = 0; i <= mid; ++i) {
                dist += median - S[i];
            }
            for (int i = mid + 1; i < len; ++i) {
                dist += S[i] - median;
            }
        }
        return dist;
    }
    return 0;
}

int main() {
    int n, m, t;
    while (scanf("%d %d %d", &n, &m, &t) != EOF) {
        memset(row_cnt, 0, sizeof(row_cnt));
        memset(col_cnt, 0, sizeof(col_cnt));
        memset(row_prefix_sum, 0, sizeof(row_prefix_sum));
        memset(col_prefix_sum, 0, sizeof(col_prefix_sum));
        for (int i = 0; i < t; ++i) {
            int x, y; // x for row, y for col
            scanf("%d %d", &x, &y);
            ++row_cnt[x];
            ++col_cnt[y];
        }
        int row_ok = (t % n == 0) ? 1 : 0;
        int col_ok = (t % m == 0) ? 1 : 0;
        long long row_action_num = 0, col_action_num = 0;
        if (1 == row_ok) {
            cal_normalized_prefix_sum(row_cnt + 1, row_prefix_sum + 1, n, t / n);
            row_action_num = cal_min_dist_to_median(row_prefix_sum + 1, n);
        }
        if (1 == col_ok) {
            cal_normalized_prefix_sum(col_cnt + 1, col_prefix_sum + 1, m, t / m);
            col_action_num = cal_min_dist_to_median(col_prefix_sum + 1, m);
        }
        if (2 == row_ok + col_ok) {
            printf("both %lld\n", row_action_num + col_action_num);
        } else if (1 == row_ok + col_ok) {
            if (1 == row_ok) {
                printf("row %lld\n", row_action_num);
            } else {
                printf("column %lld\n", col_action_num);
            }
        } else {
            printf("impossible\n");
        }
    }
    return 0;
}
