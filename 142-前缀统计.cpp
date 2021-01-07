#include <stdio.h>
#include <cstring>

// const int MAX_LEN = 1000005; 报了Memory Limit Exceeded.
const int MAX_LEN = 100000; // 能过
char s[MAX_LEN];

int trie[MAX_LEN][26], cnt[MAX_LEN];
int tot;

void Init() {
  memset(trie, 0, sizeof(trie));
  memset(cnt, 0, sizeof(cnt));
  tot = 1;
}

void Insert(const char* s, const int len) {
  int p = 1;
  for (int i = 0; i < len; ++i) {
    int ch = s[i] - 'a';
    if (0 == trie[p][ch]) {
      ++tot;
      trie[p][ch] = tot;
    }
    p = trie[p][ch];
  }
  ++cnt[p];
}

int Search(const char* s, const int len) {
  int p = 1, prefix_cnt = 0;
  for (int i = 0; i < len; ++i) {
    int ch = s[i] - 'a';
    if (0 == trie[p][ch]) {
      break;
    }
    p = trie[p][ch];
    prefix_cnt += cnt[p];
  }
  return prefix_cnt;
}

int main() {
  int n, m;
  scanf("%d %d", &n, &m);
  Init();
  for (int i = 0; i < n; ++i) {
    memset(s, 0, sizeof(s));
    scanf("%s", s);
    int len = strlen(s);
    Insert(s, len);
  }
  for (int j = 0; j < m; ++j) {
    memset(s, 0, sizeof(s));
    scanf("%s", s);
    int len = strlen(s);
    printf("%d\n", Search(s, len));
  }
  return 0;
}
