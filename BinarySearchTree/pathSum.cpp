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


// tree path sum
int main() {

}