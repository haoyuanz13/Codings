#include <iostream>
#include <vector>
#include <string>

using namespace std;

typedef vector<int> row;
typedef vector<row> matrix_r;

// the standard binary search in vector
bool bsFindInRow(row& r, int target) {
  if (r.empty() || r.size() == 0)
    return false;

  int left = 0, right = r.size() - 1;
  int mid; 

  while (left < right) {
    mid = left + (right - left) / 2;
    if (r.at(mid) == target)
      return true;
    else if (r.at(mid) < target)
      left = mid + 1;
    else 
      right = mid - 1;
  }
  return r.at(left) == target;

}

// check whether element is in the sorted matrix or not
// the whole matrix is in order
bool searchAllSorted(matrix_r& m, int target) {
  // check whether the matrix is empty or not
  if (m.empty() || m[0].empty())
    return false;

  int row = m.size(), col = m[0].size();
  // check whether the target locates in the interval between [first, last]
  if (target < m[0][0] || target > m[row - 1][col - 1])
    return false;

  // search within the matrix using the last element of each row as pivot
  for (int r = 0; r < row; r ++) {
    int pivot = m[r][col - 1];

    if (target == pivot)
      return true;

    else if (target < pivot)
      return bsFindInRow(m[r], target);
  }

  return false; 
}

// the case that in matrix, each column is sorted and each row is sorted
bool searchRowColSorted(matrix_r& m, int target) {
  // check whether the matrix is empty or not
  if (m.empty() || m[0].empty())
    return false;
  if (m[0][0] == target)
    return true;

  int r = 0, c = m[0].size() - 1;

  while (c >= 0 && r < m.size()) {
    if (m[r][c] == target)
      return true;
    else if (m[r][c] > target)
      c --;
    else
      r ++;
  }

  return false; 
}

// count the order of certain element in a sorted matrix
int findOrder(matrix_r& m, int target) {
  int r = 0, c = m[0].size() - 1;
  int count = 0, pivot;

  while(r < m.size() && c >= 0) {
    pivot = m[r][c];
    if (pivot <= target) {
      r ++;
      count += c + 1;
    } 

    else 
      c --;
  }

  return count;
}


// use two pointers in the matrix for binary search
// find the kth smallest element in a sorted matrix
int findKthInMatrix(matrix_r& m, int K) {
  int row = m.size(), col = m[0].size();
  int l = m[0][0], r = m[row - 1][col - 1];
  int mid;

  while (l < r) {
    mid = (l + r) >> 1;
    int order_mid = findOrder(m, mid);

    cout << "The value " << mid << " has order " << order_mid << ". " << endl;

    if (order_mid < K)
      l = mid + 1;
    else
      r = mid;
  }
  return l;
}

int main(int argc, char** argv) {
  matrix_r mat;
  int layer = 3;

  // the first layer
  int row_1 [] = {1, 4, 7, 11, 15};
  row r1 (row_1, row_1 + sizeof(row_1) / sizeof(int) );
  mat.push_back(r1);

  // the first layer
  int row_2 [] = {2, 5, 8, 12, 19};
  row r2 (row_2, row_2 + sizeof(row_2) / sizeof(int) );
  mat.push_back(r2);

  // the first layer
  int row_3 [] = {3, 5, 9, 16, 22};
  row r3 (row_3, row_3 + sizeof(row_3) / sizeof(int) );
  mat.push_back(r3);

  // bool exist = searchRowColSorted(mat, 13);
  // string res = (exist)? "Find" : "Not find";
  // cout << res << endl;

  int num = findKthInMatrix(mat, 7);
  cout << num << endl;
  // for (int i = 0; i < layer; i ++) {
  //   vector<int> cur = mat.at(i);

  //   for (vector<int>::iterator it = cur.begin(); it != cur.end(); it ++) {
  //     cout << ' ' << *it;
  //   }
  //   cout << '\n';
  // }

  return 0;
}