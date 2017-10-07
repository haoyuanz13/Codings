#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <limits>

using namespace std;

// given an array and target sum number, find the total combination 
// numbers to get the target sum

// BFS or DFS is pretty time cost since no limited of combination times
int numCombSum(array<int, 3> nums, int target) {
  vector<int> numComb(target + 1, 0);
  // fill (numComb.begin(), numComb.end(), 0);

  numComb[0] = 1;

  for (int subsum = 1; subsum <= target; subsum ++) {
    for (int ch : nums) {
      if (subsum - ch >= 0)
        numComb[subsum] += numComb[subsum - ch];
    }

  }
  return numComb[target];
}

// find the min combination times
int combMin(array<int, 3> nums, int target) {
  vector<int> dp(target + 1, -1);
  dp[0] = 0;

  for (int sub = 1; sub <= target; sub ++) {
    int cur = numeric_limits<int>::max();

    for (int ch : nums) {
      if (sub - ch >= 0) {
        if (dp[sub - ch] == -1)
          continue;

        cur = min(cur, dp[sub - ch] + 1);
      }
    }

    if (cur != numeric_limits<int>::max())
      dp[sub] = cur;

  }

  return dp[target];
}


int main(int argv, char**argc) {
  array<int, 3> num = {1, 2, 5};
  const int target = 11;

  int res = combMin(num, target);
  cout << res << endl;

  return 0;
}