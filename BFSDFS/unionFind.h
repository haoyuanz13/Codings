#ifndef _UNION_FIND_H
#define _UNION_FIND_H

#include <vector>
#include <iostream>

using namespace std;

class unionFind {
public:
  unionFind(): count(0) {}
  
  unionFind(int n) {
    father.reserve(n);

    for (int i = 0; i < n; i ++)
      father[i] = i;
  }
  
  virtual ~unionFind() {}


// class function
public:
  // find input's father
  int find(int x) {
    if (father[x] == x)
      return x;
    father[x] = find(father[x]);
    return father[x];
  }

  // union two elements
  void unions(int node1, int node2) {
    int rt1 = find(node1), rt2 = find(node2);
    if (rt1 == rt2)
      return;
    father[rt1] = rt2;
    count --;
    return;
  }

  // return group number
  int query() {
    return count;
  }

  // set group number
  void set_count(int total) {
    count = total;
  }

// private variables
private:
  vector<int> father;
  int count; 

};  // end class

#endif // _UNION_FIND_H