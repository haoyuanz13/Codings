#include "TreeNode.h"

#include <stdio.h>
#include <vector>
#include <stack>
#include <queue>

using namespace std;


// leetcode 199: follow up problem of level traverse
// for each level, start from the right child
vector<int> rightSideView(TreeNode* root) {
  vector<int> res;
  if (!root)
    return res;

  queue<TreeNode*> que;
  que.push(root);
  res.push_back(root->val);

  int pre = 1;  // count the number of nodes in current layer
  bool canVis = true;  // represent whether the node can be seen from right side

  while (!que.empty()) {
    TreeNode* cur = que.front();
    que.pop();
    pre --;

    // check the right child first
    if (cur->right) {
      if (canVis) {
        res.push_back(cur->right->val);
        canVis = false;
      }
      que.push(cur->right);
    }

    // then check the left child
    if (cur->left) {
      if (canVis) {
        res.push_back(cur->left->val);
        canVis = false;
      }
      que.push(cur->left);
    }

    // the current layer nodes have been traversed
    if (pre == 0) {
      // store the number of nodes in next layer
      pre = que.size();
      canVis = true;
    }
  }

  return res;
}