// import from built in library
#include <vector>
#include <iostream>
#include <queue>
#include <algorithm>

// import from design class
#include "unionFind.h"

using namespace std;

// global variable to represent directions
int dir [4][4] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
typedef vector<vector<int>> matrix;
// island problem, basically three approaches
// BFS, DFS, Union Find

// print matrix
void printVis(bool vis[4][5]) {
  for (int i = 0; i < 4; i ++) {
    for (int j = 0; j < 5; j ++) {
      cout << vis[i][j] << ",";
    }
    cout << "\n";
  }

}

// BFS using queue
int islandBFS(matrix& grid) {
  if (grid.empty() || grid[0].empty())
    return 0;

  int row = grid.size(), col = grid[0].size();
  // bool vis [row][col] = {};

  vector<vector<int>> vis (row, vector<int>(col, 0));

  // fill(&vis[0][0], &vis[0][0] + sizeof(vis), false);

  // initVis(vis);
  // printVis(vis);

  // int dir [4][4] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

  int count = 0;

  for (int r = 0; r < row; r ++) {
    for (int c = 0; c < col; c ++) {
      if (grid[r][c] == 0 || vis[r][c])
        continue;

      queue<int> pos;
      pos.push(r), pos.push(c);
      vis[r][c] = true;

      // traverse all neighbors
      while (!pos.empty()) {
        int cur_r = pos.front();
        pos.pop();

        int cur_c = pos.front();
        pos.pop();

        for (int i = 0; i < 4; i ++) {
          int nei_r = cur_r + dir[i][0], nei_c = cur_c + dir[i][1];

          if (nei_r < 0 || nei_r >= row || nei_c < 0 || nei_c >= col)
            continue;

          if (grid[nei_r][nei_c] == 1 && !vis[nei_r][nei_c]) {
            pos.push(nei_r);
            pos.push(nei_c);
            vis[nei_r][nei_c] = true;
          }
        }
      }

      count ++;
    }
  }

  return count;
}


// DFS amd assign reeference to pass vis matrix 
void dfs(matrix& grid, int row, int col, int r, int c, vector<vector<bool>>& vis) {
  if (r < 0 || r >= row || c < 0 || c >= col)
    return;
  if (vis[r][c] || grid[r][c] == 0)
    return;

  vis[r][c] = true;

  for (int i = 0; i < 4; i ++) {
    for (int j = 0; j < 5; j ++) {
      cout << vis[i][j] << ",";
    }
    cout << "\n";
  }
  cout << "------------------------------------" << endl;


  for (int i = 0; i < 4; i ++) {
    int next_r = r + dir[i][0], next_c = c + dir[i][1];
    dfs(grid, row, col, next_r, next_c, vis);
  }

  return;
}

// DFS for island problem
int islandDFS(matrix& grid) {
  if (grid.empty() || grid[0].empty())
    return 0;

  int row = grid.size(), col = grid[0].size();
  // bool vis [row][col] = {};
  vector<vector<bool>> vis (row, vector<bool>(col, false));

  int count = 0;
  for (int r = 0; r < row; r ++) {
    for (int c = 0; c < col; c ++) {
      if (grid[r][c] == 0 || vis[r][c])
        continue;
      
      dfs(grid, row, col, r, c, vis);
      count ++;
    }
  }

  return count;
}

// union find structure 
int islandUF(matrix& grid) {
  if (grid.empty() || grid[0].empty())
    return 0;

  int row = grid.size(), col = grid[0].size();
  // create a new union find object
  unionFind uf(row * col);

  int num_island = 0;
  for (int r = 0; r < row; r ++)
    for (int c = 0; c < col; c ++)
      num_island += (grid[r][c] == 1)? 1 : 0;

  uf.set_count(num_island);

  // union elements
  for (int r = 0; r < row; r ++) {
    for (int c = 0; c < col; c ++) {
      if (grid[r][c] == 0)
        continue;

      // traverse all valid neighbors 
      for (int i = 0; i < 4; i ++) {
        int next_r = r + dir[i][0], next_c = c + dir[i][1];

        if (next_r < 0 || next_r >= row || next_c < 0 || next_c >= col)
          continue;
        if (grid[next_r][next_c] == 0)
          continue;

        // connect its valid neighbors and reduce island number
        uf.unions(r * col + c, next_r * col + next_c);
      }

    }
  }
  return uf.query(); 
}


int main(int argc, char**argv) {
  matrix m {{1, 1, 0, 0, 0}, 
            {1, 1, 0, 0, 0}, 
            {0, 1 ,1, 1, 0}, 
            {0, 0, 0, 1, 1}};

  cout << islandUF(m) << endl;
}

