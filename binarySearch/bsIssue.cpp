#include <vector>
#include <iostream>

using namespace std;

typedef vector<vector<int>> matrix;


// converge in the matrix
vector<int> finding(int rs, int re, int cs, int ce, matrix& m, bool row_search) {
  // converge in row dimension
  if (row_search) {
    int rmid = rs + (re - rs) / 2;
    int cind = cs;
    // find the max within certain region
    for (int c = cs + 1; c <= ce; c ++) {
      if (m[rmid][c] > m[rmid][cind])
        cind = c;
    }

    // compare with two neighbors
    bool larger_top = (m[rmid][cind] > m[rmid - 1][cind]);
    bool larger_down = (m[rmid][cind] > m[rmid + 1][cind]);

    if (larger_top && larger_down) {
      vector<int> res {rmid, cind};
      return res;
    } else if (larger_top) {
      // search in the below region and in column dimension
      return finding(rmid + 1, re, cs, ce, m, false);
    } else {
      // search in the upper region and in column dimension
      return finding(rs, rmid - 1, cs, ce, m, false);
    }
  }

  // converge in column dimension
  else {
    int cmid = cs + (ce - cs) / 2;
    int rind = rs;
    // find the max within certain region
    for (int r = rs + 1; r <= re; r ++) {
      if (m[r][cmid] > m[rind][cmid])
        rind = r;
    }

    // compare with two neighbors
    bool larger_left = (m[rind][cmid] > m[rind][cmid - 1]);
    bool larger_right = (m[rind][cmid] > m[rind][cmid + 1]);

    if (larger_left && larger_right) {
      vector<int> res {rind, cmid};
      return res;
    } else if (larger_left) {
      // search in the right region and in column dimension
      return finding(rs, re, cmid + 1, ce, m, true);
    } else {
      // search in the left region and in column dimension
      return finding(rs, re, cs, cmid - 1, m, true);
    }
  } 

}
// find a peak element in matrix
// assume edge elements are small
vector<int> findPeak(matrix& m) {
  int row = m.size(), col = m[0].size();
  return finding(1, row - 2, 1, col - 2, m, true);
}

int main() {
  matrix m {{1, 2, 3, 6, 5}, 
            {16, 41, 23, 22, 6}, 
            {15, 17, 20, 21, 7}, 
            {14, 18, 19, 20, 10}, 
            {13, 14, 11, 10, 9}};

  vector<int> res = findPeak(m);

  for (int i = 0; i < res.size(); i ++)
    cout << res[0] << " ";
  cout << "\n";

}