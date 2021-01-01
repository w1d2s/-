#include <stdio.h>
#include <algorithm>
#include <vector>
#include <cmath>

/* 关键：
 * 1. 排序，并且建立原来位置与排序后链表中位置的关系（B数组保存指针直接访问排序后的节点，及其前驱和后继）
 * 2. 倒序处理B数组，先处理Bn，此时Bn的前驱、后继的idx均小于n；然后删掉Bn指向的链表节点，继续处理Bn-1....
 */

#define MAX_N 100005
#define INT_MIN -2147483648
#define INT_MAX 2147483647

struct PairNode {
  PairNode(): val(INT_MAX) {}
  PairNode(const int _v, const int _idx):
    val(_v), idx(_idx) {} 
  int val, idx;
  bool operator<(const PairNode& rhs) const {
    return val > rhs.val;
  }
};

struct ListNode {
  ListNode(): prev(nullptr), next(nullptr) {}
  explicit ListNode(const PairNode _v):
    val(_v), prev(nullptr), next(nullptr) {}
  PairNode val;
  ListNode *prev, *next;
};

ListNode* Insert(ListNode* ptr, const PairNode _v) {
  ListNode* q = new ListNode(_v);
  q->next = ptr->next;
  ptr->next = q;
  q->prev = ptr;
  if (q->next) {
    q->next->prev = q;
  }
  return q;
}

void Delete(ListNode* ptr) {
  if (!ptr) return;
  if (ptr->prev) {
    ptr->prev->next = ptr->next;
  }
  if (ptr->next) {
    ptr->next->prev = ptr->prev;
  }
  delete ptr;
}

void Destruct(ListNode* head) {
  while (head->next) {
    Delete(head->next);
  }
  delete(head);
}

int main() {
  int n;
  std::vector<PairNode> A;
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    int tmp;
    scanf("%d", &tmp);
    A.emplace_back(tmp, i);
  }
  std::sort(A.begin(), A.end());
  std::vector<ListNode*> B(n, nullptr);
  ListNode *head = new ListNode();
  ListNode *prev = head;
  for (int i = 0; i < n; ++i) {
    ListNode* p = Insert(prev, A[i]);
    B[A[i].idx] = p;
  }

  std::vector<PairNode> result;
  for (int i = n - 1; i > 0; --i) {
    int diff = INT_MAX;
    int pos = 0;
    ListNode *cur = B[i];
    if (cur->prev) {
      int tmp = std::abs(cur->prev->val.val - cur->val.val);
      if (tmp < diff) {
        diff = tmp;
        pos = cur->prev->val.idx;
      }
    }
    if (cur->next) {
      int tmp = std::abs(cur->next->val.val - cur->val.val);
      if (tmp < diff) {
        diff = tmp;
        pos = cur->next->val.idx;
      }
    }
    result.emplace_back(diff, pos);
    Delete(cur);
  }
  for (int i = result.size() - 1; i >= 0; --i) {
    printf("%d %d\n", result[i].val, result[i].idx + 1);
  }
  Destruct(head);
  return 0;
}
