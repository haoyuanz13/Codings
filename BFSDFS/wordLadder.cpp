#include <vector>
#include <string>
#include <iostream>
#include <queue>
#include <set>
#include <algorithm>
#include <cstring>

using namespace std;

// convert string into char vector
vector<char> str2Vector(string& str) {
  char str_arr[str.size()];
  strcpy(str_arr, str.c_str());

  vector<char> res (str_arr, str_arr + str.size());
  return res;
}

int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
  if (beginWord.compare(endWord) == 0)
    return 0;
  // create a new set for better search performance
  set<string> wordset {endWord};
  for (int i = 0; i < wordList.size(); i ++)
    wordset.insert(wordList[i]);

  queue<string> que;
  set<string> vis;

  // BFS pipeline
  que.push(beginWord);
  int step_size = 1, layer_num = 1;

  while (!que.empty()) {
    string cur = que.front();
    que.pop();
    layer_num --;

    vector<char> chars = str2Vector(cur);
    for (int i = 0; i < chars.size(); i ++) {
      // replace char at each position to find next possible word in the list
      for (char rep = 'a'; rep <= 'z'; rep ++) {
        char store = chars[i];
        if (store == rep)
          continue;

        chars[i] = rep;
        string newcur(chars.begin(), chars.end());
        if (newcur.compare(endWord) == 0)
          return step_size + 1;

        if (vis.count(newcur) <= 0 && wordset.count(newcur) > 0) {
          que.push(newcur);
          vis.insert(newcur);
        }
        // recover
        chars[i] = store;
      }
    }

    // current layer end
    if (layer_num == 0) {
      if (que.empty())
        return 0;
      layer_num = que.size();
      step_size ++;
    }

  }
  return step_size;
}

int main() {
  string beg = "hit";
  string end = "cog";
  vector<string> wl {"hot", "dot", "dog", "lot", "log"};

  cout << ladderLength(beg, end, wl) << endl;
}