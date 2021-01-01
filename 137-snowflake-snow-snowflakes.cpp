#include <stdio.h>
#include <vector>
#include <list>

const int N = 100010, P = 99991;

struct SnowFlake {
  SnowFlake() {}
  SnowFlake(const int a,
            const int b,
            const int c,
            const int d,
            const int e,
            const int f) {
    s[0] = a, s[1] = b, s[2] = c;
    s[3] = d, s[4] = e, s[5] = f;
  }
  int s[6];
};

int Hash(const SnowFlake& snow) {
  int sum = 0;
  int prod = 1;
  for (int i = 0; i < 6; ++i) {
    sum = (sum + snow.s[i]) % P;
    prod = (long long)prod * snow.s[i] % P;
  }
  return (sum + prod) % P;
}

bool Equal(const SnowFlake& a,
           const SnowFlake& b) {
  int forward[12], reverse[12];
  for (int i = 0; i < 12; ++i) {
    forward[i] = b.s[i % 6];
    reverse[11 - i] = b.s[i % 6];
  }
  bool equal = false;
  for (int j = 0; j < 6; ++j) {
    for (int k = 0; k < 6; ++k) {
      if (a.s[k] != forward[k + j]) break;
      if (k == 5) equal = true;
    }
    if (equal) return true;
  }
  for (int j = 0; j < 6; ++j) {
    for (int k = 0; k < 6; ++k) {
      if (a.s[k] != reverse[k + j]) break;
      if (k == 5) equal = true;
    }
    if (equal) return true;
  }
  return false;
}

int main() {
  int n;
  scanf("%d", &n);
  std::vector<std::list<SnowFlake>> hash_list(N);
  bool found = false;
  for (int i = 0; i < n; ++i) {
    int a, b, c, d, e, f;
    scanf("%d %d %d %d %d %d", &a, &b, &c, &d, &e, &f);
    SnowFlake snow(a, b, c, d, e, f);
    int h = Hash(snow);
    std::list<SnowFlake>& cur_list = hash_list[h];
    for (auto iter = cur_list.begin(); iter != cur_list.end(); ++iter) {
      if (Equal(*iter, snow)) {
        found = true;
        break;
      }
    }
    cur_list.push_back(snow);
  }
  if (found) {
    printf("Twin snowflakes found.\n");
  } else {
    printf("No two snowflakes are alike.\n");
  }
  return 0;
}

