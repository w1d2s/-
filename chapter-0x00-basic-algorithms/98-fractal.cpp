#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <utility>

typedef std::pair<long long, long long> Point;

Point calc(int N, long long M) {
    if (N == 0) {
        return std::make_pair(0, 0);
    }
    long long prev_level_dist = pow(2, N - 1);
    long long prev_level_num = prev_level_dist * prev_level_dist;
    Point point_prev_level = calc(N - 1, M % prev_level_num);
    long long x = point_prev_level.first;
    long long y = point_prev_level.second;
    int type = M / prev_level_num;
    switch (type) {
    case 0:
        return std::make_pair(y, x);
    case 1:
        return std::make_pair(prev_level_dist  + x, y);
    case 2:
        return std::make_pair(prev_level_dist + x, prev_level_dist + y);
    case 3:
        return std::make_pair(prev_level_dist - 1 - y, 2 * prev_level_dist - 1 - x);
    }
}

long long calc_dist(Point pa, Point pb) {
    long long dx = pa.first - pb.first;
    long long dy = pa.second - pb.second;
    return (long long)(0.5f + 10 * sqrt(dx * dx + dy * dy));
}

int main() {
    int n;
    scanf("%d", &n);
    while (n--) {
        int N;
        long long A, B;
        scanf("%d %lld %lld", &N, &A, &B);
        Point pa = calc(N, A - 1);
        //printf("x : %lld, y : %lld\n", pa.first, pa.second);
        Point pb = calc(N, B - 1);
        //printf("x : %lld, y : %lld\n", pb.first, pb.second);
        printf("%lld\n", calc_dist(pa, pb));
    }
    return 0;
}
