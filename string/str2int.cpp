#include <vector>
#include <string>
#include <cstring>
#include <cctype>
#include <limits>

using namespace std;

// remove white space around string
string trim(string& str) {
  if (str.empty())
    return str;

  // remove the white space in left side
  str.erase(0, str.find_first_not_of(' '));

  // remove the white space in right side
  str.erase(str.find_last_not_of(' ') + 1);

  return str;
}

// designed string to integer
int myAtoi(string str) {
  // trim
  str = trim(str);
  if (str.empty())
    return 0;

  char charArray [str.size()];
  strcpy(charArray, str.c_str());

  int flag = 1, ind = 0;
  if (!isdigit(charArray[ind])) {
    char cur = charArray[ind];
    if (cur != '+' && cur != '-')
      return 0;
    if (cur == '-')
      flag = -1;
    ind ++;
  }

  // prevent overflow
  long res = 0;
  int themax = numeric_limits<int>::max();
  int themin = numeric_limits<int>::min();
  while (ind < str.size() && isdigit(charArray[ind])) {
    res = res * 10 + charArray[ind] - '0';

    if (flag * res > themax)
      return themax;
    if (flag * res < themin)
      return themin;

    ind ++;
  }

  res *= flag;
  return (int)res;

}