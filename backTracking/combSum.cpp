#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;


// leetcode 40: no multiple used and array has duplicates
void dfs2(vector<int>& cands, int sum, int start, vector<int>& cur, vector<vector<int>>& res) {
  if (sum == 0) {
    res.push_back(cur);
    return;
  }

  for (int i = start; i < cands.size(); i ++) {
    int val = cands[i];
    if (sum < val)
      continue;
    if (i > start && val == cands[i - 1])
      continue;

    cur.push_back(val);
    dfs2(cands, sum - val, i + 1, cur, res);
    cur.pop_back();
  }
  return;
}

vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
  vector<vector<int>> res;
  if (candidates.empty() || candidates.size() < 1)
    return res;

  sort(candidates.begin(), candidates.end());
  vector<int> cur;
  dfs2(candidates, target, 0, cur, res);
  return res;

}

// leetcode 39: repeat usage and all positive elements
void dfs(vector<int>& cands, int sum, int start, vector<int>& cur, vector<vector<int>>& res) {
  if (sum == 0) {
    res.push_back(cur);
    return;
  }

  for (int i = start; i < cands.size(); i ++) {
    int val = cands[i];
    if (sum < val)
      continue;

    cur.push_back(val);
    dfs(cands, sum - val, i, cur, res);
    cur.pop_back();
  }
  return;
}

vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
  vector<vector<int>> res;
  if (candidates.empty() || candidates.size() < 1)
    return res;

  vector<int> cur;
  dfs(candidates, target, 0, cur, res);
  return res;
}

int main() {

}