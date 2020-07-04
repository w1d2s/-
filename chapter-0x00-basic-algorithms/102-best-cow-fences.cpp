#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

using namespace std;

/* 如何理解使用二分法的前提：单调性？
 * 设可能的最大平均值为S，那么mid <= S时，一定存在一段不少于F的子段
 * 使得平均值 >= mid；反之当mid > S时，一定不存在这么一个子段。
 * 这样在mid两边一半取值的方案满足，一半不满足，就可以二分
 */

double a[100005];
double sum[100005];

double max_interval_sum(int N, int F, double S) {
    double max_sum = -1e10;
    double min_first_F = 1e10;
    for (int i = 1; i <= N; ++i) {
        sum[i] = a[i] + sum[i - 1] - S;
    }
    for (int i = F; i <= N; ++i) {
        min_first_F = sum[i - F] < min_first_F ? sum[i - F] : min_first_F;
        max_sum = (sum[i] - min_first_F) > max_sum ? (sum[i] - min_first_F) : max_sum;
    }
    return max_sum;
}

int main() {
    int N, F;
    while (scanf("%d %d", &N, &F) != EOF) {
        memset(a, 0, sizeof(a));
        memset(sum, 0, sizeof(sum));
        int j = 1;
        double sum_of_a = 0, avg_of_a = 0;
        int _N = N;
        while (_N--) {
            scanf("%lf", &a[j]);
            sum_of_a += a[j];
            ++j;
        }
        avg_of_a = sum_of_a / N;
        double l = avg_of_a, r = sum_of_a;
        double eps = 1e-8;
        while (l + eps < r) {
            double mid = (l + r) / 2;
            if (max_interval_sum(N, F, mid) >= 0) {
                l = mid;
            } else {
                r = mid;
            }
        }
        //printf("%d\n", (int)(l * 1000));
        cout << (int)(r * 1000) << endl;
    }
    return 0;
}
