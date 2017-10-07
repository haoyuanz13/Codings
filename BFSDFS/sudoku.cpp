#include <vector>
#include <iostream>
#include <set>

using namespace std;


bool isValidSudoku(vector<vector<char>>& board) {
  int row = board.size(), col = board[0].size();

  for (int i = 0; i < row; i ++) {
    set<char> dim_row;
    set<char> dim_col;
    set<char> dim_cube;

    for (int j = 0; j < col; j ++) {
      // row check
      if (board[i][j] != '.' && dim_row.count(board[i][j]) > 0)
        return false;
      dim_row.insert(board[i][j]);
      
      // col check
      if (board[j][i] != '.' && dim_col.count(board[j][i]) > 0)
        return false;
      dim_col.insert(board[j][i]);

      // cube check
      int cubeR = 3 * (i / 3), cubeC = 3 * (i % 3);
      int curi = cubeR + j / 3, curj = cubeC + j % 3;

      if (board[curi][curj] != '.' && dim_cube.count(board[curi][curj]) > 0)
        return false;
      dim_cube.insert(board[curi][curj]);
    }

  }
  return true;
    
}
// check
bool isValid(vector<vector<char>> board, int r, int c, char cur) {
  for (int ind = 0; ind < 9; ind ++) {
    if (board[ind][c] != '.' && board[ind][c] == cur)
      return false;
    if (board[r][ind] != '.' && board[r][ind] == cur)
      return false;

    int indr = 3 * (r / 3) + ind / 3;
    int indc = 3 * (c / 3) + ind % 3;
    if (board[indr][indc] != '.' && board[indr][indc] == cur)
      return false;
  }
  return true;
}


bool solve(vector<vector<char>>& board, int row, int col) {
  for (int r = 0; r < row; r ++) {
    for (int c = 0; c < col; c ++) {
      if (board[r][c] != '.')
        continue;

      for (char t = '1'; t <= '9'; t ++) {
        if (isValid(board, r, c, t)) {
          board[r][c] = t;
          if (solve(board, row, col))
            return true;
          else
            board[r][c] = '.';  // recover
        }
      }  // end for 
      return false;

    }  // end inner for
  }  // end outer for
  return true;
}

void solveSudoku(vector<vector<char>>& board) {
  if (board.empty() || board[0].empty())
    return;
  int row = board.size(), col = board[0].size();
  solve(board, row, col);
  return;
}

int main() {

}