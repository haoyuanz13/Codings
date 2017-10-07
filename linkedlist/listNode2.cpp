#include <vector>
#include <iostream>
#include <queue>

#include "ListNode.h"

using namespace std;

struct mycomp
{
  bool ascending;
  mycomp(const bool &asc = false) {
    ascending = asc;
  }

  bool operator() (const ListNode *a, const ListNode *b) {
    if (ascending)
      return (a->val) > (b->val);
    else
      return (a->val) < (b->val);
  }
};

// merge K linkednode lists
ListNode *mergeKLists(vector<ListNode*>& lists) {
  if (lists.empty())
    return nullptr;

  priority_queue<ListNode, vector<ListNode*>, mycomp> que(true);

  for (int i = 0; i < lists.size(); i ++) {
    ListNode *cur = lists[i];
    if (cur)
      que.push(cur);
  }

  ListNode *res = new ListNode(0);
  ListNode *cur = res;

  while (!que.empty()) {
    cur->next = que.top();
    que.pop();
    cur = cur->next;

    if (cur->next)
      que.push(cur->next);
  }

  return res->next;
}


// add two linkedlist
ListNode *addTwo(ListNode *l1, ListNode *l2) {
  if (!l1)
    return l2;
  if (!l2)
    return l2;

  ListNode *res = new ListNode(0);
  ListNode *pre = res;

  int carry = 0;
  while (l1 || l2 || carry != 0) {
    ListNode *cur = new ListNode(0);
    carry = ((l1)? l1->val : 0) + ((l2)? l2->val : 0) + carry;

    cur->val = carry % 10;
    carry /= 10;

    pre->next = cur;
    pre = cur;

    l1 = (l1)? l1->next : l1;
    l2 = (l2)? l2->next : l2;
  }

  return res->next;
}

// 
void reorderList(ListNode* head) {
  if (!head || !head->next || !head->next->next)
    return;

  ListNode *slow = head;
  ListNode *fast = head;

  // locate the middle of list
  while (fast->next && fast->next->next) {
    fast = fast->next->next;
    slow = slow->next;
  }

  // reverse the second half of list
  ListNode *mid = slow->next;
  ListNode *right = mid->next;
  while (right) {
    mid->next = right->next;
    right->next = slow->next;
    slow->next = right;
    right = mid->next;
  }

  // insert
  ListNode *s1 = head;
  ListNode *s2 = slow->next;
  while (s1 != slow) {
    slow->next = s2->next;
    s2->next = s1->next;
    s1->next = s2;

    s1 = s2->next;
    s2 = slow->next;
  }
  return;
}

int main() {
  Lis

}