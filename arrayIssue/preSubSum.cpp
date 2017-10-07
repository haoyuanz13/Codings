#include <array>
#include <vector>
#include <iostream>
#include <unordered_map>
#include <algorithm>

using namespace std;
typedef vector<vector<int>> matrix;
// prefix sum problem
// Within array, find a subarray with sum 0
// use unorder map as hash map to store prefix sum and its index
vector<int> subarrayZero(vector<int> nums) {
  unordered_map<int, int> hash;
  hash[0] = -1;  // special case at index 0

  int len = nums.size();
  int presum = 0;

  vector<int> res;
  for (int i = 0; i < len; i ++) {
    presum += nums[i];

    // find valid subarray
    if (hash.count(presum) > 0) {
      int ind1 = hash[presum] + 1;
      int ind2 = i;

      res.assign(nums.begin() + ind1, nums.begin() + ind2 + 1);
      break;
    }

    hash[presum] = i;
  }
  return res; 
}

// print matrix
void printM(matrix& m, int row, int col) {
  for (int i = 0; i < row; i ++) {
    for (int j = 0; j < col; j ++) {
      cout << m[i][j] << ", ";
    }
    cout << '\n';
  }
}
// submatrix sum equals to zero
matrix submatrixZero(matrix& m) {
  // result matrix to store two point index
  matrix res (2, vector<int>(2, 0));

  if (m.empty() || m[0].empty())
    return res;

  int row = m.size(), col = m[0].size();

  int sum_mat [row + 1][col + 1] = {};


  for (int r = 1; r <= row; r ++)
    for (int c = 1; c <= col; c ++) 
      sum_mat[r][c] = m[r - 1][c - 1] + sum_mat[r - 1][c] + sum_mat[r][c - 1] - sum_mat[r - 1][c - 1];


  // select two rows to find region sum
  for (int r1 = 0; r1 < row; r1 ++) {
    for (int r2 = r1 + 1; r2 <= row; r2 ++) {
      // key: region sum, value: colum index
      unordered_map<int, int> hash;

      for (int ind_c = 0; ind_c <= col; ind_c ++) {
        int diff = sum_mat[r2][ind_c] - sum_mat[r1][ind_c];

        if (hash.count(diff) > 0) {
          int ind_c_pre = hash[diff];
          res[0][0] = r1;
          res[0][1] = ind_c_pre;
          res[1][0] = r2 - 1;
          res[1][1] = ind_c - 1;

          return res;
        }

        hash[diff] = ind_c;
      }

    }
  }

  return res;
}

int main(int argc, char** argv) {
  // vector<int> nums {3, 1, 2, -1, 2, -4, 2};
  // vector<int> res = subarrayZero(nums);

  matrix m {{1, 2, -4, -1}, 
            {2, -1, 3, 1}, 
            {4, 1, 2, 1}, 
            {1, 1, 0, 1}};

  matrix res = submatrixZero(m);

  for (int i = 0; i < 2; i ++)
    cout << res[i][0] << ", " << res[i][1] << endl;

  return 0;
}