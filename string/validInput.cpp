#include <iostream>
#include <string>
#include <algorithm>
#include <string.h>
#include <ctype.h>
#include <limits>
// #include <stdio.h>

using namespace std;

// achieve trim function
string trim(string& str) {
  if (str.empty()) {
    return str;
  }

  // remove left-side white space 
  str.erase(0, str.find_first_not_of(' ')); 
  // remove right-side white space
  str.erase(str.find_last_not_of(' ') + 1);
  return str;
}

// convert string to integer 
int str2int(string& str) {
  string pure_str = trim(str);
  if (pure_str.empty())
    return 0;

  int sign = 1, ind = 0;

  if (!isdigit(pure_str.at(ind))) {
    char cur = pure_str.at(ind);

    if (cur != '+' && cur != '-')
      return 0;

    if (cur == '-')
      sign = -1;

    ind ++;
  }

  long long res = 0;
  while (ind < pure_str.size() && isdigit(pure_str.at(ind))) {
    res = res * 10 + pure_str.at(ind) - '0';

    if (sign * res > numeric_limits<int>::max())
      return numeric_limits<int>::max();
    if (sign * res < numeric_limits<int>::min())
      return numeric_limits<int>::min();

    ind ++;
  }

  return (int) sign * res;
}

// test valid input: using pointers
bool isValidNum(string& str) {
  // remove white spaces at two sides
  string pure_str = trim(str);

  // the original string contains all white space
  if (pure_str.empty())
    return false;

  pure_str += "*";   // the tail label
  int len = pure_str.size();

  int ind_p = 0, count = 0;

  // ind pointer movement
  if (pure_str.at(ind_p) == '+' || pure_str.at(ind_p) == '-')
    ind_p ++;
  
  // check digits
  while (isdigit(pure_str.at(ind_p))) {
    ind_p ++;
    count ++;
  }

  // check dot notation
  if (pure_str.at(ind_p) == '.')
    ind_p ++;

  // check digits
  while (isdigit(pure_str.at(ind_p))) {
    ind_p ++;
    count ++;
  }

  // no valid digit before possbile 'e'
  if (count == 0)
    return false;

  // meet 'e'
  if (pure_str.at(ind_p) == 'e') {
    count = 0;
    ind_p ++;

    if (pure_str.at(ind_p) == '+' || pure_str.at(ind_p) == '-')
      ind_p ++;

    while (isdigit(pure_str.at(ind_p))) {
      ind_p ++;
      count ++;
    }

    // the case that no digit chasing 'e' should be invalid
    if (count == 0)
      return false;
  }

  return (ind_p == len - 1);

}


int main(int argc, char** argv) {
  string input;
  cin >> input;

  // int res = str2int(input);
  int res = isValidNum(input);
  if (res)
    cout << "Valid number !" << endl;
  else
    cout << "Invalid number !" << endl;
  // cout << res << endl;
}