#include <vector>
#include <iostream>
#include <queue>
#include <limits>

using namespace std;



// the following up problem of post office building
// still find a place to build office with the smallest distance sum
// but there exists wall in the grid
// idea: start from each house to empty spaces
int smallestDis(vector<vector<int>> grid) {
  if (grid.empty() || grid[0].empty())
    return -1;

  int row = grid.size(), col = grid[0].size();
  // store distance sum to all houses
  int dis [row][col] = {};
  // store the number of houses that each empty place can reach
  int numReachHouse [row][col] = {};

  int numHouse = 0;
  int dir[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

  for (int r = 0; r < row; r ++) {
    for (int c = 0; c < col; c ++) {
      // locate house place
      if (grid[r][c] != 1)
        continue;

      numHouse ++;
      // start from each house and count distance to each empty space
      int disFromHouse = 0;
      bool vis [row][col] = {};
      queue<int> que;
      que.push(r * col + c);
      vis[r][c] = true;

      cout << "current house locates at " << r << ", " << c << endl;
      while (!que.empty()) {
        // all empty spaces at the same layer should be assigned same distance
        int curLayerNum = que.size();
        for (int k = 0; k < curLayerNum; k ++) {
          int indr = que.front() / col;
          int indc = que.front() % col;
          que.pop();

          for (int id_d = 0; id_d < 4; id_d ++) {
            int nextr = indr + dir[id_d][0];
            int nextc = indc + dir[id_d][1];

            if (nextr < 0 || nextr >= row || nextc < 0 || nextc >= col)
              continue;
            if (vis[nextr][nextc] || grid[nextr][nextc] != 0)
              continue;

            cout << "The reached empty space is " << nextr << ", " << nextc << " with dis " << disFromHouse << "." << endl;  
            que.push(nextr * col + nextc);
            vis[nextr][nextc] = true;
            dis[nextr][nextc] += disFromHouse + 1;
            numReachHouse[nextr][nextc] += 1;
          }  // end inner for
        }  // end outer for

        for (int i = 0; i < row; i ++) {
          for (int j = 0; j < col; j ++) {
            cout << dis[i][j] << ' ';
          }
          cout << '\n';
        }
        cout << '\n';

        disFromHouse ++;
      }  // end while
    }
  }  // end for

  // traverse the empty space to find the smallest distance one
  int dis_min = numeric_limits<int>::max();
  for (int r = 0; r < row; r ++) {
    for (int c = 0; c < col; c ++) {
      if (grid[r][c] != 0)
        continue;
      if (numReachHouse[r][c] != numHouse)
        continue;

      dis_min = (dis_min > dis[r][c])? dis[r][c] : dis_min;
    }
  }

  return (dis_min == numeric_limits<int>::max())? -1 : dis_min;

}



int main() {
  vector<vector<int>> m {{0, 1, 0, 0, 0}, 
                         {1, 0, 0, 2, 1}, 
                         {0, 1, 0, 0, 0}};
  cout << smallestDis(m) << endl;
}