#include "TreeNode.h"

#include <stdio.h>
#include <vector>
#include <stack>
#include <queue>

using namespace std;


// in order traverse
vector<int> inorderTraversal(TreeNode* root) {
  vector<int> res;
  TreeNode *cur = root;
  stack<TreeNode*> stk;

  while (!stk.empty() || cur) {
    while (cur) {
      stk.push(cur);
      cur = cur->left;
    }

    cur = stk.top();
    stk.pop();

    res.push_back(cur->val);

    cur = cur->right;
  }

  return res;
}

// post order traverse
vector<int> postorderTraversal(TreeNode* root) {
  vector<int> res;
  if (!root)
    return res;

  TreeNode *cur = root;
  TreeNode *lastVis = root;

  stack<TreeNode*> stk;

  while (!stk.empty() || cur) {
    while (cur) {
      stk.push(cur);
      cur = cur->left;
    }

    cur = stk.top();
    if (cur->right && cur->right != lastVis)
      cur = cur->right;
    else {
      res.push_back(cur->val);
      lastVis = stk.top();
      stk.pop();
      cur = NULL;
    }
  }
  return res;
}

// level order
vector<vector<int>> levelOrder(TreeNode* root) {
  vector<vector<int>> res;
  if (!root)
    return res;

  queue<TreeNode*> que;
  vector<int> cur_layer;

  int num_layer = 1;
  que.push(root);

  cur_layer.push_back(root->val);
  res.push_back(cur_layer);
  cur_layer.clear();

  while (!que.empty()) {
    TreeNode *te = que.front();
    que.pop();
    num_layer --;

    if (te->left) {
      que.push(te->left);
      cur_layer.push_back(te->left->val);
    }

    if (te->right) {
      que.push(te->right);
      cur_layer.push_back(te->right->val);
    }

    if (num_layer == 0) {
      if (cur_layer.empty())
        return res;

      res.push_back(cur_layer);
      num_layer = cur_layer.size();
      cur_layer.clear();
    }
  }

  return res;
}

