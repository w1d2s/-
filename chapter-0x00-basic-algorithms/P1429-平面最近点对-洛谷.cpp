#include <iostream>
#include <iomanip>
#include <string.h>
#include <cmath>
#include <limits>
#include <vector>
#include <algorithm>

#define MAX_N 200005

/* 利用分治法解决平面最近点对问题，注意以下几点：
 * 
 * 1. 按照y给点排序时，可以将归并排序融入算法，保证复杂度为O(nlogn).
 * 2. merge分界线两边的点的最小距离时，左边每个满足
 *      mid_x - delta <= x <= mid_x的点P(x, y)最多与右边的
 *      落在[mid_x, mid_x + delta] x [y - delta, y + delta]范围内6个点计算距离（思考为什么是6个点），
 *      注意代码中对这一步的处理：如何找P点在边界右边第一个开始计算的点，
 *      以及delta可能为INF的情况.
 * 3. 可能有极端情况出现，最好是开始处理前将坐标系随机旋转一个角度theta，
 *      但这题数据弱，不随机也能过。
 *
 * P.S. 注意归并操作会破坏按 x 坐标的有序性，从而不能得到正确的 mid_x，
 *      必须在 [l, mid] 和 [mid + 1, r] 进行归并前把正确的 mid_x 保存下来。
 *
 */

using namespace std;

const double INF = numeric_limits<double>::max() / 3;

struct Point {
    int id;
    double x, y;
};

void print_point(const Point& p) {
    cout << "id : " << p.id << " x : " << p.x << " y : " << endl;
}

struct Cmp_x {
    bool operator()(const Point& a, const Point& b) {
        return a.x < b.x;
    }
}; 

Point p_arr[MAX_N], tmp_p_arr[MAX_N];

int find_mid(const int lo, const int hi) {
    if ((hi - lo) % 2 == 1) {
        return lo + (hi - lo + 1) / 2;        
    } else {
        return lo + (hi - lo) / 2;
    }
}

double cal_dist(const Point& a, const Point& b) {
    return sqrt( (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y) );
}

void merge_y(const int lo_left, const int lo_right, const int hi_right) {
    int hi_left = lo_right - 1;
    int i = lo_left, j = lo_right;
    int k = lo_left;
    while (i <= hi_left && j <= hi_right) {
        if (p_arr[i].y <= p_arr[j].y) {
            tmp_p_arr[k++] = p_arr[i++];
        } else {
            tmp_p_arr[k++] = p_arr[j++];
        }
    }
    while (i <= hi_left) {
        tmp_p_arr[k++] = p_arr[i++]; 
    }
    while (j <= hi_right) {
        tmp_p_arr[k++] = p_arr[j++];
    }

    for (int m = lo_left; m <= hi_right; ++m) {
        p_arr[m] = tmp_p_arr[m];
    }
}

void cal_nearest_merge(const int lo_left, const int lo_right,
                    const int hi_right, const double mid_x,
                    const double delta, double& min_dist) {
    int hi_left = lo_right - 1;
    //  注意，这里就需要对 mid_x 左右两边的点进行按y从小到大归并，
    //      下面计算[mid_x - delta, mid_x + delta]较方便。
    //
    merge_y(lo_left, lo_right, hi_right);

    //  注意！这里lo_right处的点已经不是mid_x了！！！

    min_dist = INF;

    int k = 0;
    for (int i = lo_left; i <= hi_right; ++i) {
        if (p_arr[i].x <= mid_x + delta &&
                mid_x - delta <= p_arr[i].x) {
            tmp_p_arr[k++] = p_arr[i];
        }
    }
   
    for (int i = 0; i < k; ++i) {
        for(int j = i - 1; j >= 0 && tmp_p_arr[i].y - tmp_p_arr[j].y <= delta; --j) {
            double dist = cal_dist(tmp_p_arr[i], tmp_p_arr[j]);
            min_dist = min(dist, min_dist);
        }
    }
}

void cal_nearest_point_pair(const int lo, const int hi, double& min_dist) {
    if (hi - lo <= 1) {
        // less or equal than 2 points, calculate directly.
        if (hi - lo == 1) {
            min_dist = cal_dist(p_arr[lo], p_arr[hi]);
            if (p_arr[lo].y > p_arr[hi].y) {
                swap(p_arr[lo], p_arr[hi]);
            }
        } else {
            min_dist = INF;
        }
        return;
    }
    
    int lo_right = find_mid(lo, hi);
    double dist_left, dist_right;
    
    //  注意！下面进行归并操作之后，点就不是按照x从小到大有序排列了，
    //      必须现在把正确的 mid_x 保存下来
    double mid_x = p_arr[lo_right].x;

    cal_nearest_point_pair(lo, lo_right - 1, dist_left);
    cal_nearest_point_pair(lo_right, hi, dist_right);

    double delta = min(dist_left, dist_right);
    double min_dist_merge;
    
    cal_nearest_merge(lo, lo_right, hi, mid_x, delta, min_dist_merge);
    min_dist = min(min_dist_merge, delta);
}


int main() {
    int n;
    cin >> n;
    memset(p_arr, 0, sizeof(p_arr));
    memset(tmp_p_arr, 0, sizeof(tmp_p_arr));
    for (int i = 0; i < n; ++i) {
        double x, y;
        // should do random rotation here
        cin >> x >> y;
        p_arr[i].id = i + 1;
        p_arr[i].x = x;
        p_arr[i].y = y;
    }
    
    sort(p_arr, p_arr + n, Cmp_x());

    double min_dist;
    cal_nearest_point_pair(0, n - 1, min_dist);
    
    cout << fixed << setprecision(4) << min_dist << endl;
    return 0;
}
