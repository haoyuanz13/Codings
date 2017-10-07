#include <vector>
#include <iostream>
#include <string>
#include <cstring>
#include <queue>

#include "TrieNode.h"
using namespace std;


// insert word string to initialize the trie tree
void insertwords(vector<string>& word, TrieNode *root, int idx) {
  if (word.empty() || word.size() == 0)
    return;
  if (idx >= word.size())
    return;

  TrieNode *temp = root;
  string cur = word[idx];
  for (int i = 0; i < cur.size(); i ++) {
    int ind = cur.at(i) - 'a';

    if (temp->child[ind] == nullptr)
      temp->child[ind] = new TrieNode();
    temp = temp->child[ind];
  }

  temp->isword = true;
  temp->idx = idx;

  return;
}


// build tree based on a vector of strings
TrieNode* buildTree(vector<string>& words) {
  TrieNode *root = new TrieNode();
  
  for (int i = 0; i < words.size(); i ++)
    insertwords(words, root, i);

  return root;
}

// check whether the string locates in the tree
bool find(string str_target, int level, TrieNode *root) {
  if (level == str_target.size())
    return root->isword;

  char cur = str_target.at(level);
  if (cur == '.') {
    for (int i = 0; i < 26; i ++) {
      if (root->child[i])
        if ( find(str_target, level + 1, root->child[i]) )
          return true;
    }
    return false;
  }

  else if (root->child[cur - 'a'])
    return find(str_target, level + 1, root->child[cur - 'a']);

  else
    return false;
}

// search word
bool search(string& str_target, TrieNode *root) {
  return find(str_target, 0, root);
}


int main() {
  vector<string> words {"zhang", "hao", "yuan"};
  TrieNode *root = buildTree(words);

  string test = "zha";
  cout << search(test, root) << endl;

  // insertwords(words, root, 0);
  // queue<TrieNode*> que;
  // que.push(root);

  // while (!que.empty()) {
  //   TrieNode *cur = que.front();
  //   que.pop();

  //   for (int i = 0; i < 26; i ++) {
  //     if (cur->child[i]) {
  //       cout << char('a' + i);
  //       que.push(cur->child[i]);
  //     } 
  //   }

  //   if (cur->isword)
  //     cout << cur->idx;

  //   cout << "\n";
  // }

}