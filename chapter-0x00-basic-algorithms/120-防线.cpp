#include <stdio.h>
#include <string.h>
#include <algorithm>

#define MAX_N 200005

/* 本题题干中有一个十分重要的条件：
 *
 * “有奇数个防具的位置至多只有一个”
 *
 * 该条件决定了可以使用二分答案的方式：如果奇数防具位置为x0，考虑 <= x 这段区间的总防具个数（前缀和）
 * 当 x < x0 时，prefix_sum(x) 为偶数
 * 当 x >= x0 时，prefix_sum(x) 为奇数
 *
 * 满足二分答案所需要的单调性。
 *
 * 而计算 <= x 这段区间的总防具个数用 O(n) 时间即可完成。
 *
 * 并且注意这种将单点判断转化为区间判断的思路。
 */

struct Seq {
    long long s, e, d;
};

Seq seq[MAX_N];

long long prefix_sum(long long x, const Seq& seq) {
    long long res = 0;
    if (seq.s <= x) {
        res = (std::min(seq.e, x) - seq.s) / seq.d + 1;
    }
    return res;
}

long long total_sum(long long x, int n) {
    long long sum = 0;
    for (int i = 0; i < n; ++i) {
        sum += prefix_sum(x, seq[i]);
    }
    return sum;
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        memset(seq, 0, sizeof(seq));
        int n;
        long long max_e = 0;
        scanf("%d", &n);
        for (int i = 0; i < n; ++i) {
            scanf("%lld %lld %lld", &seq[i].s, &seq[i].e, &seq[i].d);
            max_e = std::max(max_e, seq[i].e);
        }
        long long l = 0, r = max_e + 1;
       
        if (0 == total_sum(r, n) % 2) {
            printf("There's no weakness.\n");
            continue;
        }

        while (l < r) {
            long long mid = (l + r) >> 1;
            if (1 == total_sum(mid, n) % 2) {
                r = mid;
            } else {
                l = mid + 1;
            }
        }
        
        int num = total_sum(r, n) - total_sum(r - 1,  n);
        printf("%lld %lld\n", r, num);
    }
    return 0;
}
