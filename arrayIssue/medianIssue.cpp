#include <vector>
#include <queue>
#include <iostream>
#include <algorithm>
#include <unordered_map>

using namespace std;

// create a contact comparison structure
struct myComparison
{
  bool ascending;

  // the deflaut order is desceng
  myComparison(const bool &ascend = false){
    ascending = ascend;
  }
  // define operator
  bool operator() (const int &a, const int &b) const {
    if (ascending)
      return a > b;  // ascending 
    else
      return a < b;  // descending
  }
  
};

// create a max heap for the first half
priority_queue<float, vector<float>, myComparison> maxh;
priority_queue<float, vector<float>, myComparison> minh(true);

unordered_map<int, int> maxh_hash;
unordered_map<int, int> minh_hash;

class Solution {
public:
    
    
int validSize(bool ismaxh) {
  int res = 0;
  if (ismaxh) {
    for (auto& x : maxh_hash) {
      res += (x.second > 0)? 1 : 0;
    }
  } else {
    for (auto& x : minh_hash) {
      res += (x.second > 0)? 1 : 0;
    }
  }

  return res;
}


void add(int num) {
  maxh.push(num);
  if (maxh_hash.count(num) <= 0)
    maxh_hash[num] = 0;
  maxh_hash[num] += 1;

  int cur = maxh.top();
  maxh.pop();
  maxh_hash[cur] -= 1;

  minh.push(cur);
  if (minh_hash.count(cur) <= 0)
    minh_hash[num] = 0;
  minh_hash[num] += 1;

  int size_maxh = validSize(true);
  int size_minh = validSize(false);

  if (size_maxh < size_minh) {
    cur = minh.top();
    minh.pop();
    minh_hash[cur] -= 1;

    maxh.push(cur);
    if (maxh_hash.count(cur) <= 0)
      maxh_hash[num] = 0;
    maxh_hash[num] += 1;
  }

  return;
}

void update(int num) {
  if (maxh_hash.count(num) > 0) {
    maxh_hash[num] -= 1;
  } else {
    minh_hash[num] -= 1;
  }

  int size_maxh = validSize(true);
  int size_minh = validSize(false);

  if (size_maxh < size_minh) {
    int cur = minh.top();
    minh.pop();
    minh_hash[cur] -= 1;

    maxh.push(cur);
    if (maxh_hash.count(cur) <= 0)
      maxh_hash[num] = 0;
    maxh_hash[num] += 1;
  }
  return;
}

double getMedian() {
  if (maxh.empty() && minh.empty())
    return (double)0;

  int size_maxh = validSize(true);
  int size_minh = validSize(false);

  int peek_maxh = maxh.top();
  while (maxh_hash[peek_maxh] <= 0) {
    maxh.pop();
    peek_maxh = maxh.top();
  }

  int peek_minh = minh.top();
  while (minh_hash[peek_minh] <= 0) {
    minh.pop();
    peek_minh = minh.top();
  }

  if (size_maxh == size_minh)
    return ((double)peek_maxh + (double)peek_minh) / 2.0;
  else
    return (double)peek_maxh;

}


vector<double> medianSlidingWindow(vector<int>& nums, int k) {
  vector<double> res;
  if (nums.empty() || nums.size() < 1)
    return res;

  int len = nums.size();
  int total = len - k + 1;
  if (total <= 0) {
    res.push_back(0.0);
    return res;
  }

  res.reserve(total);

  for (int i = 0; i <= len; i ++) {
    if (i >= k) {
      res[i - k] = getMedian();
      update(nums[i - k]);
    }

    if (i < len)
      add(nums[i]);
  }

  return res;
}
};