#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;


// Leetcode 221: max square in matrix 
// check three neighbors legnth, due to the properties of square, need to select min one
int maximalSquare(vector<vector<char>>& matrix) {
  if (matrix.empty() || matrix[0].empty())
    return 0;
  int row = matrix.size(), col = matrix[0].size();
  vector<vector<int>> dp (2, vector<int>(col + 1, 0));

  int res = 0;
  for (int r = 1; r <= row; r ++) {
    for (int c = 1; c <= col; c ++) {
      if (matrix[r - 1][c - 1] == '0')
        dp[r % 2][c] = 0;
      else {
        int m = min(dp[(r - 1) % 2][c], dp[r % 2][c - 1]);
        m = min(m, dp[(r - 1) % 2][c - 1]);
        dp[r % 2][c] = m + 1;

        res = (m + 1 > res)? m + 1 : res;
      }
    }
  }

  return res * res;
}


// Leetcode 85: max rectangle 
int maximalRectangle(vector<vector<char>>& matrix) {
  if (matrix.empty() || matrix[0].empty())
    return 0;
  int row = matrix.size(), col = matrix[0].size();

  vector<int> left(col, 0);
  vector<int> right(col, col);
  vector<int> height(col, 0);

  int res = 0;

  for (int i = 0; i < row; i ++) {
    int curl = 0, curr = col;

    // check left edge and height
    for (int j = 0; j < col; j ++) {
      if (matrix[i][j] == '1') {
        height[j] += 1;
        left[j] = max(left[j], curl);
      } else {
        height[j] = 0;
        left[j] = 0;
        curl = j + 1;
      }
    }

    // check right edge 
    for (int j = col - 1; j >= 0; j --) {
      if (matrix[i][j] == '1')
        right[j] = min(right[j], curr);
      else {
        right[j] = col;
        curr = j;
      }
    }

    // get the max area of current row
    for (int j = 0; j < col; j ++)
      res = max(res, (right[j] - left[j]) * height[j]);
  }

  return res;
}