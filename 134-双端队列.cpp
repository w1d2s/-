#include <stdio.h>
#include <algorithm>
#include <vector>

#define MAX_N 200005
#define INT_MIN -2147483648
#define INT_MAX 2147483647

/* 关键点：
 * 1. 从直接求解转换为先排序，再划分为尽可能少的段落，使每个段落可以形成一个双端队列。
 * 2. 什么样的段落可以转换为双端队列？由于A[i]是按照i从小到大依次处理，根据双端队列
 *    的入队规则，段落的下标数组满足单谷性质时可以形成双端队列（先下降在上升）。
 * 3. 相同数字之间的顺序可以任意调换。
 * 4. 贪心策略：尽可能加入前一段的队列，证明正确性。
 */

struct Pair {
  Pair(int _v, int _idx): v(_v), idx(_idx) {}
  int v, idx;
  bool operator<(const Pair& p) const {
    return v < p.v;
  }
};

struct Segment {
  Segment():
    min_idx(INT_MAX), max_idx(INT_MIN), decending(true) {}
  Segment(const Pair& p):
    val(p.v), beg(p.idx), end(p.idx), min_idx(p.idx), max_idx(p.idx) {}
  void append(const Pair& p) {
    end = p.idx;
    min_idx = std::min(min_idx, p.idx);
    max_idx = std::max(max_idx, p.idx);
  }
  void refresh(const Pair& p) {
    val = p.v;
    beg = end = p.idx;
    min_idx = max_idx = p.idx;
  }
  int val;
  int beg, end;
  int min_idx, max_idx;
  bool decending;
};

void try_merge_with_prev_seg(const Segment& prev,
                             Segment& cur,
                             int& queue_count) {
  if (prev.decending) {
    if (cur.max_idx < prev.min_idx) {
      cur.decending = true;
    } else {
      cur.decending = false;
    }
  } else {
    if (cur.min_idx > prev.max_idx) {
      cur.decending = false;
    } else {
      cur.decending = true;
      ++queue_count;
    }
  }
}


int main() {
  int N;
  std::vector<Pair> A;
  scanf("%d", &N);
  for (int i = 0; i < N; ++i) {
    int v;
    scanf("%d", &v);
    A.emplace_back(v, i);
  }

  std::sort(A.begin(), A.end());

  int queue_count = 1;
  std::vector<Segment> S;
  Segment seg(A[0]);

  for (int i = 1; i < N; ++i) {
    if (A[i].v == A[i - 1].v) {
      seg.append(A[i]);
      if (i == N - 1 && S.size() > 0) {
        auto prev = S.back();
        try_merge_with_prev_seg(prev, seg, queue_count);
      }
    } else {
      if (S.size() > 0) {
        auto prev = S.back();
        try_merge_with_prev_seg(prev, seg, queue_count);
      }
      S.push_back(seg);
      seg.refresh(A[i]);
    }
  }

  printf("%d\n", queue_count);
  return 0;
}
