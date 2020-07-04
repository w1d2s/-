#include <stdio.h>
#include <math.h>
#include <string.h>
#include <vector>
#include <algorithm>

#define MAX_N 1010

/* 假设有一对相邻的大臣i和j：
 *  K M_1 M_2 ... M_i M_j ..... M_n
 * |<---A区域--->|       |<-B区域->| 
 * 
 * 他们前面所有人左手数字乘积为S，那么考虑如下几种情况：
 * 1. i在前j在后(i,j)：两人中最大值为 S * max(1/R[i], L[i]/R[j])
 *    1-1. i为最大值：1/R[i] > L[i]/R[j]，得到 R[j] > L[i]*R[i]，
 *          此时在(j,i)排序时自动满足2-1，即i为最大值，P_i_at_ji=L[i]/R[i]
 *    1-2. j为最大值：1/R[i] < L[i]/R[j]，得到 R[j] < L[i]*R[i]
 * 2. j在前i在后(j,i)：两人中最大值为 S * max(1/R[j], L[j]/R[i])
 *    2-1. i为最大值：1/R[j] < L[j]/R[i]，得到 R[j] > R[i]/L[j]
 *    2-2. j为最大值：1/R[j] > L[j]/R[i]，得到 R[j] < R[i]/L[j]，
 *          此时在(i,j)排序时自动满足1-2，即j为最大值，P_j_at_ij=L[i]/R[j]
 *
 * 先考虑1-1和2-2两种情况：当 R[j] > L[i]*R[i]时，(i,j)排列最大值为
 * P_i_at_ij = 1/R[i]，(j,i)排列最大值为P_i_at_ji = L[i]/R[i]，由于L[i]为正整数，
 * 自动得到P_i_at_ij < P_i_at_ji，即：要使最大值尽可能小，应该选择(i, j)排序。
 * R[j] < R[i]/L[i]时论证方法相同，应该选择(j,i)排序使最大值尽可能小。
 * 
 * 再考虑1-2和2-1两种情况：当R[j] 处于 (R[i]/L[i], L[i]*R[i])之间时，判断一下
 * 两种排列下最大值的关系（该选哪种排列就确定了），解出R[j]范围，就知道了R[j]在
 * 哪个范围下该选哪一种排列，才能使最大值尽可能小。
 * P_j_at_ij > P_i_at_ji时，该选(j,i)，解出 R[j] < R[i]*L[i]/L[j]. 
 * P_j_at_ij < P_i_at_ji时，该选(i,j)，解出 R[j] > R[i]*L[i]/L[j].
 *
 *
 *
 * 画在数轴上：
 *
 *   选择(j,i)排法 <-|   (j,i)    |     (i,j)   |-> 选择(i,j)排法
 * R[j]  ------------+------------+-------------+------------------->
 *               R[i]/L[i]  R[i]*L[i]/L[j]  L[i]*R[i]
 *
 * 综合起来就是 R[j]*L[j] < R[i]*L[i]时，j放前面，反之i放前面。
 *
 * 另外，注意到：
 * 1. 交换相邻的i和j，对A区域和B区域所有人得分没有影响，可以通过上述结论交换使得最大值变小，
 *    或至少不变。
 * 2. 对于i和j不相邻的情况，如果出现了逆序对，即存在 i+1 < j，使得R[i]*L[i] > R[j]*L[j]，那么
 *    对于 k = i+1，有三种情况：
 *    2-1. R[k]*L[k] < R[j]*L[j] < R[i]*L[i]，(i,k)是相邻逆序对，应当交换，
 *         然后再次递归的考虑(i,...,j)段，但此时(i,...j)段长度减一。
 *    2-2. R[j]*L[j] < R[i]*L[i] < R[k]*L[k]，(k,...,j)是不相邻逆序对，递归处理之，
 *         他的长度也比(i,...,j)减一。
 *    2-3 .R[j]*L[j] < R[k]*L[k] < R[i]*L[i]，(k,...,j)是不相邻逆序对，递归处理之，
 *         长度比(i,...,j)减一，处理完之后再处理i和k/j的逆序对关系。
 *
 *  position : 1 2 3 4 5 6 7 8
 *    index  :   i k     j
 *
 *    注意三种情况下，i/j中至少有一个会和中间的元素k构成逆序对，意味着这时的结果一定不是最优的，
 *    可以通过消除逆序对使结果变好。处理这些规模更小的逆序对最终会回到相邻逆序对的情况，再把相邻
 *    逆序对消除即可，因此最终要把逆序对个数减至0才能使结果最优(最大值最小)。
 *    所以按照 R[i]*L[i]越小越靠前的方式排序所有大臣即可。
 */

struct Node {
    int l, r;
    bool operator<(const Node& rhs) {
        //注意，这样带等号是错误的，会导致std::sort段错误
        //return l * r <= rhs.l * rhs.r;
        return l * r < rhs.l * rhs.r;
    }
};

Node ministers[MAX_N];

std::vector<int> mul(const std::vector<int>& a, int b) {
    std::vector<int> r;
    int t = 0;
    for (int i = 0; i < a.size(); ++i) {
        t += a[i] * b;
        r.push_back(t % 10);
        t /= 10;
    }
    while (t) {
        r.push_back(t % 10);
        t /= 10;
    }
    return r;
}

std::vector<int> div(const std::vector<int>& a, int b) {
    std::vector<int> r;
    int t = 0;
    bool is_first = true;
    for (int i = a.size() - 1; i >= 0; --i) {
        t = t * 10 + a[i];
        int x = t / b;
        if (!is_first || x) {
            r.push_back(x);
            is_first = false;
        }
        t %= b;
    }
    if (is_first) {
        r.push_back(0);
    }
    std::reverse(r.begin(), r.end());
    return r;
}

bool is_greater_than(const std::vector<int>& a, const std::vector<int>& b) {
    if (a.size() != b.size()) {
        return a.size() > b.size();
    }
    for (int i = a.size() - 1; i >= 0; --i) {
        if (a[i] == b[i]) {
            continue;
        }
        return a[i] > b[i];
    }
    return false;
}

int main() {
    int n;
    scanf("%d", &n);
    memset(ministers, 0, sizeof(ministers));
    for (int i = 0; i <= n; ++i) {
        scanf("%d %d", &ministers[i].l, &ministers[i].r);
    }
    std::sort(ministers + 1, ministers + 1 + n);
    std::vector<int> max(1, 0);
    std::vector<int> prev_product(1, 1);
    for (int i = 0; i <= n; ++i) {
        if (i > 0) {
            std::vector<int> tmp = div(prev_product, ministers[i].r);
            if (is_greater_than(tmp, max)) {
                std::swap(max, tmp);
            }
        }
        prev_product = mul(prev_product, ministers[i].l);
    }
    for (int i = max.size() - 1; i >= 0; --i) {
        printf("%d", max[i]);
    }
    printf("\n");
    return 0;
}
