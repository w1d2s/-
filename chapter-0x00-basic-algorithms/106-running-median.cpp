#include <stdio.h>
#include <functional>
#include <queue>

/* 对顶堆做法 */

class RunningMedian {
public:
    RunningMedian() : _n(0), _median(0) {}
    int insert(const int val) {
        if (_n == 0) {
            _median = val;
            ++_n;
            return _median;
        }
        if (_n % 2 == 1) {
            if (val <= _median) {
                _max_heap.push(val);
            } else {
                _min_heap.push(val);
            }
            ++_n;
            return 0.0; // invalid median, just placehoder;
        } else {
            size_t left_sz = _max_heap.size();
            size_t right_sz = _min_heap.size();
            if (left_sz > right_sz) {
                if (val < _median) {
                    _min_heap.push(_median);
                    _max_heap.push(val);
                    _median = _max_heap.top();
                    _max_heap.pop();
                } else {
                    _min_heap.push(val);
                }
            } else if (left_sz < right_sz) {
                if (val > _median) {
                    _max_heap.push(_median);
                    _min_heap.push(val);
                    _median = _min_heap.top();
                    _min_heap.pop();
                } else {
                    _max_heap.push(val);
                }
            }
            ++_n;
            return _median;
        }
    }
private:
    int _n, _median;
    std::priority_queue<int, std::vector<int>, std::less<int>> _max_heap; // left half
    std::priority_queue<int, std::vector<int>, std::greater<int>> _min_heap; // right half
};

int main() {
    int p;
    scanf("%d", &p);
    while (p--) {
        int idx, m;
        scanf("%d %d", &idx, &m);
        printf("%d %d\n", idx, (m + 1) / 2);
        RunningMedian run_med;
        for (int i = 0; i < m; ++i) {
            int val;
            scanf("%d", &val);
            int med = run_med.insert(val);
            if ((i + 1) % 2 == 1) {
                printf("%d", med);
                if (i < m - 1) {
                    if (((i + 2) / 2) % 10 == 0) {
                        printf("\n");
                    } else {
                        printf(" ");
                    }
                } else {
                    printf("\n");
                }
            }
        }
    }
    return 0;
}
