#include <vector>
#include <queue>
#include <iostream>
#include <algorithm>

using namespace std;

/*
 Round Robin problem
 A system needs to deal with a list of processes, the max operation time for each single 
 process is q, if cannot finish, put the rest of process at the tail of the queue.
 Compute the efficiency: wait time / total process numbers 
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

double roundRobin(vector<int>& arrTimes, vector<int>& exeTimes, int q) {
  if (arrTimes.empty() || exeTimes.empty() || arrTimes.size() != exeTimes.size())
    return 0.0;

  int length = arrTimes.size();
  queue<process*> que;

  int cur_time = 0;
  double wait_time = 0;
  int ind = 0;

  while (!que.empty() || ind < length) {
    if (!que.empty()) {
      process* cur = que.front();
      wait_time += cur_time - cur->arrTime;

      // the max exe time is q
      cur_time += min(cur->exeTime, q);

      for (ind < length && arrTimes[ind] <= cur_time; ind ++) {
        process* n = new process(arrTimes[ind], exeTimes[ind]);
        que.push(n);
      }

      if (cur->exeTime > q) {
        process* n = new process(cur_time, cur->exeTime - q);
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
