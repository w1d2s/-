#include <stdio.h>
#include <cstring>
#include <vector>
#include <unordered_map>

const int MAX_LEN = 1000005;
const int MAX_N =   100005;
char s[MAX_LEN];

struct Trie {
  explicit Trie(const int capacity): idx_last_node(1) {
    _nodes.reserve(capacity);
    _nodes.emplace_back(26, 0);
  }

  ~Trie() = default;

  void Insert(const char* s, const int len) {
    int p = 1;
    for (int i = 0; i < len; ++i) {
      if (_nodes.size() - 1 < p) {
        _nodes.emplace_back(26, 0);
      }
      if (0 == _nodes[p][s[i] - 'a']) {
        _nodes.emplace_back(26, 0);
        _nodes[p][s[i] - 'a'] = _nodes.size() - 1;
      }
      p = _nodes[p][s[i] - 'a'];
    }
    if (_cnt.find(p) == _cnt.end()) {
      _cnt[p] = 1;
    } else {
      _cnt[p] += 1;
    }
  }

  int Search(const char* s, const int len) {
    int p = 1, prefix_cnt = 0;
    for (int i = 0; i < len; ++i) {
      if (_nodes.size() - 1 < p) {
        break;
      }
      p = _nodes[p][s[i] - 'a'];
      if (_cnt.find(p) != _cnt.end()) {
        prefix_cnt += _cnt[p];
      }
    }
    return prefix_cnt;
  }

  std::vector<std::vector<int>> _nodes;
  std::unordered_map<int, int> _cnt;
  int idx_last_node;
};

int main() {
  int n, m;
  scanf("%d %d", &n, &m);
  Trie trie(2 * n);
  for (int i = 0; i < n; ++i) {
    memset(s, 0, sizeof(s));
    scanf("%s", s);
    int len = strlen(s);
    trie.Insert(s, len);
  }
  for (int j = 0; j < m; ++j) {
    memset(s, 0, sizeof(s));
    scanf("%s", s);
    int len = strlen(s);
    printf("%d\n", trie.Search(s, len));
  }
  return 0;
}
