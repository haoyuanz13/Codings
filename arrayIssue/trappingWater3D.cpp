#include <vector>
#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;

// Leetcode 407: trapping rain water (3D)
// Tips: create a new structure and use the priority queue

// designed structure to represent wall in 3D environment
struct cell
{
  int x, y, height;
  
  cell(int pos_x, int pos_y, int h){
    x = pos_x;
    y = pos_y;
    height = h;
  }
};

// designed comparator
struct cellComp
{
  bool ascending;
  cellComp(const bool order = false) {
    ascending = order;
  }

  // operator
  bool operator()(const cell* a, const cell* b) const {
    if (ascending)
      return (a->height) > (b->height);
    else
      return (a->height) < (b->height);
  }
};


// main algorithm
int trapRainWater(vector<vector<int>>& heightMap) {
  // corner case
  if (heightMap.empty() || heightMap[0].empty())
    return 0;  
  
  // define neighbor traversing operation
  vector<int> dx {1, -1, 0, 0};
  vector<int> dy {0, 0, 1, -1};

  // define priority queue (ascending in terms of cell height)
  priority_queue<cell, vector<cell*>, cellComp> cell_vec(true);
  
  // define a map to label the traversed state 
  int row = heightMap.size(), col = heightMap.front().size();
  vector<vector<bool>> vis (row, vector<bool>(col, false));

  // handle boundaries first
  for (int r = 0; r < row; r ++) {
    cell* cell_left = new cell(r, 0, heightMap[r][0]);
    cell_vec.push(cell_left);
    vis[r][0] = true;  // label true as visited

    cell* cell_right = new cell(r, col - 1, heightMap[r][col - 1]);
    cell_vec.push(cell_right);
    vis[r][col - 1] = true;  // label true as visited
  }
  
  for (int c = 1; c < col - 1; c ++) {    // avoid repeated traversing
    cell* cell_up = new cell(0, c, heightMap[0][c]);
    cell_vec.push(cell_up);
    vis[0][c] = true;  // label true as visited

    cell* cell_bot = new cell(row - 1, c, heightMap[row - 1][c]);
    cell_vec.push(cell_bot);
    vis[row - 1][c] = true;  // label true as visited
  }

  // find lowest cell and count its water capacity, finally converge
  int storage = 0;
  while (!cell_vec.empty()) {
    cell* cur = cell_vec.top();
    cell_vec.pop();

    // traverse all valid neighbors
    for (int i = 0; i < 4; i ++) {
      int nei_x = cur->x + dx[i];
      int nei_y = cur->y + dy[i];
      
      // outside map 
      if (nei_x < 0 || nei_x >= row || nei_y < 0 || nei_y >= col)
        continue;
      // has been visited
      if (vis[nei_x][nei_y])
        continue;
      
      // valid neighbor case
      int pivot_height = (cur->height > heightMap[nei_x][nei_y])? cur->height : heightMap[nei_x][nei_y];

      cell* cell_nei = new cell(nei_x, nei_y, pivot_height);
      cell_vec.push(cell_nei);
      vis[nei_x][nei_y] = true;
      
      int water = (0 < cur->height - heightMap[nei_x][nei_y])? cur->height - heightMap[nei_x][nei_y] : 0;
      storage += water;
    }
  }

  return storage;
  
}
 




