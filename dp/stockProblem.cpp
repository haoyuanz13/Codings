#include <vector>
#include <iostream>
#include <algorithm>
#include <limits>

using namespace std;

// buy and sell stock problem 


// leetcode 121: only one transaction allowed and compute the max profit
int maxProfit121(vector<int>& prices) {
  if (prices.empty() || prices.size() < 2)
    return 0;

  int len = prices.size();
  // max_p[i] represents the max profit can obtain until day i
  vector<int> max_p(len, 0);
  int lmin = prices.front();

  int res = 0;
  for (int i = 1; i < len; i ++) {
    int cur = prices[i];
    if (cur < lmin) {
      lmin = cur;
      max_p[i] = max_p[i - 1];
    } else {
      max_p[i] = (max_p[i - 1] > cur - lmin)? max_p[i - 1] : (cur - lmin);
    }

    res = (max_p[i] > res)? max_p[i] : res;
  }

  return res;
}

// leetcode 122: transaction multiple times and compute the max profit
// greedy method
int maxProfit122(vector<int>& prices) {
  if (prices.empty() || prices.size() < 2)
    return 0;

  int len = prices.size();
  int res = 0;

  for (int i = 0; i < len - 1; i ++) {
    int day_profit = prices[i + 1] - prices[i];
    res += (day_profit > 0)? day_profit : 0;
  }
  return res;
}

// leetcode 123: transaction at most twice and compute the max profit
// separate two times transcations, take the ith day as pivot, compute its left and right side max profit just like problem 121
int maxProfit123(vector<int>& prices) {
  if (prices.empty() || prices.size() < 2)
    return 0;

  int len = prices.size();
  // left[i] represents the max profit can obtain until day i
  // right[i] represents the max profit can obtain from day i to len - 1
  vector<int> left(len, 0);
  vector<int> right(len, 0);

  // left to right traverse
  int lmin = prices.front();
  for (int i = 1; i < len; i ++) {
    int cur = prices[i];
    if (cur < lmin) {
      lmin = cur;
      left[i] = left[i - 1];
    } else {
      left[i] = (left[i - 1] > cur - lmin)? left[i - 1] : (cur - lmin);
    }
  }

  // right to left traverse
  int lmax = prices.back();
  for (int i = len - 2; i >= 0; i --) {
    int cur = prices[i];
    if (cur >lmax) {
      lmax = cur;
      right[i] = right[i + 1];
    } else {
      right[i] = (right[i + 1] > lmax - cur)? right[i + 1] : (lmax - cur);
    }
  }

  // find the max comb
  int res = 0;
  for (int i = 0; i < len; i ++)
    res = (res > left[i] + right[i])? res : left[i] + right[i];

  return res;

}


// leetcode 188: transaction at most k times
// two matrixs to store local and global value
int maxProfit188(int k, vector<int>& prices) {
  if (prices.empty() || prices.size() < 2)
    return 0;
  int len = prices.size();

  // if given more than len/2 transaction times, we can use greedy method
  if (k >= len / 2) {
    int res = 0;
    for (int i = 0; i < len - 1; i ++) {
      int day_profit = prices[i + 1] - prices[i];
      res += (day_profit > 0)? day_profit : 0;
    }
    return res;
  }

  // the general method
  vector<vector<int>> global(len, vector<int>(k + 1, 0));
  vector<vector<int>> local(len, vector<int>(k + 1, 0));

  for (int deal_time = 1; deal_time <= k; deal_time ++) {
    for (int day_time = 1; day_time < len; day_time ++) {
      int day_profit = prices[day_time] - prices[day_time - 1];

      int val1 = global[day_time - 1][deal_time - 1] + ((day_profit > 0)? day_profit : 0);
      int val2 = local[day_time - 1][deal_time] + day_profit;

      local[day_time][deal_time] = max(val1, val2);
      global[day_time][deal_time] = max(global[day_time - 1][deal_time], local[day_time][deal_time]);
    }
  }

  return global[len - 1][k];
}

// leetcode 309: buy as many times as you want but have some constraints
// use the graph to show transactions
int maxProfit309(vector<int>& prices) {
  if (prices.empty() || prices.size() < 2)
    return 0;

  // three states 
  int len = prices.size();

  vector<int> canBuyorRest(len, 0);
  vector<int> canSellotRest(len, 0);
  vector<int> onlyRest(len, 0);

  canBuyorRest[0] = 0;
  canSellotRest[0] = -prices.front();
  onlyRest[0] = numeric_limits<int>::min();

  for (int i = 1; i < len; i ++) {
    canBuyorRest[i] = max(canBuyorRest[i - 1], onlyRest[i - 1]);
    canSellotRest[i] = max(canSellotRest[i - 1], canBuyorRest[i - 1] - prices[i]);
    onlyRest[i] = canSellotRest[i - 1] + prices[i];
  }

  return max(canBuyorRest.back(), onlyRest.back());

}

int main() {

}