#include <stdio.h>
#include <string.h>
#include <unordered_map>
#include <vector>
#include <algorithm>

#define MAX_N 1010

using namespace std;

/* 关键思路：
 * 1. 求最值问题 转化为 二分答案判定可行性，给定边长mid，判断是否存在一个至少包住C单位的正方形。
 * 2. 如何判定？转化为二维前缀和差分问题，正方形左上角(x1, y1)，右下角(x2, y2)，根据容斥原理，
 *    正方形 Area = sum[x2][y2] - sum[x1][y2] - sum[x2][y1] + sum[x1][y1]
 *    求左上角坐标(x1, y1)时注意细节。
 * 3. 离散化：x和y可以分别用两个数组离散化，本题用一个，容易实现。注意实现细节。
 */

typedef pair<int, int> PII;

vector<int> dist;
int sum[MAX_N][MAX_N];
vector<PII> points;
unordered_map<int, int> dist_to_idx;

bool is_valid(int mid, int C) {
    // (x1, y1) 左上角，(x2, y2) 右下角，先找到卡住正方形对角的
    // 两个坐标，然后用前缀和差分。
    for (int i_x1 = 0, i_x2 = 1; i_x2 < dist.size(); ++i_x2) {
        while (dist[i_x2] - dist[i_x1 + 1] >= mid) {
            ++i_x1;
        }

        for (int i_y1 = 0, i_y2 = 1; i_y2 < dist.size(); ++i_y2) {
            while (dist[i_y2] - dist[i_y1 + 1] >= mid) {
                ++i_y1;
            }
            
            if (sum[i_x2][i_y2] - sum[i_x1][i_y2] - sum[i_x2][i_y1] + sum[i_x1][i_y1] >= C) {
                return true;
            }
        }
    }
    return false;
}

int main() {
    int C, N;
    scanf("%d %d", &C, &N);
    
    dist.push_back(0);
    
    for (int i = 0; i < N; ++i) {
        int x, y;
        scanf("%d %d", &x, &y);
        points.emplace_back(x, y);
    
        dist.push_back(x);
        dist.push_back(y);
    }
   
    // discretize x and y coordinate, put together.
    sort(dist.begin(), dist.end());
    dist.erase(unique(dist.begin(), dist.end()), dist.end());
    
    for (int i = 0; i < dist.size(); ++i) {
        dist_to_idx[dist[i]] = i;
    }

    memset(sum, 0, sizeof(sum));

    // calculate 2-D prefix sum
    for (int i = 0; i < points.size(); ++i) {
        int x = points[i].first, y = points[i].second;
        int i_x = dist_to_idx[x], i_y = dist_to_idx[y];
        ++sum[i_y][i_x];
    }

    for (int i = 1; i < dist.size(); ++i) {
        for (int j = 1; j < dist.size(); ++j) {
            // i for x , j for y
            sum[i][j] += sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1];
        }
    }
    
    // binary search answer
    int l = 1, r = 10000;
    while (l < r) {
        int mid = (l + r) >> 1;
        if (is_valid(mid, C)) {
            r = mid; 
        } else {
            l = mid + 1;
        }
    }
    printf("%d\n", r);

    return 0;
}


