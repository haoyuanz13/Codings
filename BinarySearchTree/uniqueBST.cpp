#include <vector>
#include "TreeNode.h"

#include <stdio.h>
#include <vector>
#include <stack>
#include <queue>

using namespace std;

vector<TreeNode*> gensub(int start, int end) {
  vector<TreeNode*> subres;

  if (start > end) {
    subres.push_back(nullptr);
    return subres;
  }

  for (int mid = start; mid <= end; mid ++) {
    vector<TreeNode*> sub_l = gensub(start, mid - 1);
    vector<TreeNode*> sub_r = gensub(mid + 1, end);

    for (int i = 0; i < sub_l.size(); i ++) {
      for (int j = 0; j < sub_r.size(); j ++) {
        TreeNode* l = sub_l[i];
        TreeNode* r = sub_r[j];

        TreeNode* cur = new TreeNode(mid);
        mid->left = l;
        mid->right = r;

        res.push_back(cur);
      }
    }
  }

  return res;
}


vector<TreeNode*> generateBST(int n) {
  if (n == 0) {
    vector<TreeNode*> res;
    return res;
  }

  return gensub(1, n);
}

