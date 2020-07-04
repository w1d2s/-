#include <stdio.h>
#include <string.h>
#include <algorithm>

/* 贪心策略：两种对称的方法：
 * 1. 从大到小排序minSPF，依次对每头牛考虑范围内可用的SPF最大的防晒霜。
 *    因为如果当前的牛可用的防晒霜有x和y，且SPF[x] < SPF[y]，那么对后面的牛，
 *    由于minSPF一定比当前的小，所以x和y的下界一定满足，再考虑上界，有三种可能：
 *    x/y都能用，x能用y不能用，都不能用；因此当前选择y对后续影响最小。
 * 2. 从小到大排序maxSPF，依次对每头牛考虑范围内可用的SPF最小的防晒霜。
 * 3. 如果有当前牛用了某防晒霜导致后面有一头牛不能满足，给当前的用；因为每头牛
 *    权重都是1.
 */

struct Cow {
    int minSPF, maxSPF;
    Cow() {}
    void assign(int _min, int _max) {
        minSPF = _min, maxSPF = _max;
    }
    bool operator<(const Cow& rhs) {
        //return minSPF > rhs.minSPF;
        return maxSPF < rhs.maxSPF;
    }
};

struct Sunscreen {
    int SPF, cover;
    Sunscreen() {}
    void assign(int _SPF, int _cover) {
        SPF = _SPF, cover = _cover;
    }
};

Cow cow[2510];
Sunscreen sunscreen[2510];

int main() {
    int C, L;
    while (scanf("%d %d", &C, &L) != EOF) {
        memset(cow, 0, sizeof(cow));
        memset(sunscreen, 0, sizeof(sunscreen));
        for (int i = 0; i < C; ++i) {
            int min, max;
            scanf("%d %d", &min, &max);
            cow[i].assign(min, max);
        }
        for (int i = 0; i < L; ++i) {
            int spf, cover;
            scanf("%d %d", &spf, &cover);
            sunscreen[i].assign(spf, cover);
        }
        std::sort(cow, cow + C);
        int result = 0;
        for (int i = 0; i < C; ++i) {
            //int max_sunscreen_spf = -1;
            int min_sunscreen_spf = 2000;
            int idx = -1;
            for (int j = 0; j < L; ++j) {
                if (cow[i].minSPF <= sunscreen[j].SPF &&
                    sunscreen[j].SPF <= cow[i].maxSPF &&
                    sunscreen[j].cover > 0) {
                    //if (sunscreen[j].SPF > max_sunscreen_spf) {
                    //    max_sunscreen_spf = sunscreen[j].SPF;
                    //    idx = j;
                    //}
                    if (sunscreen[j].SPF < min_sunscreen_spf) {
                        min_sunscreen_spf = sunscreen[j].SPF;
                        idx = j;
                    }
                }
            }
            if (idx != -1) {
                ++result;
                --sunscreen[idx].cover;
            }
        }
        printf("%d\n", result);
    }
    return 0;
}
