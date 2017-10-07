#include <iostream>
#include <vector>
// design class 
#include "ListNode.h"
#include <stdio.h>

using namespace std;

// swap nodes in the linked list
ListNode *swapPairs(ListNode *head) {
  if (!head || !head->next)
    return head;

  ListNode *pre = new ListNode(0);
  pre->next = head;

  ListNode *left = head;
  ListNode *right = head->next;

  head = pre;

  while (right) {
    left->next = right ->next;
    right->next = pre->next;
    pre->next = right;

    pre = left;
    left = left->next;

    if (!left)
      break;

    right = left->next;
  }
  return head->next;

}
// find group nodes with k elements
ListNode *findk(ListNode *s, int k) {
  int i = 1;
  while (i < k && s) {
    s = s->next;
    i ++;
  }

  return s;
}

// reverse in K group
ListNode* reverseKGroup(ListNode* head, int k) {
  if (!head || !head->next || k == 0)
    return head;

  ListNode *pre = new ListNode(0);
  pre->next = head;

  ListNode *fast = head;
  head = pre;

  ListNode *left, *right;

  while (fast) {
    // crop nodes group 
    fast = findk(fast, k);
    if (!fast)
      break;

    fast = fast->next;
    left = pre->next;
    right = left->next;

    // reverse nodes within the group
    while (right != fast) {
      left->next = right->next;
      right->next = pre->next;
      pre->next = right;
      right = left->next;
    }

    pre = left;
  }

  return head->next;
}


int main(int argc, char** argv) {

}
