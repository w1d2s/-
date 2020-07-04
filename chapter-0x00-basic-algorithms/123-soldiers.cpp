#include <stdio.h>
#include <algorithm>
#include <cmath>

#define MAX_N 10005

/* 1. 首先注意到x方向和y方向是不相关的，可以当做两个独立的1维问题考虑。
 * 2. y方向就是货仓选址问题，直接找中位数，计算最短距离 S_y = Sum{i = 0 to (n - 1)}|y[i] - y_median|
 * 3. x方向这样考虑：
 *    a) 首先按照x[i]从小到大排序，那么排在第i个的元素，移动到最优位置之后一定还是第i个；
 *    b) 设第0个元素的最优位置为X_start，那么第i个元素要移动到的最优位置就是(X_start + i);
 *    c) x方向的最小移动距离： 
 *
 *          S_x = Sum{i = 0 to (n - 1)}|x[i] - (X_start + i)|
 *              = Sum{i = 0 to (n - 1)}|(x[i] - i) - X_start|
 *              = Sum{i = 0 to (n - 1)}|c[i] - X_start|
 *
 *       即可转化为货仓选址问题，令序列 c[i] = x[i] - i，当X_start为c[i]中位数时，S_x最小。
 */

long long x[MAX_N], y[MAX_N];

long long cal_median(long long* x, int n) {
    long long median;
    if (0 == n % 2) {
        median = (x[n / 2] + x[(n / 2) - 1]) / 2;
    } else {
        median = x[(n - 1) / 2];
    }
    return median;
}

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%lld %lld", &x[i], &y[i]);
    }
    long long y_median, y_min_dist = 0;
    std::sort(y, y + n);
    y_median = cal_median(y, n);

    for (int i = 0; i < n; ++i) {
        y_min_dist += abs(y[i] - y_median);
    }

    long long x_final_start, x_min_dist = 0;
    std::sort(x, x + n);
    for (int i = 0; i < n; ++i) {
        x[i] -= i;
    }
    std::sort(x, x + n);
    x_final_start = cal_median(x, n);

    for (int i = 0; i < n; ++i) {
        x_min_dist += abs(x[i] - x_final_start);
    }
    
    printf("%lld\n", x_min_dist + y_min_dist);

    return 0;
}
