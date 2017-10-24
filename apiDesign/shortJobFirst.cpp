#include <vector>
#include <queue>
#include <iostream>
#include <algorithm>

using namespace std;

/*
 The shorted Job First structure
 The difference is: 
 - 1. no constraint operation time;
 - 2. execute shorted process first, if tied, earlier arrival time first.
*/

struct process
{
  int arrTime;
  int exeTime;

  process(int at, int et) {
    arrTime = at;
    exeTime = et;
  }
  
};

struct myComp
{
  bool ascending;

  myComp(const bool& asd) {
    ascending = asd;
  }

  bool operator() (const process* a, const process* b) {
    if (a->exeTime == b->exeTime)
      return (a->arrTime) > (b->arrTime);
    else
      return (a->exeTime) > (b->exeTime);
  }
  
};

double shortedJobFirst(vector<int>& arrTimes, vector<int>& exeTimes) {
  if (arrTimes.empty() || exeTimes.empty() || arrTimes.size() != exeTimes.size())
    return 0.0;

  int length = arrTimes.size();
  priority_queue<process, vector<process*>, myComp> que(true);

  int cur_time = 0;
  double wait_time = 0;
  int ind = 0;

  while (!que.empty() || ind < length) {
    if (!que.empty()) {
      process* cur = que.front();
      que.pop();

      wait_time += cur_time - cur->arrTime;
      cur_time += cur->exeTime;

      for (ind < length && arrTimes[ind] <= cur_time; ind ++) {
        process* n = new process(arrTimes[ind], exeTimes[ind]);
        que.push(n);
      }
    }  // end if

    else {
      process* n = new process(arrTimes[ind], exeTimes[ind]);
      que.push(n);

      cur_time = arrTimes[ind ++];
    }  // end else
  }  // end while

  return wait_time / length;
}
