#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <set>
#include <algorithm>

using namespace std;

/* 高度关系是显然的，但是降低时间复杂度的关键
 * 在于将原序列的区间操作转化为差分序列的单点操作
 */

int main() {
    int n, p, h, m;
    int c[10005], d[10005];
    while (scanf("%d %d %d %d", &n, &p, &h, &m) != EOF) {
        memset(c, 0, sizeof(c));
        memset(d, 0, sizeof(d));
        set<pair<int, int> > see_each_other;
        while (m--) {
            int i, j;
            scanf("%d %d", &i, &j);
            if (i > j) {
                swap(i, j);
            }
            if (see_each_other.find(make_pair(i, j)) != see_each_other.end()) {
                continue;
            }
            see_each_other.insert(make_pair(i, j));
            d[i + 1] -= 1;
            d[j] += 1;
        }
        c[0] = 0;
        for (int i = 1; i <= n; ++i) {
            c[i] = c[i - 1] + d[i];
        }
        for (int i = 1; i <= n; ++i) {
            c[i] -= c[p];
            printf("%d\n", h + c[i]);
        }
    }
    return 0;
}
