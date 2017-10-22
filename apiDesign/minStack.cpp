#include <stack>
#include <queue>
#include <iostream>
#include <limits>
#include <unordered_map>

using namespace std;

struct myComp
{
  myComp() {}

  bool operator() (long& a, long& b) const {
      return a > b;
  }
  
};

// method one: use priority queue to store elements in ascending order
class MinStack {
public:
  stack<int> stk;
  priority_queue<long, vector<long>, myComp> que;
  
  /** initialize your data structure here. */
  MinStack() {
  }
  
  void push(int x) {
    stk.push(x);
    que.push((long)x);
  }
  
  void pop() {
    int cur = stk.top();
    stk.pop();
    
    // delete the element that has been poped from stack
    vector<long> temp;
    while (!que.empty()) {
      long it = que.top();
      if ((int)it == cur) {
        que.pop();
        break;
      }

      else {
        temp.push_back(it);
        que.pop();
      }
    }

    for (int i = 0; i < temp.size(); i ++) 
      que.push(temp[i]);

  }
  
  int top() {
    if (!stk.empty())
      return stk.top();
  }
  
  int getMin() {
    long res = que.top();
    if (res < numeric_limits<int>::min())
      return numeric_limits<int>::min();
    else
      return (int)res;
  }
};

// much faster way: use hash table to store the appearance times of element in the stack
class MinStack {
public:
  stack<int> stk;
  priority_queue<long, vector<long>, myComp> que;
  unordered_map<long, int> hash;
  /** initialize your data structure here. */
  MinStack() {
  }
  
  void push(int x) {
    stk.push(x);

    long long_x = (long)x;
    que.push(long_x);

    if (hash.count(long_x) <= 0)
      hash[long_x] = 0;
    // count appearence times
    hash[long_x] += 1;
  }
  
  void pop() {
    int cur = stk.top();
    stk.pop();

    hash[(long)cur] -= 1;
  }
  
  int top() {
    if (!stk.empty())
      return stk.top();
  }
  
  int getMin() {
    long res = que.top();

    while (hash[res] <= 0) {
      que.pop();
      res = que.top();
    }

    if (res < numeric_limits<int>::min())
      return numeric_limits<int>::min();
    else
      return (int)res;
  }
};


// method 3: create a new strcture and take the min stack as linked list
struct Node
{
  int val;
  int min;  // store the min value of the whole linked list
  Node* next;

  Node(int v, int m) {
    val = v;
    min = m;
    next = nullptr;
  }

  Node(int v, int m, Node* n) {
    val = v;
    min = m;
    next = n;
  }

};

class MinStack {
public:
  Node* head;

  /** initialize your data structure here. */
  MinStack() {
    head = nullptr;
  }
  
  void push(int x) {
    if (head == nullptr)
      head = new Node(x, x);
    else {
      // make the new inserted node as the head one to simulate stack stucture
      Node* cur = new Node(x, min(x, head->min), head);
      head = cur;
    }
      
  }
  
  void pop() {
    head = head->next;
  }
  
  int top() {
    return head->val;
  }
  
  int getMin() {
    return head->min;
  }
};



/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack obj = new MinStack();
 * obj.push(x);
 * obj.pop();
 * int param_3 = obj.top();
 * int param_4 = obj.getMin();
 */