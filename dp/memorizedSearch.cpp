#include <vector>
#include <iostream>
#include <unordered_map>

using namespace std;

// convert vector into int key form
int encode(vector<int>& used) {
  int key = 0;
  for (int i = 0; i < used.size(); i ++) {
    key <<= 1;
    key |= used[i];
  }
  return key;
}


bool canwin(int des, vector<int>& used, unordered_map<int, bool>& hash) {
  int key = encode(used);
  if (hash.count(key) > 0)
    return hash[key];

  for (int val = 1; val < used.size(); val ++) {
    if (used[val] == 0) {
      used[val] = 1;  // represent usage 
      if (des <= val || !canwin(des - val, used, hash)) {
        hash[key] = true;
        used[val] = 0;  // clean up
        return true;
      }  // end if
      used[val] = 0;
    }  // end if
  }  // end for

  hash[key] = false;
  return false;
}

// leetcode 464: using memorized search 
bool canIWin(int maxChoosableInteger, int desiredTotal) {
  int sum = (1 + maxChoosableInteger) * maxChoosableInteger / 2;
  if (sum < desiredTotal)
    return false;

  if (desiredTotal <= 0)
    return true;

  unordered_map<int, bool> hash;
  vector<int> used (maxChoosableInteger + 1, 0);

  return canwin(desiredTotal, used, hash);
}