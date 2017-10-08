/* 
  hourse robber problem, total three cases
  1. line 
  2. circle
  3. tree
*/

#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;


// house locates in a line order
int rob_line(vector<int>& nums) {
  if (nums.empty() || nums.size() == 0)
    return 0;

  // rolling vector, 2 is enough
  int rob_val[2] = {};
  rob_val[1] = nums[0];
  for (int i = 2; i <= nums.size(); i ++) {
    int val1 = nums[i - 1] + rob_val[(i - 2) % 2];
    int val2 = rob_val[(i - 1) % 2];

    rob_val[i % 2] = (val1 > val2)? val1 : val2;
  }

  return rob_val[nums.size() % 2];

}

// house locates in a circle
int rob_circle(vector<int>& nums) {
  if (nums.empty() || nums.size() == 0)
    return 0;
  if (nums.size() == 1)
    return nums[0];

  // rolling vector, 2 is enough
  int rob_val[2] = {};
  int len = nums.size();

  // no steal on the first house
  rob_val[1] = nums[1];
  for (int i = 2; i < len; i ++) {
    int val1 = nums[i] + rob_val[(i - 2) % 2];
    int val2 = rob_val[(i - 1) % 2];

    rob_val[i % 2] = (val1 > val2)? val1 : val2;
  }

  int max1 = rob_val[(len - 1) % 2];

  // steal on the first house
  rob_val[0] = nums[0];
  rob_val[1] = nums[0];
  for (int i = 2; i < len; i ++) {
    int val1 = nums[i] + rob_val[(i - 2) % 2];
    int val2 = rob_val[(i - 1) % 2];

    rob_val[i % 2] = (val1 > val2)? val1 : val2;
  }

  int max2 = rob_val[(len - 2) % 2];  // the tail one cannot be stolen

  return (max1 > max2)? max1 : max2;
}


struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
 
int find(TreeNode* root, bool canStealRoot) {
  if (root == nullptr)
    return 0;

  if (canStealRoot) {
    int p1 = root->val + find(root->left, false) + find(root->right, false);
    int p2 = max(find(root->left, true), find(root->left, false)) + max(find(root->right, true), find(root->right, false));

    return max(p1, p2);
  } else {
    return max(find(root->left, true), find(root->left, false)) + max(find(root->right, true), find(root->right, false));
  }
}

// tree strcuture
int rob(TreeNode* root) {
  if (root == nullptr)
    return 0;
  return find(root, true);
    
}

