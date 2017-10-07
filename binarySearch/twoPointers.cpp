#include <iostream>
#include <vector>
#include <array>
#include <unordered_map>
#include <algorithm>

using namespace std;

// print map
void printMap(unordered_map<int, int> map) {
  for (unordered_map<int, int>::iterator it = map.begin(); it != map.end(); ++it) {
    cout << it->first << " => " << it->second << "\n";
  }
}

// two sum problem for unordered array
array<int, 2> twoSum(array<int, 6>& nums, int target_sum) {
  unordered_map<int, int> hash;
  int ind1 = 0, ind2 = 0;
  int len = nums.size();

  for (int i = 0; i < len; i ++) {
    int comb = target_sum - nums[i];
    // cout << comb << endl;
    // cout << hash.count(comb) << endl;

    if (hash.empty() || !(hash.count(nums[i]) > 0) )
      hash[target_sum - nums[i]] = i;
    else {
      ind1 = hash[nums[i]];
      ind2 = i;
      break;
    }

  }

  array<int, 2> res {ind1, ind2};
  return res;
}

// two sum problem for sorted array: two pointers
vector<int> twoSumX(vector<int>& nums, int target_sum) {
  vector<int> res;
  if (nums.empty() || nums.size() == 0)
    return res;

  int l = 0, r = nums.size() - 1;
  while (l < r) {
    int cur_sum = nums[l] + nums[r];
    if (cur_sum == target_sum)
      break;
    else if (cur_sum < target_sum)
      l ++;
    else
      r --;
  }

  if (l != r){
    res.push_back(l);
    res.push_back(r);
  }
  return res;
}

// dfs function
void dfs_find(vector<int>& nums, int len, int ind_start, int target_sum, int K, vector<int> cur, vector<vector<int>>& res) {
  if (target_sum < K * nums.front() || target_sum > K * nums.back())
    return;

  // two sum case
  if (K == 2) {
    int l = ind_start, r = len - 1;

    while (l < r) {
      int cur_sum = nums[l] + nums[r];

      if (cur_sum == target_sum) {
        cur.push_back(nums[l]);
        cur.push_back(nums[r]);

        vector<int> cur_copy(cur);
        res.push_back(cur_copy);

        cur.pop_back();
        cur.pop_back();

        l ++, r --;
        while (l < r && nums[l] == nums[l - 1])
          l ++;
        while (l < r && nums[r] == nums[r + 1])
          r --;
      }

      else if (cur_sum < target_sum)
        l ++;
      else
        r --;
    }

    return;
  }

  for (int i = ind_start; i <= len - K; i ++) {
    int ele = nums[i];
    if (i > ind_start && nums[i - 1] == ele)
      continue;

    cur.push_back(ele);
    dfs_find(nums, len, i + 1, target_sum - ele, K - 1, cur, res);
    cur.pop_back();
  }
  return;
}

// the general k sum problem, sort array first and converge to two sum case
// dfs to find all possible combinations
vector<vector<int>> Ksum(vector<int>& nums, int K, int target_sum) {
  vector<vector<int>> res;
  if (nums.empty() || K == 0)
    return res;

  sort (nums.begin(), nums.end());

  vector<int> cur;
  dfs_find(nums, nums.size(), 0, target_sum, K, cur, res);
  return res;
}


int main(int argv, char** argc) {
  // array<int, 6> nums {10, 3, 1, 5, 11, 2};
  // array<int, 2> res = twoSum(nums, 6);
  int a [] = {5, 10, 13, 12, 0, 15, 0, 20};
  vector<int> nums (a, a + sizeof(a) / sizeof(int));

  // vector<int> res = twoSumX(nums, 20);
  vector<vector<int>> res = Ksum(nums, 3, 25);

  if (res.empty())
    cout << "No pair found!" << endl;
  else {
    int total = res.size();
    for (int i = 0; i < total; i ++) {
      vector<int> cur = res[i];

      for (int j = 0; j < cur.size(); j ++) {
        cout << cur[j] << ',';
      }
      cout << '\n';
    }
  }

    // cout << res[0] << endl;
    // cout << res[1] << endl;

  return 0;
}