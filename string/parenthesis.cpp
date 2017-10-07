#include <string>
#include <iostream>
#include <stack>
#include <vector>
#include <string>

using namespace std;

// check whether the string is a valid parenthesis one
bool validParenthesis(string& str) {
  stack<char> stk;

  if (str.empty() || str.size() < 2)
    return false;

  for (int i = 0; i < str.size(); i ++) {
    char cur = str.at(i);

    if (cur == '(' || cur == '{' || cur == '[')
      stk.push(cur);
    else {
      if (stk.empty())
        return false;

      if (cur == ')' && stk.top() != '(') 
        return false;

      if (cur == ']' && stk.top() != '[')
        return false;

      if (cur == '}' && stk.top() != '{')
        return false;

      stk.pop();
    }
  }
  return stk.empty();

}

// find the longest valid parenthesis within the string
int longestValid(string& str) {
  if (str.empty() || str.size() < 2)
    return 0;
  // stack to store index
  stack<int> stk;
  int len = str.size();

  for (int i = 0; i < len; i ++) {
    char cur = str.at(i);

    if (cur == '(')
      stk.push(i);
    else {
      if (!stk.empty() && str.at(stk.top()) == '(')
        stk.pop();
      else
        stk.push(i);
    }
  }

  if (stk.empty())
    return len;

  int longest = 0;
  int l = 0, r = len;

  while (!stk.empty()) {
    l = stk.top();
    longest = (r - l - 1 > longest)? r - l - 1 : longest;
    r = l; 
    stk.pop();
  }

  return (l > longest)? l : longest;

}

int main(int argc, char**argv) {
  string str = ")()()(";

  cout << longestValid(str) << endl;

}