#include <vector>
#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

// longest substring without duplicates
// leetcode 3: dp or two pointers chasing
int lengthOfLongestSubstringDP(string s) {
  if (s.empty() || s.size() < 2)
    return s.size();

  // dp[i] represents the longest valid string length end at i
  int dp [s.size()] = {};
  dp[0] = 1;
  // key: the unique char in the string, value: its rightest position
  unordered_map<char, int> hash;
  hash[s.at(0)] = 0;

  int longest = 1;

  for (int i = 1; i < s.size(); i ++) {
    char cur = s.at(i);
    // new character
    if (hash.count(cur) <= 0)
      dp[i] = dp[i - 1] + 1;
    
    else {
      // the duplicate is out of valid region
      if (hash[cur] < i - dp[i - 1])
        dp[i] = dp[i - 1] + 1;
      else
        dp[i] = i - hash[cur];
    }

    longest = (dp[i] > longest)? dp[i] : longest;
    // put or update the rightest index
    hash[cur] = i;
  }

  return longest;
}

int lengthOfLongestSubstringTwoChasing(string s) {
  if (s.empty() || s.size() < 2)
    return s.size();

  // array to label all possible characters
  bool exi [256] = {};
  int slow = 0, fast = 0;
  int longest = 0, len = s.size();

  for (; slow < len; slow ++) {
    while (fast < len && !exi[int(s.at(fast))]) {
      longest = (fast - slow + 1 > longest)? fast - slow + 1 : longest;
      exi[s.at(fast)] = true;
      fast ++;
    }
    exi[int(s.at(slow))] = false;
  }

  return longest;
}

// the longest substring with at most k distinct characters
// leetcode 159, 340
int longestKDistinct(string s, int k) {
  int longest = 0;

  // key: unique character, value: occurrence time in the string
  unordered_map<char, int> window;
  int slow = 0, fast = 0;
  int len = s.size();

  for (; slow < len; slow ++) {
    char cur = s.at(fast);

    while (fast < len) {
      if (window.count(cur) > 0) 
        window[cur] += 1;
      else {
        if (window.size() == k)
          break;
        window[cur] = 1;
      }

      fast ++;
    }

    longest = (fast - slow > longest)? fast - slow : longest;

    cur = s.at(slow);
    if (window.count(cur) > 0) {
      if (window[cur] > 1)
        window[cur] -= 1;
      else
        window.erase(cur);
    }
  }

  return longest;
}


// the longest substring with at least k repeating characters
// the idea is the divide and conquer
int longestSubstring(string s, int k) {
  if (k == 0 || s.empty())
    return 0;

  int occ [26] = {};
  int len = s.size();
  // count appearence times
  for (int i = 0; i < len; i ++)
    occ[s.at(i) - 'a'] ++;

  // set those characters with less k times as split pivot
  vector<int> pos {-1};
  for (int i = 0; i < len; i ++) {
    if (occ[s.at(i) - 'a'] < k)
      pos.push_back(i);
  }
  pos.push_back(len);

  if (pos.size() == 2)
    return len;

  int longest = 0;
  for (int i = 1; i < pos.size(); i ++) {
    int ss = pos[i - 1] + 1;
    int ee = pos[i];

    int sublongest = longestSubstring(s.substr(ss, ee - ss), k);
    longest = (longest > sublongest)? longest : sublongest;
  }
  return longest;
}

int main() {
  string s = "aaabb";
  cout << longestSubstring(s, 3) << endl;
}