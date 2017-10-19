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

// longest consecutive sequence, the array is out of order
// leetcode 128
int longestConsecutive(vector<int>& nums) {
  if (nums.empty() || nums.size() < 2)
    return nums.size();

  // the key is element in the array, value is their consecutive length
  unordered_map<int, int> numMap;

  for (int i = 0; i < nums.size(); i ++)
    numMap[nums[i]] = 1;

  int maxlen = 0;

  for (int i = 0; i < nums.size(); i ++) {
    if (!(numMap.count(nums[i]) > 0))
      continue;

    int curlen = 1;
    int temp1 = nums[i] + 1;
    int temp2 = nums[i] - 1;

    // traverse larger value side
    while (numMap.count(temp1) > 0) {
      curlen += 1;
      numMap.erase(temp1);  // remove element to speed up searching

      temp1 ++;
    }

    while (numMap.count(temp2) > 0) {
      curlen += 1;
      numMap.erase(temp2);

      temp2 --;
    }

    // remove the center one
    numMap.erase(nums[i]);

    maxlen = (maxlen < curlen)? curlen : maxlen;
  }

  return maxlen;

}

int main(int agrc, char** argv) {
  vector<int> nums {100, 4, 200, 1, 3, 2};
  cout << longestConsecutive(nums) << endl;

  return 0;
}
