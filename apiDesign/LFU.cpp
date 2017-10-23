#include <vector>
#include <iostream>
#include <unordered_map>
#include <queue>


using namespace std;

/*
  Create a data structure to help
  Use a priority queue to store and sort
 */

struct Data
{
  int key;
  int val;
  int timeStamp;
  int freq;

  Data(int k, int v, int t, int f) {
    key = k;
    val = v;
    timeStamp = t;
    freq = f;
  }
  
};

struct myComp
{
  myComp(){};

  bool operator() (const Data* a, const Data* b) const {
    if (a->freq == b->freq)
      return (a->timeStamp) > (b->timeStamp);
    else
      return (a->freq) > (b->freq);
  }
  
};


class LFUCache {
public:
  int timeline;
  priority_queue<Data, vector<Data*>, myComp> que;
  unordered_map<int, Data*> hash;
  int storage;

  LFUCache(int capacity) {
    timeline = 0;
    storage = capacity;      
  }
  
  int get(int key) {
    if (hash.count(key) <= 0 || storage <= 0)
      return -1;
    int res = hash[key]->val;

    increFreq(key, res);
    return res;
  }
  
  void put(int key, int value) {
    if (storage <= 0)
      return;

    // the storage has reached the max capacity
    if (hash.size() == storage && hash.count(key) <= 0) {
      Data* LFU = que.top();
      cout << LFU->key << endl;
      que.pop();
      hash.erase(LFU->key);
    }

    increFreq(key, value);
    return;      
  }

  void increFreq(int key, int value) {
    timeline ++;
    Data* cur;
    if (hash.count(key) <= 0) {
      cur = new Data(key, value, timeline, 0);
    } else {
      cur = hash[key];
      removeInQue(cur);
    }

    cur->val = value;
    cur->timeStamp = timeline;
    cur->freq ++;

    hash[key] = cur;
    que.push(cur);

    return;
  }

  // remove target element in queue
  void removeInQue(Data* target) {
    vector<Data*> temp;

    while (!que.empty()) {
      Data* cur = que.top();
      if (cur->key == target->key && cur->val == target->val 
            && cur->timeStamp == target->timeStamp 
                && cur->freq == target->freq) {
        que.pop();
        break;
      }

      temp.push_back(cur);
      que.pop();

    }

    for (int i = 0; i < temp.size(); i ++)
      que.push(temp[i]);

    return;
  }

  void hashShow() {
    for (auto& x : hash)
      cout << "The key is: " << x.first << " and value is: " << x.second->val << " with freq: " << x.second->freq << endl;
  }

};

/**
 * Your LFUCache object will be instantiated and called as such:
 * LFUCache obj = new LFUCache(capacity);
 * int param_1 = obj.get(key);
 * obj.put(key,value);
 */



int main() {
  LFUCache* obj = new LFUCache(2);
  obj->put(1, 1);
  obj->put(2, 2);
  obj->get(1);
  obj->put(3, 3);
  obj->hashShow();
}