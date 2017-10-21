#include <vector>
#include <iostream>
#include <queue>

using namespace std;

// the interval problem


struct Interval
{
  int start;
  int end;

  Interval() : start(0), end(0) {}
  Interval(int s, int e) : start(s), end(e) {}

};


struct myComp
{
  bool ascending;
  myComp(const bool& asd = false) {
    ascending = asd;
  }

  // sort based on the start time
  bool operator() (const Interval& a, const Interval& b){
    if (ascending)
      return (a.start) > (b.start);
    else
      return (a.start) < (b.start);
  }
};

bool comp(Interval& a, Interval& b) {
  return a.start > b.start;
}

// Leetcode 56: merge intervals
vector<Interval> merge1(vector<Interval>& intervals) {
  if (intervals.empty() || intervals.size() < 1)
    return intervals;

  // ascending sort based on the Interval's start
  priority_queue<Interval, vector<Interval>, myComp> inter_que(true);
  for (int ind = 0; ind < intervals.size(); ind ++)
    inter_que.push(intervals[ind]);

  Interval pre = inter_que.top();
  inter_que.pop();
    
  vector<Interval> res;
  while (!inter_que.empty()) {
    Interval cur = inter_que.top();
    inter_que.pop();

    if (cur.start > pre.end) {
      res.push_back(pre);
      pre = cur;
    }
      
    else
      pre.end = max(pre.end, cur.end);
  }
  
  // deal with the last element
  res.push_back(pre);

  return res;

}


// alternative method: sort start and end times separately
// Leetcode 56: merge intervals
vector<Interval> merge(vector<Interval>& intervals) {
  if (intervals.empty() || intervals.size() < 1)
    return intervals;

  int total = intervals.size();
  vector<int> start_times(total, 0);
  vector<int> end_times(total, 0);

  for (int i = 0; i < total; i ++) {
    start_times[i] = intervals[i].start;
    end_times[i] = intervals[i].end;
  }

  sort(start_times.begin(), start_times.end());
  sort(end_times.begin(), end_times.end());

  vector<Interval> res;
  for (int i = 0, j = 0; i < total; i ++) {
    if (i == total - 1 || start_times[i + 1] > end_times[i]) {
      Interval cur(start_times[j], end_times[i]);
      res.push_back(cur);
      j = i + 1;
    }
  }

  return res;

}


// Leetcode 57: insert intervals
vector<Interval> insert(vector<Interval>& intervals, Interval newInterval) {
  vector<Interval> res;
  bool hasInserted = false;

  for (int i = 0; i < intervals.size(); i ++) {
    Interval cur = intervals[i];
    if (hasInserted || cur.end < newInterval.start)
      res.push_back(cur);
    else if (cur.start > newInterval.end) {
      res.push_back(newInterval);
      res.push_back(cur);
      hasInserted = true;
    }
    else {
      newInterval.start = min(cur.start, newInterval.start);
      newInterval.end = max(cur.end, newInterval.end);
    }
  }

  if (!hasInserted)
    res.push_back(newInterval);

  return res;
}