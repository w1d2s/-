#include <stdio.h>
#include <string.h>

#define MAX_N 250010

/* 如何证明可解性和逆序对奇偶性的充要条件？ */

void merge(int* arr, int* tmp_arr, 
        int left_pos, int right_pos, int right_end, long long& num_rev_pair) {
    int left_end = right_pos - 1;
    int tmp_pos = left_pos;
    int len = right_end - left_pos + 1;
    while (left_pos <= left_end && right_pos <= right_end) {
        if (arr[left_pos] <= arr[right_pos]) {
            tmp_arr[tmp_pos++] = arr[left_pos++];
        } else {
            tmp_arr[tmp_pos++] = arr[right_pos++];
            num_rev_pair += left_end - left_pos + 1;
        }
    }
    while (left_pos <= left_end) {
        tmp_arr[tmp_pos++] = arr[left_pos++]; 
    }
    while (right_pos <= right_end) {
        tmp_arr[tmp_pos++] = arr[right_pos++];
    }
    for (int i = 0; i < len; ++i, --right_end) {
        arr[right_end] = tmp_arr[right_end]; 
    }
}

void merge_sort(int* arr, int* tmp_arr, 
        int left, int right, long long& num_rev_pair) {
    if (left < right) {
        int mid = (left + right) / 2;
        merge_sort(arr, tmp_arr, left, mid, num_rev_pair);
        merge_sort(arr, tmp_arr, mid + 1, right, num_rev_pair);
        merge(arr, tmp_arr, left, mid + 1, right, num_rev_pair);
    }
}

int arr[MAX_N], tmp_arr[MAX_N];

int main() {
    int n;
    while (scanf("%d", &n) != EOF) {
        memset(arr, 0, sizeof(arr));
        memset(tmp_arr, 0, sizeof(tmp_arr));
        for (int i = 1, j = 1; i <= n * n; ++i) {
            int tmp;
            scanf("%d", &tmp);
            if (0 == tmp) {
                continue;
            }
            arr[j++] = tmp;
        }
        long long num_rev_before = 0;
        merge_sort(arr, tmp_arr, 1, n * n - 1, num_rev_before);
        for (int i = 1, j = 1; i <= n * n; ++i) {
            int tmp;
            scanf("%d", &tmp);
            if (0 == tmp) {
                continue;
            }
            arr[j++] = tmp;
        }
        long long num_rev_after = 0;
        merge_sort(arr, tmp_arr, 1, n * n - 1, num_rev_after);
        if ((num_rev_before % 2) == (num_rev_after % 2)) {
            printf("TAK\n");
        } else {
            printf("NIE\n");
        }
    }
    return 0;
}
