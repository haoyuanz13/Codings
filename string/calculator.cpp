#include <string>
#include <stack>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

// calculator problem always uses stack


// convert string into char array
vector<char> str2CharArray(string& str) {
  char arr [str.size()];
  strcpy(arr, str.c_str());

  vector<char> vec (arr, arr + str.size());
  return vec;
}

// the basic calculator contains parenthesis
int calculator1(string& str) {
  int len = str.size();
  int sign = 1, res = 0;

  // create a stack
  stack<int> stk;

  // convert string into a char vector
  vector<char> char_arr = str2CharArray(str);

  for (int i = 0; i < len; i ++) {
    char cur = char_arr[i];

    // digit
    if (isdigit(cur)) {
      int sum = cur - '0';
      i ++;

      while (i < len) {
        char nextc = char_arr[i];

        if (isdigit(nextc))
          sum = sum * 10 + nextc - '0';
        else
          break;

        i ++;
      }

      i --;  // move back one position to compensate the addition in for loop
      res += sign * sum;
    }  // end if digit

    else if (cur == '+')
      sign = 1;
    else if (cur == '-')
      sign = -1;
    else if (cur == '(') {
      stk.push(res);
      stk.push(sign);

      // store previous result and compute within parenthesis
      res = 0;
      sign = 1;
    }

    else if (cur == ')') {
      int pre_sign = stk.top();
      stk.pop();

      int pre_res = stk.top();
      stk.pop();

      res = res * pre_sign + pre_res;
    }

    // cout << res << endl;
  }  // end for

  // cout << "\n";
  return res;

}


// basic calculator, operators with different priorities
int calculator2(string& str) {
  int len = str.size();
  int res = 0;
  char sign = '+';

  // create a stack
  stack<int> stk;

  // convert string into a char vector
  vector<char> char_arr = str2CharArray(str);

  int sub_sum = 0;
  for (int i = 0; i < len; i ++) {
    char cur = char_arr[i];

    if (isdigit(cur))
      sub_sum = sub_sum * 10 + cur - '0';

    if ((!isdigit(cur) && cur != ' ') || i == len - 1) {
      if (sign == '+')
        stk.push(sub_sum);

      else if (sign == '-')
        stk.push(-sub_sum);

      else if (sign == '*') {
        int top = stk.top();
        stk.pop();
        stk.push(top * sub_sum);
      }

      else if (sign == '/') {
        int top = stk.top();
        stk.pop();
        stk.push(top / sub_sum);
      }

      sign = cur;
      sub_sum = 0;
    }

  }

  while (!stk.empty()) {
    res += stk.top();
    stk.pop();
  }

  return res;

}


int main() {
  string input = "1 - 3 * 5 / 3";
  cout << calculator2(input) << endl;
  return 0;

}