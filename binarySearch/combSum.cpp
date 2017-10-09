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

// leetcode 279
int numSquares(int n) {
  if (n <= 0)
    return 0;

  queue<int> que;
  int table[n + 1] = {};

  for (int i = 1; i * i <= n; i ++) {
    que.push(i * i);
    table[i * i] = 1;
  }

  if (table[n] == 1)
    return 1;

  int step = 1;
  while (!que.empty()) {
    step ++;
    int num_cur = que.size();

    for (int i = 1; i <= num_cur; i ++) {
      int cur = que.front();
      que.pop();

      for (int j = 1; j * j <= n; j ++) {
        int val = cur + j * j;
        if (val == n) return step;
        if (val > n) break;

        if (val < n && table[val] == 0) {
          que.push(val);
          table[val] = step;
        }  // end if
      }  // end inner for

    }  // end outer for
  }  // end while

  return 0;
}

int main(int argv, char**argc) {
  array<int, 3> num = {1, 2, 5};
  const int target = 11;

  int res = combMin(num, target);
  cout << res << endl;

  return 0;
}
