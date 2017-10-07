#ifndef _LISTNODE_H
#define _LISTNODE_H

#include <stdio.h>

class ListNode {
public:
  int val;
  ListNode *next;
  ListNode(int x) : val(x), next(NULL) {}
};

#endif  // _LISTNODE_H 