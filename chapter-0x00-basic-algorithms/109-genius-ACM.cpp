#include <stdio.h>
#include <string.h>
#include <algorithm>

#define MAX_N 500005

/* 思路：倍增法，并且利用已经排好序的数组和后面扩充的部分归并
 * 注意爆long long 的问题
 */

int arr[MAX_N], sorted_arr[MAX_N], tmp_arr[MAX_N];

void merge(int* src_a, int left_a, int right_a,
        int* src_b, int left_b, int right_b, int* dest) {
    int len = (right_b - left_b + 1) + (right_a - left_a + 1);
    int tmp_pos = 0;
    while (left_a <= right_a && left_b <= right_b) {
        if (src_a[left_a] <= src_b[left_b]) {
            dest[tmp_pos++] = src_a[left_a++];
        } else {
            dest[tmp_pos++] = src_b[left_b++];
        }
    }
    while (left_a <= right_a) {
        dest[tmp_pos++] = src_a[left_a++];
    }
    while (left_b <= right_b) {
        dest[tmp_pos++] = src_b[left_b++];
    }
}

long long check_sum(int left, int right, int p, int M) {
    for (int i = right + 1; i <= right + p; ++i) {
        tmp_arr[i] = arr[i];
    }
    std::sort(tmp_arr + right + 1, tmp_arr + right + p + 1);
    merge(sorted_arr, left, right, tmp_arr, right + 1, right + p, tmp_arr + left);
    int i = left, j = right + p;
    long long sum = 0;
    while (M > 0 && i < j) {
        // Note 1 : 中间结果可能爆int，要用long long
        sum += (long long)(tmp_arr[j] - tmp_arr[i]) * (tmp_arr[j] - tmp_arr[i]);
        --M;
        ++i;
        --j;
    }
    return sum;
}

int main() {
    int k;
    scanf("%d", &k);
    while (k--) {
        int n, m;
        long long t;
        scanf("%d %d %lld", &n, &m, &t);
        memset(arr, 0, sizeof(arr));
        memset(sorted_arr, 0, sizeof(sorted_arr));
        memset(tmp_arr, 0, sizeof(tmp_arr));
        for (int i = 1; i <= n; ++i) {
            scanf("%d", &arr[i]);
        }
        int left = 1, right = 1, p = 1;
        int cnt = 0;
        sorted_arr[left] = arr[left];
        while (right <= n) {
            if (0 == p) {
                left = right + 1;
                right = left;
                p = 1;
                ++cnt;
                // Note 2 : 注意每一段结束开启新一段的时候，把下一段第一个元素复制到sorted_arr
                if (left < n) {
                    sorted_arr[left] = arr[left];
                }
            }
            while (right + p <= n && check_sum(left, right, p, m) <= t) {
                for (int i = left; i <= right + p; ++i) {
                    sorted_arr[i] = tmp_arr[i];
                }
                right += p;
                p *= 2;
            }
            p /= 2;
        }
        printf("%d\n", cnt);
    }
    return 0;
}
