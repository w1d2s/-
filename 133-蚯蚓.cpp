#include <stdio.h>
#include <queue>
#include <algorithm>
#include <vector>

#define MAX_N 100005
#define INT_MIN -2147483648

int max_of_three(const int a,
                 const int b,
                 const int c) {
  if (a > b) {
    if (a > c) return 1;
    if (c > b) return 3;
    return 2;
  }
  if (b > c) return 2;
  return 3;
}

int pop_max_from_three_queues(
    std::queue<int>& A,
    std::queue<int>& B,
    std::queue<int>& C,
    const int pos) {
  int val;
  if (pos == 1) {
    val = A.front();
    A.pop();
  } else if (pos == 2) {
    val = B.front();
    B.pop();
  } else {
    val = C.front();
    C.pop();
  }
  return val;
}

void cut_x_u_v(const int x,
               const int u,
               const int v,
               int& res_b,
               int& res_c) {
  double tmp = static_cast<long>(x) * static_cast<long>(u) / v;
  res_b = static_cast<int>(tmp);
  res_c = x - res_b;
}

void print_vec(const std::vector<int>& v) {
  for (int i = 0; i < v.size(); ++i) {
    printf("%d", v[i]);
    if (i < v.size() - 1) printf(" ");
  }
  printf("\n");
}

int main() {
  int n, m, q, u, v, t;
  int arr[MAX_N];
  int delta = 0;
  std::queue<int> A, B, C;

  scanf("%d %d %d %d %d %d", &n, &m, &q, &u, &v, &t);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &arr[i]);
  }

  std::sort(arr, arr + n);
  for (int i = n - 1; i >= 0; --i) {
    A.push(arr[i]);
  }

  int a = 0, b = 0, c = 0;
  std::vector<int> arr_len_before_cut;
  for (int j = 1; j <= m; ++j) {
    a = b = c = INT_MIN;
    if (!A.empty()) a = A.front();
    if (!B.empty()) b = B.front();
    if (!C.empty()) c = C.front();
    int pos = max_of_three(a + delta, b + delta, c + delta);
    int x_to_cut = pop_max_from_three_queues(A, B, C, pos) + delta;
    if (j % t == 0) {
      arr_len_before_cut.push_back(x_to_cut);
    }
    int res_b = 0, res_c = 0;
    cut_x_u_v(x_to_cut, u, v, res_b, res_c);
    delta += q;
    B.push(res_b - delta);
    C.push(res_c - delta);
  }
  print_vec(arr_len_before_cut);

  int k = 1;
  std::vector<int> arr_decending_len;
  while (true) {
    a = b = c = INT_MIN;
    if (!A.empty()) a = A.front();
    if (!B.empty()) b = B.front();
    if (!C.empty()) c = C.front();
    int pos = max_of_three(a + delta, b + delta, c + delta);
    int x = pop_max_from_three_queues(A, B, C, pos) + delta;
    if (k % t == 0) {
      arr_decending_len.push_back(x);
    }
    ++k;
    if (A.empty() && B.empty() && C.empty()) break;
  }
  print_vec(arr_decending_len);
  return 0;
}
