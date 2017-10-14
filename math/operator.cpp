#include <vector>
#include <iostream>
#include <stack>
#include <algorithm>
#include <unordered_map>
#include <limits>
#include <deque>
#include <string>

using namespace std;

// achieve basic operations via logic such as XOR, AND

// sum: AND to get carry, XOR to get add result
int getSum(int a, int b) {
  while (b != 0) {
    int c = a & b;
    a ^= b;
    b = (c << 1);
  }
  return a;
}

// subtraction: similar as sum, just convert one integer as negative form
int getSubtract(int a, int b) {
  while (b != 0) {
    int bor = (~a) & b;
    a ^= b;
    b = bor << 1;
  }

  return a;
}


// division: use binary search, the basic idea is subtraction
int divide(int dividend, int divisor) {
  int sign = ((dividend > 0) ^ (divisor > 0))? -1 : 1;

  long dd = abs(long(dividend));
  long ds = abs(long(divisor));
  long pivot = ds;

  // handle overflow problem
  if (ds == 0)
    return (sign == 1)? numeric_limits<int>::max() : numeric_limits<int>::min();

  if (dd == 0 || dd < ds)
    return 0;

  unordered_map<long, long> hash;
  hash[ds] = 1;
  deque<long> divi;
  divi.push_front(ds);

  for (int i = 0; i < 32; i ++) {
    long mul = hash[ds];
    hash[ds + ds] = mul + mul;
    ds += ds;

    if (ds > dd)
      break;
    divi.push_front(ds);
  }

  long res = 0;
  for (int i = 0; i < divi.size(); i ++) {
    long cur = divi[i];
    if (dd >= cur) {
      dd -= cur;
      res += hash[cur];
    }
    if (dd < pivot)
      break;
  }

  if (res > numeric_limits<int>::max())
    return (sign == 1)? numeric_limits<int>::max() : numeric_limits<int>::min();

  return sign * (int) res;

}

// multiplication: start from the end of string which is the lowest digit
string multiply(string num1, string num2) {
  int len1 = num1.size(), len2 = num2.size();
  int pos[len1 + len2] = {};

  for (int ind1 = len1 - 1; ind1 >= 0; ind1 --) {
    for (int ind2 = len2 - 1; ind2 >= 0; ind2 --) {
      int mul = (num1.at(ind1) - '0') * (num2.at(ind2) - '0');
      int posHigh = ind1 + ind2, posLow = ind1 + ind2 + 1;

      int sum = mul + pos[posLow];

      pos[posHigh] += sum / 10;
      pos[posLow] = sum % 10;

    }  // end inner for
  }  // end outer for

  string res = "";
  for (int ch : pos) {
    if (ch == 0 && res.empty())
      continue;

    res += to_string(ch);
  }

  return (res.empty())? "0" : res;
}


int main() {
  int a = 1, b = 12;
  // int s = getSum(a, b);
  int s = getSubtract(a, b);

  cout << s << endl;
}