#include <stdio.h>
#include <cstring>
#include <algorithm>

/* 长度为n的两个字符串比较字典序，最坏情况复杂度为O(n)
 * 一个长度为n的字符串有n个后缀，直接对所有后缀排序，复杂度为O(n * n * logn)
 * 实际上比较字典序，只要比较最长公共前缀后面一个字符的大小即可
 * 而用字符串Hash以O(n)复杂度处理出所有后缀的Hash值后，对任意两个后缀
 * 可以用二分答案的方法求出最长公共前缀长度，因为查询字符串任何子串的Hash值只需要O(1)
 * 所以两个长度为n的字符串比较字典序只需要O(logn)即可，排序所有后缀需要O(n * logn * logn)
 *
 * 注意：直接对字符串hash值排序当做字典序是错误的，因为求hash值时候有对M取模的操作.
 */

typedef unsigned long long ull;

const int N = 300005;
const int P = 131;

char s[N]; // index starts from 0
ull P_base[N] = {1};
ull hash[N] = {0};

struct Suffix {
  Suffix() = default;
  Suffix(int _l, int _r):
    l(_l), r(_r), length(r - l + 1) {}
  int l, r, length; // starts from 0
  void set(int _l, int _r) {
    l = _l, r = _r, length = r - l + 1;
  }
};

Suffix sa[N];

void CalPrefixHash(const char* s,
                   const int len) {
  for (int i = 1; i <= len; ++i) {
    // Note index
    hash[i] = hash[i - 1] * P + static_cast<ull>(s[i - 1] - 'a');
    P_base[i] = P_base[i - 1] * P;
  }
}

ull QuerySubstrHash(const int l, const int r) {
  // Note index
  return hash[r + 1] - hash[l] * P_base[r - l + 1];
}

int LongestCommonPrefixLength(const Suffix& a,
                              const Suffix& b) {
  int lo = 0, hi = std::min(a.length, b.length) - 1;
  while (lo <= hi) {
    int mid = (lo + hi) >> 1;
    ull prefix_a_hash = QuerySubstrHash(a.l, a.l + mid);
    ull prefix_b_hash = QuerySubstrHash(b.l, b.l + mid);
    if (prefix_a_hash == prefix_b_hash) {
      lo = mid + 1;
    } else {
      hi = mid - 1;
    }
  } 
  return hi + 1;
}

int compare_dict_order(const Suffix& a,
                       const Suffix& b) {
  int len_pre = LongestCommonPrefixLength(a, b);
  return s[a.l + len_pre] < s[b.l + len_pre];
}

int main() {
  memset(s, 0, sizeof(s));
  scanf("%s", s);
  int len = strlen(s);
  memset(sa, 0, sizeof(Suffix) * len);
  CalPrefixHash(s, len);

  for (int i = 0; i < len; ++i) {
    sa[i].set(i, len - 1);
  }
  std::sort(sa, sa + len, compare_dict_order);

  for (int i = 0; i < len; ++i) {
    if (i < len - 1) printf("%d ", sa[i].l);
    else printf("%d\n", sa[i].l);
  }
  
  for (int i = 0; i < len; ++i) {
    if (i == 0) {
      printf("0 ");
    } else if (0 < i && i < len - 1) {
      printf("%d ", LongestCommonPrefixLength(sa[i], sa[i - 1]));
    } else {
      printf("%d\n", LongestCommonPrefixLength(sa[i], sa[i - 1]));
    }
  }
  return 0;
}
