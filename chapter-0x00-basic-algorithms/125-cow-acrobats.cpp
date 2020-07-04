#include <stdio.h>
#include <limits>
#include <algorithm>

#define MAX_N 50005

/* 贪心法，分析过程用临项交换
 *
 * 假设最下面两头牛是a、b，上面所有牛重量为W_tot，注意到a、b互换只影响他们俩的风险值，
 * 上面所有牛都不影响。
 *                        
 *                          1项                2项
 * a下b上时，risk_1 = max(W_tot + W_b - S_a, W_tot - S_b)
 * a上b下时，risk_2 = max(W_tot + W_a - S_b, W_tot - S_a)
 *
 * 分类讨论几种情况：
 *
 * 1. 两者都取 1项，即 W_b - S_a > -S_b && W_a - S_b > -S_a ==> S_b - W_a < S_a < W_b + S_b
 *    此时，如果
 *      risk_1 < risk_2，即 W_b - S_a < W_a - S_b ==> W_a + S_a > W_b + S_b 时，取a下b上
 *      risk_1 > risk_2,  .......                     W_a + S_a < W_b + S_b 时，取a上b下
 *
 * 2. 两者都取 2项：不等式无解，不存在此情况。
 *
 * 3. risk_1取 1项，risk_2取 2项，即 W_b - S_a > -S_b && W_a - S_b < -S_a ==> S_a > W_b + S_b
 *      必然满足 risk_1 < risk_2，因此取a下b上
 *
 * 4. risk_1取 2项，risk_1取 1项，与情形3对称，即 S_a < S_b - W_a时，取a上b下。
 *
 * 注意，1/2/3/4 四种情形得到的S_a取值范围求并集就是全集，将a下b上和a上b下的解求并集即可得到，
 *
 *   S + W 越大越应该放下面，按照这个值从大到小排序即可。
 */

struct Cow {
    long long s, w;
    Cow(long long _s, long long _w) : s(_s), w(_w) {}
    Cow() {}
    bool operator<(const Cow& rhs) {
        return s + w > rhs.s + rhs.w;
    }
};

Cow cows[MAX_N];

int main() {
    int n;
    scanf("%d", &n);
    long long total_weight = 0;
    for (int i = 0; i < n; ++i) {
        scanf("%lld %lld", &cows[i].w, &cows[i].s);  
        total_weight += cows[i].w;
    }

    std::sort(cows, cows + n);

    long long max_risk = std::numeric_limits<long long>::min();

    for (int i = 0; i < n; ++i) {
        total_weight -= cows[i].w;
        if (total_weight - cows[i].s > max_risk) {
            max_risk = total_weight - cows[i].s;
        }
    }
    printf("%lld\n", max_risk);
    
    return 0;
}
