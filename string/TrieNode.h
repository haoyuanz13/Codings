#ifndef _TRIENODE_H
#define _TRIENODE_H

#include <stdio.h>
#include <algorithm>
#include <vector>
#include <cstddef>

class TrieNode{
public:
  TrieNode *child[26];
  bool isword;
  int idx;

  TrieNode() {
    this->isword = false;
    this->idx = 0;
    std::fill_n(this->child, 26, nullptr);
  }

};  // class TrieNode

#endif  // _TRIENODE_H