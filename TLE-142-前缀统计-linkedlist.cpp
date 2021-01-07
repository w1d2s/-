#include <stdio.h>
#include <cstring>
#include <vector>

const int MAX_LEN = 1000005;
const int MAX_N =   100005;
char s[MAX_LEN];

struct Node {
  Node():
    _child(26, nullptr), _end_cnt(0) {} 
  ~Node() = default;

  std::vector<Node*> _child;
  int _end_cnt;
};

struct Trie {
  Trie() {
    _root = new Node();
  }
  ~Trie() {
    delete _root;
  }
  
  void Insert(const char* s, const int len) {
    Node* cur_ptr = _root;
    for (int i = 0; i < len; ++i) {
      if (nullptr == cur_ptr->_child[s[i] -'a']) {
        cur_ptr->_child[s[i] - 'a'] = new Node();
      }
      cur_ptr = cur_ptr->_child[s[i] - 'a'];
    }
    ++(cur_ptr->_end_cnt);
  }

  int Search(const char* s, const int len) {
    Node* cur_ptr = _root;
    int prefix_cnt = 0;
    for (int i = 0; i < len; ++i) {
      if (nullptr == cur_ptr->_child[s[i] - 'a']) {
        break;
      }
      cur_ptr = cur_ptr->_child[s[i] - 'a'];
      prefix_cnt += cur_ptr->_end_cnt;
    }
    return prefix_cnt;
  }

  Node* _root;
};

int main() {
  int n, m;
  scanf("%d %d", &n, &m);
  Trie trie;
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
