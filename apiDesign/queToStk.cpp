#include <queue>
#include <iostream>
#include <deque>

// use the standard queue to implement stack
// Alternatively, deque will be better and convient

class MyStack {
public:
  /** Initialize your data structure here. */
  // use the standard queue
  queue<int> que;
  MyStack() {
  }

  /** Push element x onto stack. */
  void push(int x) {
    que.push(x);
    // reverse
    for (int i = 0; i < que.size() - 1; i ++) {
      int cur = que.front();
      que.pop();
      que.push(cur);
    }
  }

  /** Removes the element on top of the stack and returns that element. */
  int pop() {
    int res = que.front();
    que.pop();
    return res;
  }

  /** Get the top element. */
  int top() {
    return que.front();
  }

  /** Returns whether the stack is empty. */
  bool empty() {
    return que.empty();
      
  }
};

/**
 * Your MyStack object will be instantiated and called as such:
 * MyStack obj = new MyStack();
 * obj.push(x);
 * int param_2 = obj.pop();
 * int param_3 = obj.top();
 * bool param_4 = obj.empty();
 */