#ifndef _TREENODE_H
#define _TREENODE_H

#include <stdio.h>

class TreeNode {
public:
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x): val(x), left(NULL), right(NULL) {}
};

#endif  // _TREENODE_H