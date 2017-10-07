#include <string>
#include <cstring>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

// reverse string
string reverseStr(string& str) {
  if (str.empty() || str.size() < 2)
    return str;
  // built in function 
  string temp = str;  
  // it will modify the original string so it's better to make a copy of it
  reverse(temp.begin(), temp.end());  
  return temp;
}

// check whether the string is palindromic using two pointers
bool isPal(string& str) {
  if (str.empty())
    return false;
  if (str.size() == 1)
    return true;

  int l = 0, r = str.size() - 1;
  while (l <= r) {
    if (str.at(l) != str.at(r))
      return false;
    l ++;
    r --;
  }
  return true;
}

// find palindromic pairs, find index combination sets
vector<vector<int>> palindromicPairs(vector<string>& words) {
  vector<vector<int>> res;
  if (words.empty() || words.size() < 2)
    return res;

  unordered_map<string, int> hash;
  int len = words.size();

  for (int i = 0; i < len; i ++)
    hash[words[i]] = i;

  // empty string case
  if (hash.count("") > 0) {
    int ind = hash[""];
    for (int i = 0; i < len; i ++) {
      if (i == ind)
        continue;
      // check whether the string is a palindromic one
      if (isPal(words[i])) {
        vector<int> case1 {i, ind};
        vector<int> case2 {ind, i};

        res.push_back(case1);
        res.push_back(case2);
      }
    }
  }  // end outer if 

  // two strings are reserve ones
  for (int i = 0; i < len; i ++) {
    string rev = reverseStr(words[i]);
    if (hash.count(rev) > 0 && hash[rev] != i) {
      vector<int> case_cur {i, hash[rev]};
      res.push_back(case_cur);
    } 
  }

  // part of the string is palindromic
  for (int i = 0; i < len; i ++) {
    string cur = words[i];

    // check the front part
    for (int cut = 1; cut < cur.size(); cut ++) {
      string part1 = cur.substr(0, cut);
      string part1_rev = reverseStr(part1);

      string part2 = cur.substr(cut);
      string part2_rev = reverseStr(part2);

      if (isPal(part1) && hash.count(part2_rev) > 0 && hash[part2_rev] != i) {
        vector<int> case_cur {hash[part2_rev], i};
        res.push_back(case_cur);
      }

      if (isPal(part2) && hash.count(part1_rev) > 0 && hash[part1_rev] != i) {
        vector<int> case_cur {i, hash[part1_rev]};
        res.push_back(case_cur);
      }
    }  // end innner for

  }  // end outer for

  return res;
}

int main() {
  vector<string> words {"abcd", "dcba", "lls", "s", "sssll", ""};
  vector<vector<int>> res = palindromicPairs(words);
  for (int i = 0; i < res.size(); i ++) {
    vector<int> cur = res[i];
    for (int j = 0; j < cur.size(); j ++)
      cout << cur[j] << " ";
    cout << "\n";
  }

}