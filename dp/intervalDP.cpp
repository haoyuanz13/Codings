#include <vector>
#include <iostream>
#include <string>
#include <limits>
#include <unordered_map>

using namespace std;

// Interval DP problem


// stone game
int stoneGame(vector<int> stones) {
  if (stones.empty() || stones.size() == 0)
    return 0;

  int len = stones.size();

  int sum[len][len] = {};
  int dp[len][len] = {};

  for (int i = 0; i < len; i ++) {
    dp[i][i] = 0;
    sum[i][i] = stones[i];
    for (int j = i; j < len; j ++)
      sum[i][j] = sum[i][j - 1] + stones[j];
  }

  // interval dp implementation
  for (int step = 2; step < len; step ++) {
    for (int i = 0, j = i + step; j < len; i ++, j ++) {
      int cur = numeric_limits<int>::max();

      for (int k = i; k < j; k ++)
        cur = (cur < (dp[i][k] + dp[k + 1][j]))? cur : (dp[i][k] + dp[k + 1][j]);

      dp[i][j] = cur + sum[i][j];
    }
  }
  return dp[0][len - 1];
}

// Burst problem (multiplication)
// Leetcode 312
int burst(vector<int> arr) {
  if (arr.empty() || arr.size() == 0)
    return 0;

  int len = arr.size();
  int bal[len + 2] = {};

  // top and tail labels
  bal[0] = 1;
  bal[len + 1] = 1;

  for (int i = 1; i <= len; i ++)
    bal[i] = arr[i - 1];

  int dp[len + 2][len + 2] = {};
  for (int i = 1; i <= len; i ++)
    dp[i][i] = bal[i - 1] * bal[i] * bal[i + 1];

  // interval dp implementation
  for (int step = 1; step <= len; step ++) {
    for (int i = i, j = i + step; j <= len; i ++, j ++) {
      int sides = bal[i - 1] * bal[j + 1];
      int cur = numeric_limits<int>::min();

      for (int k = i; k <= j; k ++) {
        int comp = dp[i][k - 1] + dp[k + 1][j] + sides * bal[k];
        cur = (cur > comp)? cur : comp;
      }
      dp[i][j] = cur;
    }
  }

  return dp[1][len];
}

// scramble strings: memorized search
// Leetcode 87
unordered_map<string, bool> hash;
bool isScramble(string s1, string s2) {
  if (s1.size() != s2.size())
    return false;

  string curKey = s1 + "#" + s2;
  if (hash.count(curKey) > 0)
    return hash[curKey];

  int len = s1.size();
  if (len == 1)
    return (s1.compare(s2) == 0);

  for (int k = 1; k < len; k ++) {
    bool sc1 = ( isScramble(s1.substr(0, k), s2.substr(0, k)) && isScramble(s1.substr(k), s2.substr(k)) );
    bool sc2 = ( isScramble(s1.substr(0, k), s2.substr(len - k)) && isScramble(s1.substr(k), s2.substr(0, len - k)) );

    if (sc1 || sc2) {
      hash[curKey] = true;
      return true;
    }
  }

  hash[curKey] = false;
  return false;
}


int main() {

}