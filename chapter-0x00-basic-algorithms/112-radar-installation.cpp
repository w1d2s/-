#include <stdio.h>
#include <string.h>
#include <math.h>
#include <algorithm>

#define MAX_N 1010
#define DBL_MAX 1.79e+308
#define EPS 1e-10

/* 对于每一个小岛(x, y)和给定的半径d，可以计算出x轴上的
 * 一个区间[l, r]，使得雷达在这个区间内可以覆盖到该岛。
 * 于是问题转化为：给定一些区间l[i],r[i]，求最少的点的个数，
 * 使得每个区间内都至少有一个点。
 * 贪心法：对所有区间按照左端点l[i]从小到大排序，对每个雷达
 * 维护一个可行放置范围的最小右端点min_r_of_radar，如果
 * l[i] < min_r_of_radar，那么该小岛可以被该雷达覆盖；否则
 * 只能新增加一个雷达了，新雷达的min_r_of_radar = r[i].
 */

struct Interval {
    double l, r;
    Interval() {}
    void assign(double _l, double _r) {
        l = _l, r = _r;
    }
    bool operator<(const Interval& rhs) const {
        return l < rhs.l;
    }
};

void cal_interval_from_coordinate(const int x, const int y, 
        const int d, Interval& itv) {
    double dx = sqrt(double(d) * d - double(y) * y);
    double l = x - dx, r = x + dx;
    itv.assign(l, r);
}

Interval intervals[MAX_N];
double min_r_of_radar[MAX_N];

int main() {
    int n, d;
    while (scanf("%d %d", &n, &d) != EOF) {
        memset(intervals, 0, sizeof(intervals));
        bool no_solution = false;
        for (int i = 0; i < n; ++i) {
            int x, y;
            scanf("%d %d", &x, &y);
            if (y > d) {
                no_solution = true;
            }
            cal_interval_from_coordinate(x, y, d, intervals[i]);
        }
        if (no_solution) {
            printf("-1\n");
            continue;
        }
        std::sort(intervals, intervals + n);
        for (int i = 0; i < n; ++i) {
            min_r_of_radar[i] = DBL_MAX; 
        }
        int radar_idx = 0;
        for (int i = 0; i < n; ++i) {
            if (intervals[i].l <= min_r_of_radar[radar_idx]) {
                if (intervals[i].r < min_r_of_radar[radar_idx]) {
                    min_r_of_radar[radar_idx] = intervals[i].r;
                }
            } else {
                ++radar_idx;
                min_r_of_radar[radar_idx] = intervals[i].r;
            }
        }
        printf("%d\n", radar_idx + 1);
    }
    return 0;
}
