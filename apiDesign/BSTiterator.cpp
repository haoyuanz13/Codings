#include <stack>
#include <vector>
#include <iostream>

using namespace std;
// Definition for binary tree
struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
 TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
 


// BST itertaor: use inorder to store the tree
class BSTIterator {
public:
  stack<TreeNode*> stk;

  BSTIterator(TreeNode *root) {
    while (!stk.empty())
      stk.pop();
    inorder(root);
  }

  /** @return whether we have a next smallest number */
  bool hasNext() {
    return !(stk.empty());

  }

  /** @return the next smallest number */
  int next() {
    TreeNode* cur = stk.top();
    stk.pop();

    int res = cur->val;
    inorder(cur->right);
    return res;
  }

  void inorder(TreeNode* root) {    
    while((root != nullptr) == 1) {
      stk.push(root);
      root = root->left;
    }
    return;
  }

};

/**
 * Your BSTIterator will be called like this:
 * BSTIterator i = BSTIterator(root);
 * while (i.hasNext()) cout << i.next();
 */

int main() {
  TreeNode* t = new TreeNode(1);
  BSTIterator i = BSTIterator(t);

  while (i.hasNext()) {
    cout << i.next();
  }
}