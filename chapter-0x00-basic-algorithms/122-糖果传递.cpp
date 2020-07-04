#include <stdio.h>
#include <cmath>
#include <algorithm>

#define MAX_N 1000005

/* 环形纸牌均分问题：
 * 首先回忆纸牌均分问题，如何推导出最小交换数是归一化的前缀和？
 * 再看环形纸牌均分问题，首先注意到最优解必然有两个人没有交换纸牌，可以从中断开环。
 * 然后如何选择最优断点？推导在第k个人断开时的最小操作数（前缀和），注意归一化之后的
 * Sn = 0，转化为货仓选址问题（中位数的性质）。
 */

long long a[MAX_N];

int main() {
    int n;
    long long average = 0;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%lld", &a[i]);
        average += a[i];
    }
    
    average /= n;
    a[0] -= average;
    
    for (int i = 1; i < n; ++i) {
        a[i] += a[i - 1] - average;
    }
    
    std::sort(a, a + n);

    long long median;
    if (0 == n % 2) {
        median = (a[n / 2 - 1] + a[n / 2]) / 2;
    } else {
        median = a[(n - 1) / 2];
    }
    
    long long result = 0;
    for (int i = 0; i < n; ++i) {
        result += abs(a[i] - median); 
    }
    printf("%lld\n", result);
    
    return 0;
}
