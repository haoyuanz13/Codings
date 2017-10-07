#include <vector>
#include <utility>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <set>

using namespace std;

bool canFinish(int numCourses, vector<pair<int, int>>& prerequisites) {
  vector<vector<bool>> diredge (numCourses, vector<bool>(numCourses, false));
  int indegree [numCourses] = {};

  // count relationship and indegrees
  for (int i = 0; i < prerequisites.size(); i ++) {
    pair<int, int> cur = prerequisites[i];
    int pre = cur.first, post = cur.second;
    if (!diredge[pre][post]) {
      diredge[pre][post] = true;
      indegree[post] = indegree[post] + 1;
    }
  }

  int count = 0;
  queue<int> que;
  
  // push all 0 indegree node
  for (int i = 0; i < numCourses; i ++) {
    if (indegree[i] == 0)
      que.push(i);
  }

  // count valid nodes
  while (!que.empty()) {
    int pre = que.front();
    que.pop();
    count ++;

    for (int c = 0; c < numCourses; c ++) {
      if (diredge[pre][c]) {
        indegree[c] --;
        if (indegree[c] == 0)
          que.push(c);
      }
    }
  }
  return (count == numCourses);
}

bool dfs(vector<vector<bool>> diredge, vector<bool>& vis, int start) {
  if (vis[start])
    return false;

  vis[start] = true;
  for (int c = 0; c < diredge[start].size(); c ++) {
    if (!diredge[start][c])
      continue;
    if (!dfs(diredge, vis, c))
      return false;
  }
  
  // recover
  vis[start] = false;
  return true;
}


// dfs: once find dulplicate traversed node, exists circle
bool canFinish(int numCourses, vector<pair<int, int>>& prerequisites) {
  vector<vector<bool>> diredge (numCourses, vector<bool>(numCourses, false));
  vector<bool> vis (numCourses, false);
  vector<bool> isPre (numCourses, false);

  // count relationship and indegrees
  for (int i = 0; i < prerequisites.size(); i ++) {
    pair<int, int> cur = prerequisites[i];
    int pre = cur.first, post = cur.second;
    if (!diredge[pre][post]) {
      diredge[pre][post] = true;
      isPre[pre] = true;
    }
  }

  for (int i = 0; i < numCourses; i ++) {
    if (!isPre[i])
      continue;
    if (!dfs(diredge, vis, i))
      return false;
  }

  return true;
}


vector<int> findOrder(int numCourses, vector<pair<int, int>>& prerequisites) {
  int indegree[numCourses] = {};
  unordered_map<int, set<int>> edge;

  // count relationship and indegrees
  for (int i = 0; i < prerequisites.size(); i ++) {
    pair<int, int> cur = prerequisites[i];
    int pre = cur.second, post = cur.first;

    if (!(edge.count(pre) > 0)) {
      set<int> temp;
      edge[pre] = temp;
    }

    if (edge[pre].empty() || !(edge[pre].count(post) > 0) ) {
        indegree[post] = indegree[post] + 1;
    }
    edge[pre].insert(post);
  }

  int count = 0;
  vector<int> res;

  queue<int> que;
  for (int i = 0; i < numCourses; i ++) {
    if (indegree[i] == 0)
      que.push(i);
  }

  while (!que.empty()) {
    int cur = que.front();
    que.pop();

    res.push_back(cur);
    count ++;

    if (edge.count(cur) > 0) {
      set<int> followers = edge[cur];
      for (set<int>::iterator it = followers.begin(); it != followers.end(); ++ it) {
          int vec = *it;
          
          indegree[vec] = indegree[vec] - 1;
        if (indegree[vec] == 0)
          que.push(vec);
      }
    }
  }

  return (count == numCourses)? res : vector<int>{};
}