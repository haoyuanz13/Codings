#include <stack>
#include <iostream>

// use the stack to implement queue: two stacks

class MyQueue {
public:
  // store the pushed elements in stack order 
  stack<int> stk_in;

  // store the elements in queue order, the inverse order of stk_in
  stack<int> stk_out;

  /** Initialize your data structure here. */
  MyQueue() {
      
  }

  /** Push element x to the back of queue. */
  void push(int x) {
    stk_in.push(x);
  }

  /** Removes the element from in front of queue and returns that element. */
  int pop() {
    if (stk_out.empty())
      reverse();
    int res = stk_out.top();
    stk_out.pop();
    return res;
  }

  /** Get the front element. */
  int peek() {
    if (stk_out.empty())
      reverse();
    return stk_out.top();      
  } 

  /** Returns whether the queue is empty. */
  bool empty() {
    return (stk_in.empty()) && (stk_out.empty());
  }

  void reverse() {
    while (!stk_in.empty()) {
      int get = stk_in.top();
      stk_in.pop();
      stk_out.push(get);
    }
    return;
  }
};

/**
 * Your MyQueue object will be instantiated and called as such:
 * MyQueue obj = new MyQueue();
 * obj.push(x);
 * int param_2 = obj.pop();
 * int param_3 = obj.peek();
 * bool param_4 = obj.empty();
 */