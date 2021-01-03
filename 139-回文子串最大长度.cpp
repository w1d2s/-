#include <stdio.h>
#include <cstring>
#include <algorithm>

/* 注意处理下标的细节
 * 另外hash表用vector会被卡TLE，换成数组就过了
 */

typedef unsigned long long ull;

const int N = 1000010;
const int P = 131;

char s[N]; // index starts from 1
ull P_base[N] = {1};
ull hash_forward[N] = {0};
ull hash_reverse[N] = {0};

void CalPrefixHashBidirectional(const char* str,
                                const int length) {
  for (int i = 1; i <= length; ++i) {
    hash_forward[i] = hash_forward[i - 1] * P + static_cast<ull>(str[i] - 'a');
    P_base[i] = P_base[i - 1] * P;
  }
  for (int j = length; j >= 1; --j) {
    hash_reverse[j] = hash_reverse[j + 1] * P + static_cast<ull>(str[j] - 'a');
  }
}

ull QueryForwardSubStrHash(const int l, const int r) {
  return hash_forward[r] - hash_forward[l - 1] * P_base[r - l + 1];
}

ull QueryReverseSubStrHash(const int l, const int r) {
  return hash_reverse[l] - hash_reverse[r + 1] * P_base[r - l + 1];
}

bool IsPalindrome(const int l_forward, const int r_forward,
                  const int l_reverse, const int r_reverse) {
  ull forward_half = QueryForwardSubStrHash(l_forward, r_forward);
  ull reverse_half = QueryReverseSubStrHash(l_reverse, r_reverse);
  return forward_half == reverse_half;
}

int main() {
  int t = 1;
  while (true) {
    memset(s, 0, sizeof(s));
    scanf("%s", &s[1]);
    if ('E' == s[1]) break;
    int len = strlen(&s[1]);
    CalPrefixHashBidirectional(s, len);
    int max_palindrome_len = -1;

    for (int i = 1; i < len * 2; ++i) {
      if (i % 2 == 1) {
        int idx = (i + 1) >> 1;
        int max_half_len = std::min(idx, len - idx + 1);
        int lo = 1, hi = max_half_len;
        while (lo <= hi) {
          int mid = (lo + hi) >> 1;
          int l_forward = idx - mid + 1, r_forward = idx;
          int l_reverse = idx, r_reverse = idx + mid - 1;
          if (IsPalindrome(l_forward, r_forward,
                           l_reverse, r_reverse)) {
            lo = mid + 1;
          } else {
            hi = mid - 1;
          }
        }
        max_palindrome_len = std::max(max_palindrome_len, hi * 2 - 1);
      } else {
        int idx_left = i / 2, idx_right = i / 2 + 1;
        int max_half_len = std::min(idx_left, len - idx_right + 1);
        int lo = 1, hi = max_half_len;
        while (lo <= hi) {
          int mid = (lo + hi) >> 1;
          int l_forward = idx_left - mid + 1;
          int r_forward = idx_left;
          int l_reverse = idx_right;
          int r_reverse = idx_right + mid - 1;
          if (IsPalindrome(l_forward, r_forward,
                           l_reverse, r_reverse)) {
            lo = mid + 1;
          } else {
            hi = mid - 1;
          }
        }
        max_palindrome_len = std::max(max_palindrome_len, hi * 2);
      }
    }
    printf("Case %d: %d\n", t, max_palindrome_len);
    ++t;
  }
  return 0;
}
