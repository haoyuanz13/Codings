#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

typedef vector<vector<int>> matrix;


// increase subsequence in array, no need to be continuous (DP)
int longestLength(vector<int> nums) {
  if (nums.empty() || nums.size() < 1)
    return 0;
  if (nums.size() == 1)
    return 1;

  int len = nums.size();
  vector<int> dp (len, 1);

  int max_len = 1;

  for (int i = 0; i < len; i ++) {
    int cur = nums[i];
    // traverse all previous longest length
    for (int j = 0; j < i; j ++) {
      if (cur > nums[j] && dp[i] < dp[j] + 1) {
        dp[i] = dp[j] + 1;
        max_len = (max_len < dp[i])? dp[i] : max_len;
      }
    }
  }
  return max_len;
}


int main(int agrc, char** argv) {
  vector<int> nums {10, 9, 2, 5, 3, 7, 101, 18};
  cout << longestLength(nums) << endl;

  return 0;
}