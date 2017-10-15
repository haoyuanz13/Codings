#include <vector>
#include <iostream>
#include <unordered_map>
#include <string>
#include <limits>
#include <math.h>
#include <algorithm>

using namespace std;

// long division problem, leetcode 166
// use hash map and need to deal with overflow problem
string fractionToDecimal(int numerator, int denominator) {
  if (numerator == denominator)
    return "1";

  if (denominator == 0) {
    if (numerator > 0)
      return to_string(numeric_limits<int>::max());
    else
      return to_string(numeric_limits<int>::min());
  }

  if (numerator == 0)
    return "0";

  // main process
  string res = "";
  res += ((numerator > 0) ^ (denominator > 0))? "-" : "";

  long nom = abs((long)numerator);
  long den = abs((long)denominator);  // cast long type first

  // extract integer part
  res += to_string(nom / den);
  nom %= den;

  // no fraction part
  if (nom == 0)
    return res;

  res += ".";
  unordered_map<long, int> hash;
  hash[nom] = res.size();

  while (nom != 0) {
    nom *= 10;
    res += to_string(nom / den);
    nom %= den;

    if (hash.count(nom)) {
      res.insert(hash[nom], "(");
      res += ")";
      break;
    }
    hash[nom] = res.size();
  }

  return res;
}


int main() {
  int a = -1;
  int b = -2147483648;
  cout << fractionToDecimal(a, b) << endl;
}