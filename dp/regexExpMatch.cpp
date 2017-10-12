#include <vector>
#include <string>
#include <iostream>

using namespace std;


// leetcode 10: regex matching
// '.' can match any single character
// '*' can match zero or more of the preceding characters
bool isMatch10(string s, string p) {
  if (p.empty())
    return s.empty();

  // state[i][j] represents the match state of s.at(i - 1) and p.at(j - 1)
  int row = s.size() + 1, col = p.size() + 1;
  vector<vector<bool>> state (row, vector<bool>(col, false));
  state[0][0] = true;

  for (int j = 1; j < col; j ++) {
    if (p.at(j - 1) == '*') {
      if (state[0][j - 1] || (j > 1 && state[0][j - 2]))
        state[0][j] = true;
    }
  }

  for (int i = 1; i < row; i ++) {
    for (int j = 1; j < col; j ++) {
      if (s.at(i - 1) == p.at(j - 1) || p.at(j - 1) == '.')
        state[i][j] = state[i - 1][j - 1];

      if (p.at(j - 1) == '*') {
        if (s.at(i - 1) != p.at(j - 2) && p.at(j - 2) != '.')
          state[i][j] = state[i][j - 2];
        else
          state[i][j] = (state[i - 1][j] || state[i][j - 1] || state[i][j - 2]);
      }
    }
  }

  return state[row - 1][col - 1];

}

// leetcode 44: similar as 10
bool isMatch(string s, string p) {
  if (p.empty())
    return s.empty();

  // state[i][j] represents the match state of s.at(i - 1) and p.at(j - 1)
  int row = s.size() + 1, col = p.size() + 1;
  vector<vector<bool>> state (row, vector<bool>(col, false));
  state[0][0] = true;

  // initialize
  for (int j = 1; j < col; j ++) {
    if (p.at(j - 1) == '*')
      state[0][j] = true;
    else
      break;
  }

  for (int i = 1; i < row; i ++) {
    for (int j = 1; j < col; j ++) {
      if (p.at(j - 1) != '*') {
        state[i][j] = state[i - 1][j - 1] && (s.at(i - 1) == p.at(j - 1) || p.at(j - 1) == '?');
      else
        state[i][j] = (state[i - 1][j] || state[i][j - 1]);
    }
  }

  return state[row - 1][col - 1];
}