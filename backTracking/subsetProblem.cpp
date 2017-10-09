#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;


// dfs
void dfs(vector<int> nums, int len, int ind_start, vector<int>& cur, vector<vector<int>>& res) {
  res.push_back(cur);

  for (int i = ind_start; i < len; i ++) {
    cur.push_back(nums[i]);
    dfs(nums, len, i + 1, cur, res);
    cur.pop_back();
  }
  return;
}

// subset problems: no duplicates
vector<vector<int>> subsets_dfs(vector<int>& nums) {
  vector<vector<int>> res;
  if (nums.empty() || nums.size() < 1)
    return res;

  vector<int> temp;
  dfs(nums, nums.size(), 0, temp, res);
  return res;
}

// iterative method
vector<vector<int>> subsets_iter(vector<int>& nums) {
  vector<vector<int>> res;
  if (nums.empty() || nums.size() < 1)
    return res;

  vector<int> temp;
  res.push_back(temp);

  for (int i = 0; i < nums.size(); i ++) {
    int res_len = res.size();
    for (int j = 0; j < res_len; j ++) {
      vector<int> cur = res[j];

      cur.push_back(nums[i]);
      res.push_back(cur);
      cur.pop_back();
    }
  }

  return res;
}


/*
  subset problem that contains duplicates
*/

// dfs
void dfs_dul(vector<int> nums, int len, int ind_start, vector<int>& cur, vector<vector<int>>& res) {
  res.push_back(cur);

  for (int i = ind_start; i < len; i ++) {
    if (i > ind_start && nums[i] == nums[i - 1])
      continue;
    
    cur.push_back(nums[i]);
    dfs(nums, len, i + 1, cur, res);
    cur.pop_back();
  }
  return;
}

// subset problems: has duplicates, sort first
vector<vector<int>> subsets_dfs_dul(vector<int>& nums) {
  vector<vector<int>> res;
  if (nums.empty() || nums.size() < 1)
    return res;

  sort(nums);

  vector<int> temp;
  dfs_dul(nums, nums.size(), 0, temp, res);
  return res;
}


int main() {

}