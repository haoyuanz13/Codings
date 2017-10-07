#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

// dfs for permutation
void dfs(vector<int> nums, vector<bool>& used, vector<int>& cur, vector<vector<int>>& res) {
  if (cur.size() == nums.size()) {
    vector<int> temp(cur);
    res.push_back(temp);
    return;
  }

  for (int i = 0; i < nums.size(); i ++) {
    if (used.at(i))
      continue;
    // handle duplications
    if (i > 0 && nums.at(i) == nums.at(i - 1) && !used[i - 1])
      continue;

    // add current element
    used.at(i) = true;
    cur.push_back(nums.at(i));

    dfs(nums, used, cur, res);

    // clean up
    cur.pop_back();
    used.at(i) = false;
  }

  return;

}

// permutation function
vector<vector<int>> permutation(vector<int>& nums) {
  vector<vector<int>> res;
  if (nums.empty() || nums.size() < 1)
    return res;

  int len = nums.size();
  vector<bool> used(len, false);

  // deal with duplications: sort first
  sort(nums.begin(), nums.end());

  vector<int> cur;
  dfs(nums, used, cur, res);

  return res;
}


// iteration for permutation problem, insertion element
vector<vector<int>> permutation_iteration(vector<int>& nums) {
  vector<vector<int>> res;
  
  if (nums.empty())
    return res;

  vector<int> first{nums.front()};
  res.push_back(first);

  for (int i = 1; i < nums.size(); i ++) {
    vector<vector<int>> newers;
    int ele_insert = nums.at(i);
    
    for (int ind_insert = 0; ind_insert <= i; ind_insert ++) {
      for (int k = 0; k < res.size(); k ++) {
        vector<int> temp(res.at(k));
        temp.insert(temp.begin() + ind_insert, ele_insert);
        newers.push_back(temp);
      }
    }

    res = newers;
  }

  return res;
}

int main(int argv, char** argc) {
  vector<int> nums {1, 1, 2};

  vector<vector<int>> res = permutation(nums);
  // vector<vector<int>> res = permutation_iteration(nums);

  for (int i = 0; i < res.size(); i ++) {
    vector<int> cur = res.at(i);
    for (int j = 0; j < cur.size(); j ++)
      cout << cur.at(j) << " ";

    cout << "\n";
  }
}