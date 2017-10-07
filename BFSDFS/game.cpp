#include <vector>
#include <iostream>
#include <queue>
#include <unordered_map>

using namespace std;


void pascalTriangle(int k) {
  vector<vector<int>> pas;
  vector<int> init {1};
  pas.push_back(init);
  
  vector<int> pre = pas.front();
  
  for (int i = 1; i < k; i ++) {
    vector<int> cur {1};
    for (int c = 1; c < i; c ++) {
        cur.push_back(pre[c - 1] + pre[c]);
    }
    cur.push_back(1);
    
    pre = cur;
    pas.push_back(cur);
  }
  
  for (int i = 0; i < k; i ++) {
    for (int c = 0; c < pas[i].size(); c ++)
      cout << pas[i][c] << " ";
    cout << "\n";
  }
  return;
}


// check circle
vector<int> turnR(vector<int> dir) {
  int x = 1 * dir[1];
  int y = -1 * dir[0];
  vector<int> res {x, y};
  return res;
}

vector<int> turnL(vector<int> dir) {
  int x = -1 * dir[1];
  int y = 1 * dir[0];
  vector<int> res {x, y};
  return res;
}

vector <string> doesCircleExist(vector <string> commands) {
  vector<string> res;
  for (int i = 0; i < commands.size(); i ++) {
    string cmd_cur = commands[i];
    int len = cmd_cur.size();
    
    vector<int> dir {0, 1};
    int x = 0, y = 0;
    
    for (int j = 0; j < 4; j ++) {
      for (int k = 0; k < len; k ++) {
        char cc = cmd_cur.at(k);
        if (cc == 'G') {
          x += dir[0];
          y += dir[1];
        }
        else if (cc == 'R')
          dir = turnR(dir);
        else if (cc == 'L')
          dir = turnL(dir);                    
      }
    }
    
    if (x == 0 && y == 0)
      res.push_back("YES");
    else
      res.push_back("NO");        
  }
  return res;
}

// struct UndirectedGraphNode {
//   int label;
//   vector<UndirectedGraphNode*> neighbors;
//   UndirectedGraphNode(int x) : label(x) {};
// };

// UndirectedGraphNode *cloneGraph(UndirectedGraphNode *node) {
//   if(node == nullptr)
//     return node;

//   UndirectedGraphNode* newnode = new UndirectedGraphNode(node->label);
//   unordered_map<int, UndirectedGraphNode*> hash;
//   hash[node->label] = newnode;

//   // store original node list
//   queue<UndirectedGraphNode*> que;
//   que.push(node);

//   while (!que.empty()) {
//     UndirectedGraphNode* cur = que.front();
//     que.pop();

//     vector<UndirectedGraphNode*> cur_nei = cur->neighbors;
//     // traverse all neighbors
//     for (int i = 0; i < cur_nei.size(); i ++) {
//       UndirectedGraphNode* cur_node_nei = cur_nei[i];
//       if (hash.count(cur_node_nei->label) <= 0) {
//         // clone
//         UndirectedGraphNode* clone_nei = new UndirectedGraphNode(cur_node_nei->label);
//         hash[clone_nei->label] = clone_nei;
//         // push original node into queue
//         que.push(cur_node_nei);
//       }  // end if
//       hash[cur->label]->neighbors.push_back(hash[cur_node_nei->label]);
//     }  // end for
//   }  // end while

//   return newnode;
// }

// int bombGame(vector<vector<char>>& grid) {
//   if (grid.empty() || grid[0].empty())
//     return 0;
//   int row = grid.size(), col = grid[0].size();
//   int maxE = 0;

//   // count killed enemy in row direction
//   int kill_r = 0;
//   // count killed enemy in col direction
//   int kill_c[col] = {};

//   for (int r = 0; r < row; r ++) {
//     for (int c = 0; c < col; c ++) {
//       // count killed enemy in row direction
//       if (c == 0 || grid[r][c - 1] == 'W') {
//         kill_r = 0;
//         for (int k = c; k < col && grid[r][k] != 'W'; k ++)
//           kill_r += (grid[r][k] == 'E')? 1 : 0;
//       }

//       // count killed enemy in column direction
//       if (r == 0 || grid[r - 1][c] == 'W') {
//         kill_c[c] = 0;
//         for (int k = r; k < row && grid[k][c] != 'W'; k ++)
//           kill_c[c] += (grid[k][c] == 'E')? 1 : 0;
//       }

//       // only count for empty space
//       if (grid[r][c] == '0')
//         maxE = (maxE > kill_r + kill_c[c])? maxE : kill_r + kill_c[c];
//     }
//   }

//   return maxE;
// }

// vector<vector<int>> dir {{1, 0}, {-1, 0}, {0, -1}, {0, 1},
//                          {1, 1}, {-1, -1}, {-1, 1}, {1, -1}};


// int detect(vector<vector<int>> board, int row, int col, int r, int c) {
//   int live = 0;
//   for (int i = 0; i < 8; i ++) {
//     int next_r = r + dir[i][0];
//     int next_c = c + dir[i][1];

//     if (next_r < 0 || next_r >= row || next_c < 0 || next_c >= col)
//       continue;
//     live += (board[next_r][next_c]) & 1;
//   }
//   return live;
// }

// void gameOfLife(vector<vector<int>>& board) {
//   if (board.empty() || board[0].empty())
//     return;

//   int row = board,size(), col = board[0].size();
//   for (int r = 0; r < row; r ++) {
//     for (int c = 0; c < col; c ++) {
//       int num_live = detect(board, row, col, r, c);

//       if (board[r][c] == 1 && num_live >= 2 && num_live <= 3)
//         board[r][c] = 3;
//       else if (board[r][c] == 0 && num_live == 3)
//         board[r][c] = 2;
//     }
//   }

//   for (int r = 0; r < row; r ++) {
//     for (int c = 0; c < col; c ++)
//       board[r][c] >>= 1;
//   }

//   return;

// }

int main() {
  // vector<vector<char>> grid {{'0', 'E', '0', '0'}, 
  //                            {'E', '0', 'W', 'E'}, 
  //                            {'0', 'E', '0', '0'}};

  // cout << bombGame(grid) << endl;
  pascalTriangle(4);

}