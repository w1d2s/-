// Forward declaration of compare API.
// bool compare(int a, int b);
// return bool means whether a is less than b.

/* 思路：假设前k-1个元素已经排好了，用二分法找出第k个元素的位置
 * 每个元素比较次数log(k),总共不超过nlog(n)次比较
 */

class Solution {
public:
    vector<int> specialSort(int N) {
        vector<int> sorted_arr(N, 0);
        sorted_arr[0] = 1;
        for (int cnt = 2; cnt <= N; ++cnt) {
            int l = 0, r = cnt - 1, mid;
            while (l < r) {
                mid = (l + r) >> 1;    
                if (compare(cnt, sorted_arr[mid])) {
                    r = mid;
                } else {
                    l = mid + 1;
                }
            }
            for (int i = cnt - 2; i >= l; --i) {
                sorted_arr[i + 1] = sorted_arr[i];
            }
            sorted_arr[l] = cnt;
        }
        return sorted_arr;
    }
};
