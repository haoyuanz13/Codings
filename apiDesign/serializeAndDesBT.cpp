#include <string>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

// Definition for a binary tree node.
struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
 
class Codec {
public:

  // Encodes a tree to a single string.
  // level traverse
  string serialize(TreeNode* root) {
    if (root == nullptr)
      return "";
    queue<TreeNode*> que;
    que.push(root);

    string res = "";
    while (!que.empty()) {
      TreeNode* cur = que.front();
      que.pop();

      if (cur == nullptr)
        res += "n ";
      else {
        res += to_string(cur->val) + " ";
        que.push(cur->left);
        que.push(cur->right);
      }
    }
    return res;
  }

  // Decodes your encoded data to tree.
  TreeNode* deserialize(string data) {
    if (data.empty() || data.size() < 1)
      return nullptr;

    vector<string> arr = ownSplit(data);
    queue<TreeNode*> que;

    TreeNode* root = new TreeNode(stoi(arr.front()));
    que.push(root);

    for (int i = 1; i < arr.size(); i ++) {
      TreeNode* cur = que.front();
      que.pop();

      // check left child
      if (arr[i].compare("n") != 0) {
        TreeNode* left_kid = new TreeNode(stoi(arr[i]));
        cur->left = left_kid;
        que.push(left_kid);
      }

      // check right child
      i ++;
      if (arr[i].compare("n") != 0) {
        TreeNode* right_kid = new TreeNode(stoi(arr[i]));
        cur->right = right_kid;
        que.push(right_kid);
      }

    }
    return root;
      
  }

  // split string based on the white space
  vector<string> ownSplit(string str) {
    vector<string> res;

    for (int i = 0; i < str.size(); i ++) {
      if (str.at(i) == ' ')
        continue;

      string cur = "";
      while (i < str.size() && str.at(i) != ' ') {
        cur += str.at(i);
        i ++;
      }
      res.push_back(cur);
    }

    return res;
  }

};

// Your Codec object will be instantiated and called as such:
// Codec codec;
// codec.deserialize(codec.serialize(root));