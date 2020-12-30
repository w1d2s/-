#include <stdio.h>
#include <algorithm>
#include <deque>

#define MAX_N 300005
#define INT_MIN -2147483648

/* 优先队列
 * 维护一个下标递增、前缀和也递增的序列，这就是最优解的策略空间
 */

int main() {
  long S[MAX_N] = {0};
  int n, m;
  scanf("%d %d", &n, &m);
  for (int i = 1; i <= n; ++i) {
    int a;
    scanf("%d", &a);
    S[i] = S[i - 1] + a;
  }
  std::deque<int> Q;
  Q.push_back(0);
  long res = INT_MIN;
  for (int r = 1; r <= n; ++r) {
    while (!Q.empty() && r - Q.front() > m) {
      Q.pop_front();
    }
    res = std::max(res, S[r] - S[Q.front()]);
    while (!Q.empty() && S[Q.back()] >= S[r]) {
      Q.pop_back();
    }
    Q.push_back(r);
  }
  printf("%ld\n", res);
  return 0;
}
