#include <stdio.h>
#include <algorithm>

#define MAX 100005

int main() {
    int n;
    int pos[MAX];
    while (scanf("%d", &n) != EOF) {
        for (int i = 0; i < n; ++i) {
            scanf("%d", &pos[i]);
        }
        std::sort(pos, pos + n);
        int dist = 0;
        if (n % 2 == 1) {
            int mid = (n - 1) / 2;
            for (int i = 0; i < mid; ++i) {
                dist += pos[mid] - pos[i];
            }
            for (int i = mid + 1; i < n; ++i) {
                dist += pos[i] - pos[mid];
            }
        } else {
            int mid = n / 2 - 1;
            int median = (pos[mid] + pos[mid + 1]) / 2;
            for (int i = 0; i <= mid; ++i) {
                dist += median - pos[i];
            }
            for (int i = mid + 1; i < n; ++i) {
                dist += pos[i] - median;
            }
        }
        printf("%d\n", dist);
    }
    return 0;
}

