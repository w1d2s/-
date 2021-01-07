#include <stdio.h>
#include <stdint.h>
#include <cstring>
#include <algorithm>

/* 把32位无符号int视作长度为32的0/1串，用trie存储
 * 寻找异或最大的pair时，从被查询数v的最高位开始，
 * 先按照最高位取反的bit在trie中查找，如果查找到了就把结果
 * 该位置为1，如果没找到，就按照不取反的查找，但是结果该位为0
 * 搜索到底就是与被查找数组成最大的异或对的数。
 * 这其中有一些贪心的思想。
 */

// 每个整数占据31个节点位置，整数数目不超过1e5，因此总结点数不超过31 * 1e5
const int MAX_N = 31 * (1e5 + 5); 

int trie[MAX_N][2], end[MAX_N];
int tot = 1;

void Insert(const uint32_t v) {
  int p = 1;
  for (int i = 31; i >= 0; --i) {
    int ch = int(bool((1 << i) & v));
    if (0 == trie[p][ch]) {
      ++tot;
      trie[p][ch] = tot;
    }
    p = trie[p][ch];
  }
  end[p] = 1;
}

uint32_t SearchXor(const uint32_t v) {
  uint32_t res = 0, nor_v = ~v;
  int p = 1;
  for (int i = 31; i >= 0; --i) {
    int ch = int(bool((1 << i) & nor_v));
    if (0 != trie[p][ch]) {
      p = trie[p][ch];
      res |= (1 << i);
    } else {
      ch = int(bool((1 << i) & v));
      p = trie[p][ch];
    }
  }
  return res;
}

int main() {
  int n;
  int max_res = 0;
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    uint32_t tmp;
    scanf("%u", &tmp);
    Insert(tmp);
    uint32_t xor_res = SearchXor(tmp);
    if (xor_res > max_res) {
      max_res = xor_res;
    }
  }
  printf("%u\n", max_res);
  return 0;
}
