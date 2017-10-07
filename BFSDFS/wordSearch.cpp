#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;
struct treeNode 
{
  treeNode* next[26];
  string word;
  bool vis;

  treeNode() {
    fill_n(next, 26, nullptr);
    vis = false;
  }

};

treeNode* buildTree(vector<string> words) {
  treeNode* root = new treeNode();

  if (words.empty())
    return root;

  for (int i = 0; i < words.size(); i ++) {
    string cur = words[i];
    treeNode* temp = root;

    for (int j = 0; j < cur.size(); j ++) {
      char it = cur.at(j);
      if (!temp->next[it - 'a'])
        temp->next[it - 'a'] = new treeNode();
      temp = temp->next[it - 'a'];
    }

    temp->word = cur;
  }

  return root;
}

void dfs(int r, int c, vector<vector<char>>& board, treeNode* root, vector<string>& res) {
  char cur = board[r][c];

  if (cur == '#' || !root->next[cur - 'a'])
    return;

  root = root->next[cur - 'a'];
  if (!root->vis && !root->word.empty()) {
    res.push_back(root->word);
    root->vis = true;
  }

  // vis label
  board[r][c] = '#';
  // search neighbors
  if (r > 0)
    dfs(r - 1, c, board, root, res);
  if (r < board.size() - 1)
    dfs(r + 1, c, board, root, res);
  if (c > 0)
    dfs(r, c - 1, board, root, res);
  if (c < board[0].size() - 1)
    dfs(r, c + 1, board, root, res);

  // clean up
  board[r][c] = cur;
}

vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
  vector<string> res;
  treeNode* root = buildTree(words);
  int row = board.size(), col = board[0].size();

  for (int r = 0; r < row; r ++) {
    for (int c = 0; c < col; c ++) {
      dfs(r, c, board, root, res);
    }
  }

  return res;    
}

bool find(int i, int j, int curlen, vector<vector<char>>& board, string word, vector<vector<bool>>& vis) {
  if (curlen == word.size())
    return true;

  vis[i][j] = true;
  bool x = false;

  int row = board.size(), col = board[0].size();
  // check the around neighbors
  if (i + 1 < row && !vis[i + 1][j] && board[i + 1][j] == word.at(curlen))
    x = x || find(i + 1, j, curlen + 1, board, word, vis);
  
  if (i - 1 >= 0 && !vis[i - 1][j] && board[i - 1][j] == word.at(curlen))
    x = x || find(i - 1, j, curlen + 1, board, word, vis);
  
  if (j + 1 < col && !vis[i][j + 1] && board[i][j + 1] == word.at(curlen))
    x = x || find(i, j + 1, curlen + 1, board, word, vis);
  
  if (j - 1 >= 0 && !vis[i][j - 1] && board[i][j - 1] == word.at(curlen))
    x = x || find(i, j - 1, curlen + 1, board, word, vis);

  // clean up
  vis[i][j] = false;
  return x;
}

bool exist(vector<vector<char>>& board, string word) {
  if (word.empty())
    return false;
  int row = board.size(), col = board[0].size();

  vector<vector<bool>> vis(row, vector<bool> (col, false));

  for (int i = 0; i < row; i ++) {
    for (int j = 0; j < col; j ++) {
      if (board[i][j] != word.at(0))
        continue;
      if (find(i, j, 1, board, word, vis))
        return true;
    }
  }

  return false;
}

int main() {

}