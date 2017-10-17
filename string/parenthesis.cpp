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

// Leetcode 241: add parentheses, divide and conquer problem
unordered_map<string, vector<int>> hash;
vector<int> diffWaysToCompute(string input) {
  vector<int> res;
  if (hash.count(input) > 0)
    return hash[input];

  for (int i = 0; i < input.size(); i ++) {
    char cur = input.at(i);
    if (cur != '+' && cur != '-' && cur != '*')
      continue;

    vector<int> pre = diffWaysToCompute(input.substr(0, i));
    vector<int> beh = diffWaysToCompute(input.substr(i + 1));

    for (int j1 = 0; j1 < pre.size(); j1 ++) {
      for (int j2 = 0; j2 < beh.size(); j2 ++) {
        if (cur == '+')
          res.push_back(pre.at(j1) + beh.at(j2));

        if (cur == '-')
          res.push_back(pre.at(j1) - beh.at(j2));

        if (cur == '*')
          res.push_back(pre.at(j1) * beh.at(j2));
      }  // end inner for
    }  // end outer for
  }

  if (res.empty())
    res.push_back(stoi(input));
  hash[input] = res;

  return res;
}

int main(int argc, char**argv) {
  string str = ")()()(";

  cout << longestValid(str) << endl;

}
