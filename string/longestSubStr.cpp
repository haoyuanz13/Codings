#include <string>
#include <unordered_map>
#include <iostream>
#include <vector>

using namespace std;

// find the longest substring without duplicates 
int longestNoDupSubStr(string& str) {
  if (str.empty())
    return 0;
  if (str.size() < 2)
    return str.size();

  int len = str.size();
  // dp[i] stores the longest valid string end at index i
  vector<int> dp (len, 1);
  // hash table to store the rightest index of each unique char
  unordered_map<char, int> hash;
  hash[str.at(0)] = 0;

  int longest = 1;
  for (int i = 1; i < len; i ++) {
    char cur = str.at(i);

    if (hash.count(cur) <= 0)
      dp[i] = dp[i - 1] + 1;

    else {
      if (hash[cur] < i - dp[i - 1])
        dp[i] = dp[i - 1] + 1;
      else
        dp[i] = 1 - hash[cur];
    }

    longest = (dp[i] > longest)? dp[i] : longest;
    hash[cur] = i;
  }
  return longest;
}

// the substring is allowed to contain at most K duplicates
int longestKDupSubStr(string& str, int K) {
  if (str.empty())
    return 0;
  if (str.size() < 2)
    return str.size();

  vector<int> times (256, 0);

  int slow = 0, fast = 0;
  int longest = 0, len = str.size();

  for (; slow < len; slow ++) {
    while (fast < len && times[str.at(fast)] < K) {
      longest = (fast - slow + 1 > longest)? fast - slow + 1 : longest;
      times[str.at(fast)] += 1;
      fast ++;
    }

    times[str.at(slow)] -= 1;
  }

  return longest;
}

int main(int argc, char** argv) {
  string str = "abcabcbb";
  cout << longestKDupSubStr(str, 3) << endl;

}