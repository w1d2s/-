#include <stdio.h>
#include <iostream>
#include <string>
#include <unordered_map>

struct Node {
  int _group;
  int _person;
  Node* _next;

  Node(const int group, const int person, Node* next): 
    _group(group), _person(person), _next(next) {}
};

class GroupQueue {
public:
  GroupQueue() {
    _dummy_head = new Node(-1, -1, nullptr);
    _tail = _dummy_head;
  }
  ~GroupQueue() {
    while (_dummy_head->_next) {
      Node* tmp = _dummy_head->_next;
      _dummy_head->_next = tmp->_next;
      delete tmp;
    } 
    delete _dummy_head;
  }

  void Enqueue(const int group, const int person) {
    if (_group_tail.find(group) != _group_tail.end()) {
      Node* g_tail = _group_tail[group];
      g_tail = Insert(g_tail, group, person);
      _group_tail[group] = g_tail;
    } else {
      Node* g_tail = Insert(_tail, group, person);
      _group_tail[group] = g_tail; 
    }
  }

  int Dequeue() {
    if (_dummy_head->_next) {
      Node* head = _dummy_head->_next;
      _dummy_head->_next = head->_next;
      int person = head->_person;
      if (!(head->_next && head->_next->_group == head->_group)) {
        auto iter = _group_tail.find(head->_group);
        _group_tail.erase(iter);
      }
      delete head; 
      return person;
    }
    return -1;
  }

private:
  Node* Insert(Node* pos, const int group, const int person) {
    // pos should not be nullptr
    Node* tmp = pos->_next;
    pos->_next = new Node(group, person, tmp);
    if (pos == _tail) {
      _tail = pos->_next;
    }
    return pos->_next;
  }

  Node* _dummy_head;
  Node* _tail;
  std::unordered_map<int, Node*> _group_tail;
};

int main() {
  int t;
  int cases = 1;
  std::unordered_map<int, int> person2group;
  while (scanf("%d", &t) != EOF) {
    if (t == 0) {
      break;
    }
    for (int i = 0; i < t; ++i) {
      int n;
      scanf("%d", &n);
      for (int j = 0; j < n; ++j) {
        int person;
        scanf("%d", &person);
        person2group[person] = i;
      }
    }
    printf("Scenario #%d\n", cases);
    GroupQueue q;
    std::string cmd;
    while (std::cin >> cmd) {
      if (cmd[0] == 'E') {
        int p;
        scanf("%d", &p);
        q.Enqueue(person2group[p], p);
      } else if (cmd[0] == 'D') {
        int p = q.Dequeue();
        printf("%d\n", p);
      } else {
        printf("\n");
        break;
      }
    }
    ++cases;
  }
  return 0;
}
