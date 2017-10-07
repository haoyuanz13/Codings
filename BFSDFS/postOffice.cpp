#include <vector>
#include <iostream>
#include <algorithm>
#include <limits>

using namespace std;

typedef vector<vector<int>> matrix;

// select a certain position that the sum of distance to all post offices is smallest
// use the special property of Manhattan distance
int getDis(vector<int> indset, vector<int>pre_sum, int pivot, int total) {
  if (total == 0)
    return 0;

  if (pivot < indset.front())
    return pre_sum[total] - total * pivot;

  if (pivot > indset.back())
    return total * pivot - pre_sum[total];

  // binary search to locate pivot position
  int l = 0, r = total - 1;
  int mid;
  while (l < r) {
    mid = l + (r - l) / 2;

    if (indset[mid] == pivot) {
      l = mid;
      break;
    }

    else if (indset[mid] < pivot)
      l = mid + 1;
    else
      r = mid - 1;

  }

  int num = 0;
  if (indset[l] <= pivot)
    num = l + 1;
  else
    num = l;

  int pre_cost = num * pivot - pre_sum[num];
  int suff_cost = pre_sum[total] - pre_sum[num] - (total - num) * pivot;

  return pre_cost + suff_cost;

}

int smallestDis(matrix& map) {
  if (map.empty() || map[0].empty())
    return -1;

  int row = map.size(), col = map[0].size();

  // build two vectors to store x and y indices of post office respectively
  vector<int> ind_x;
  vector<int> ind_y;

  for (int i = 0; i < row; i ++) {
    for (int j = 0; j < col; j ++) {
      if (map[i][j] == 1) {
        ind_x.push_back(i);
        ind_y.push_back(j);
      }
    }
  }

  // the special case that no post office in the map
  if (ind_x.empty() || ind_y.empty())
    return -1;

  // sort indices for faster computation
  sort (ind_x.begin(), ind_x.end());
  sort (ind_y.begin(), ind_y.end());

  // compute prefix sum of ind x and ind y
  int num_postOffice =  ind_x.size();
  vector<int> presum_x (num_postOffice + 1, 0);
  vector<int> presum_y (num_postOffice + 1, 0);

  for (int i = 1; i <= num_postOffice; i ++) {
    presum_x[i] = presum_x[i - 1] + ind_x[i - 1];
    presum_y[i] = presum_y[i - 1] + ind_y[i - 1];
  }

  // count the min manhattan distance to find the optimal one
  int min_dis = numeric_limits<int>::max();

  for (int r = 0; r < row; r ++) {
    for (int c = 0; c < col; c ++) {
      if (map[r][c] != 0)
        continue;
      // cout << "count" << endl;

      int dis_x = getDis(ind_x, presum_x, r, num_postOffice);
      int dis_y = getDis(ind_y, presum_y, c, num_postOffice);

      min_dis = (dis_x + dis_y < min_dis)? dis_x + dis_y : min_dis;
    }
  }

  return min_dis;
}

int main(int argc, char** argv) {
  matrix m {{0, 1, 0, 1}, 
            {0, 0, 1, 1}, 
            {1, 0, 0, 1}};

  cout << smallestDis(m) << endl;


}