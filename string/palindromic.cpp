#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <array>

using namespace std;

// three methods to deal with palindromic problem

// find the longest palindromic string: manacher algorithm
string longestPal(string& str) {
  if (str.empty() || str.size() < 2)
    return str;

  // insert # to the original string
  char arr [str.size()];
  str.copy(arr, str.size(), 0);

  string mod_str = "#";
  for (int i = 0; i < str.size(); i ++) {
    char cur = arr[i];

    stringstream ss;
    string temp;
    
    ss << cur;
    ss >> temp;

    mod_str += temp + "#";
  }


  // string mod_str = "#" + str + "#";
  // int i = 2;
  // while (mod_str.at(i) != '#') {
  //   mod_str.insert(i, "#");
  //   i += 2;
  // }

  int len = mod_str.size();
  int dp [len];
  dp[0] = 1;
  int idc = 0;

  for (int i = 1; i < len; i ++) {
    dp[i] = 1;
    if (i < idc + dp[idc])
      dp[i] = min(idc + dp[idc] - i, dp[2 * idc - i]);

    while (i + dp[i] < len && i - dp[i] >= 0) {
      if (mod_str.at(i + dp[i]) == mod_str.at(i - dp[i]))
        dp[i] ++;
      else
        break;
    }

    idc = (dp[i] > dp[idc])? i : idc;
  }

  string res = "";
  for (int i = idc - dp[idc] + 2; i <= idc + dp[idc] - 2; i += 2) {
    res += mod_str.at(i);
  }

  cout << res << endl;
  return res;

}

string extend(string& s, int s1, int s2) {
  while (s1 >= 0 && s2 < s.size()) {
    if (s.at(s1) == s.at(s2)) {
      s1 --;
      s2 ++;
    }
    else
      break;
  }

  return s.substr(s1 + 1, s2 - s1 - 1);
}

// extend method, consider even and odd case
string longestPalExtend(string& str) {
  if (str.empty() || str.size() < 2)
    return str;

  string res = "";
  int len = str.size();

  for (int i = 0; i < len - 1; i ++) {
    // find old pal case
    string odd = extend(str, i, i);
    res = (odd.size() > res.size())? odd : res;

    // find even pal case
    string even = extend(str, i, i + 1);
    res = (even.size() > res.size())? even : res;
  }

  cout << res << endl;
  return res;
}

// DP method
string longestPalDP(string& str) {
  if (str.empty() || str.size() < 2)
    return str;

  int len = str.size();
  bool ispal [len][len];

  int opt_l = 0, opt_r = 0;
  int max_len = 0;
  for (int step = 0; step < len; step ++) {
    int l = 0, r = l + step;

    for (; r < len; l ++, r ++) {
      if (step == 0)
        ispal[l][r] = true;
      else if (step == 1)
        ispal[l][r] = (str.at(l) == str.at(r));
      else
        ispal[l][r] = ((str.at(l) == str.at(r)) && ispal[l + 1][r - 1]);

      if (ispal[l][r] && max_len < r - l + 1) {
        max_len = r - l + 1;
        opt_l = l, opt_r = r;
      }
    }
  }

  string res = str.substr(opt_l, max_len);
  cout << res << endl;
  return res;
}

int main(int argc, char** argv) {
  string t = "zhy220330";
  longestPalDP(t);

}