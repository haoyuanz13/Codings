#include <vector>
#include <iostream>
#include <string>
#include <queue>
#include <limits>
using namespace std;


// continuous sequence (include decrease and increase)
int longestSubsequence(vector<int> nums) {
  if (nums.empty() || nums.size() == 0)
    return 0;
  if (nums.size() == 1)
    return 1;

  int maxl = 1, len = nums.size();

  // ascending sequence
  vector<int> dp_increase(len, 1);
  for (int i = 1; i < len; i ++) {
    if (nums[i] > nums[i - 1])
      dp_increase[i] = dp_increase[i - 1] + 1;

    maxl = (maxl > dp_increase[i])? maxl : dp_increase[i];
  }

  // descending sequence
  vector<int> dp_decrease(len, 1);
  for (int i = 1; i < len; i ++) {
    if (nums[i] < nums[i - 1])
      dp_decrease[i] = dp_decrease[i - 1] + 1;

    maxl = (maxl > dp_decrease[i])? maxl : dp_decrease[i];
  }

  return maxl;
}

// the sequence can be non-continuous one
int lengthOfLIS(vector<int>& nums) {
  if (nums.empty() || nums.size() < 2)
    return nums.size();
  int maxl = 1, len = nums.size();

  vector<int> dp(len, 1);
  for (int i = 0; i < len; i ++) {
    int pivot = nums[i];
    // traverse all previous states
    for (int j = 0; j < i; j ++) {
      if (pivot > nums[j] && dp[i] < dp[j] + 1)
        dp[i] = dp[j] + 1;
    }
    maxl = (maxl > dp[i])? maxl : dp[i];
  }

  return maxl;
}

struct point 
{
  int x;
  int y;

  point(int xx, int yy) {
    this->x = xx;
    this->y = yy;
  }

};

// longest increasing sequence in matrix
// graph theory
int longestIncreasingPath(vector<vector<int>>& matrix) {
  if (matrix.empty() || matrix[0].empty())
    return 0;

  int row = matrix.size(), col = matrix[0].size();
  int count = row * col, label = numeric_limits<int>::min();;
  int res = 0;

  queue<point*> leafNode;

  while(count) {

    for (int r = 0; r < row; r ++) {
      for (int c = 0; c < col; c ++) {
        if (matrix[r][c] == label)
          continue;

        // check whether this position is the local max
        bool up = (r == 0 || matrix[r][c] >= matrix[r - 1][c]);
        bool down = (r == row - 1 || matrix[r][c] >= matrix[r + 1][c]);
        bool left = (c == 0 || matrix[r][c] >= matrix[r][c - 1]);
        bool right = (c == col - 1 || matrix[r][c] >= matrix[r][c + 1]);

        if (up && down && left && right) {
          point* newone = new point(r, c);
          leafNode.push(newone);
        }

      }
    }

    while (!leafNode.empty()) {
      point* cur = leafNode.front();
      leafNode.pop();
      matrix[cur->x][cur->y] = label;
      count --;
    }

    res ++;  // increase the level
  }
  return res;
}

int main() {

}