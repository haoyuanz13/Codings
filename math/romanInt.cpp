#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

// convert integer into roman 
// create a pivot hashtable to seperate format
string intToRoman(int num) {
  unordered_map<int, vector<string>* > hash;

  hash[0] = new vector<string>{"", "M", "MM", "MMM"};
  hash[1] = new vector<string>{"", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM"};
  hash[2] = new vector<string>{"", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC"};
  hash[3] = new vector<string>{"", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX"};

  string roman = "";
  int div = 1000;

  for (int i = 0; i < 4; i ++) {
    int bit = num / div;
    roman += hash[i]->at(bit);

    num %= div;
    div /= 10;
  }

  return roman;
}


// roman to int
int romanToInt(string s) {
  unordered_map<char, int> hash ({{'M', 1000}, {'D', 500}, {'C', 100}, 
                                  {'L', 50}, {'X', 10}, {'V', 5}, {'I', 1}});

  int res = 0;
  for (int i = 0; i < s.size() - 1; i ++) {
    if (hash[s.at(i)] < hash[s.at(i + 1)])
      res -= hash[s.at(i)];
    else
      res += hash[s.at(i)];
  }

  return res + hash[s.back()];
}