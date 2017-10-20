#include <vector>
#include "TreeNode.h"

#include <stdio.h>
#include <vector>
#include <stack>
#include <queue>

using namespace std;


bool hasPathSum(TreeNode* root, int sum) {
  if (root == nullptr)
    return false;
  stack<TreeNode*> stk;
  stk.push(root);

  while (!stk.empty()) {
    TreeNode* cur = stk.top();
    stk.pop();

    if (cur->left == nullptr && cur->right == nullptr && cur->val == sum)
      return true;

    if (cur->left != nullptr) {
      cur->left->val = cur->val + cur->left->val;
      stk.push(cur->left);
    }

    if (cur->right != nullptr) {
      cur->right->val = cur->val + cur->right->val;
      stk.push(cur->right);
    }
  }

  return false;
}


void find(TreeNode* root, vector<int>& cur, vector<vector<int>>& res, int sum) {
  if (!root)
    return;

  vector<int> temp (cur);
  temp.push_back(root->val);
  // only when meet the leaf node can check sum
  if (root->left == nullptr && root->right == nullptr) {
    if (root->val == sum)
      res.push_back(temp);
    return;
  }

  find(root->left, temp, res, sum - root->val);
  find(root->right, temp, res, sum - root->val);

}

// path sum 2, leetcode 113: find all possible path sum
vector<vector<int>> pathSum2(TreeNode* root, int sum) {
  vector<vector<int>> res;
  if (!root)
    return res;

  vector<int> cur;
  find(root, cur, res, sum);

  return res;
}




// path sum 3, leetcode 437: no need to be an intact path
int count;

void feed(TreeNode* root, int sum) {
  if (!root)
    return;
  if (root->val == sum)
    count ++;

  feed(root->left, sum - root->val);
  feed(root->right, sum - root->val);
}

int pathSum(TreeNode* root, int sum) {
  count = 0;
  if (!root)
    return count;

  queue<TreeNode*> que;
  que.push(root);

  while (!que.empty()) {
    TreeNode* cur = que.front();
    que.pop();

    if (cur->left)
      que.push(cur->left);
    if (cur->right)
      que.push(cur->right);

    feed(cur, sum);
  }

  return count;
    
}

// tree path sum
int main() {

}
