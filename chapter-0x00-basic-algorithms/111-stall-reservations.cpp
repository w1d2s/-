#include <stdio.h>
#include <string.h>
#include <queue>
#include <algorithm>

#define MAX_N 50005

struct Cow {
    int a, b, idx;
    Cow() {}
    void assign(int _a, int _b, int _idx) {
        a = _a, b = _b, idx = _idx;
    }
    bool operator<(const Cow& rhs) const {
        return a < rhs.a;
    }
};

struct Stall {
    int end, idx;
    Stall(int _end, int _idx) : end(_end), idx(_idx) {}
    void assign(int _end) {
        end = _end;
    }
    // 注意：const函数
    bool operator<(const Stall& rhs) const {
        return end > rhs.end;
    }
};

Cow cow[MAX_N];
int stall_idx[MAX_N];

int main() {
    int N;
    while (scanf("%d", &N) != EOF) {
        memset(cow, 0, sizeof(cow));
        memset(stall_idx, 0, sizeof(stall_idx));
        for (int i = 0; i < N; ++i) {
            int a, b;
            scanf("%d %d", &a, &b);
            cow[i].assign(a, b, i);
        }
        std::sort(cow, cow + N);
        //for (int i = 0; i < N; ++i) {
        //    printf("%d ", cow[i].a);
        //}
        //printf("\n");
        std::priority_queue<Stall> min_heap;
        int idx = 1;
        for (int i = 0; i < N; ++i) {
            if (min_heap.empty() || min_heap.top().end >= cow[i].a) {
                min_heap.emplace(cow[i].b, idx);
                stall_idx[cow[i].idx] = idx;
                ++idx;
            } else {
                Stall cur_stall = min_heap.top();
                min_heap.pop();
                cur_stall.assign(cow[i].b);
                stall_idx[cow[i].idx] = cur_stall.idx;
                min_heap.push(cur_stall);
            }
        }
        --idx;
        printf("%d\n", idx);
        for (int i = 0; i < N; ++i) {
            printf("%d\n", stall_idx[i]);
        }
    }
    return 0;
}
