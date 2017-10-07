#include <vector>
#include <queue>
#include <map>
#include <iostream>

using namespace std;

struct mynode 
{
  int val, freq;
  mynode(int v, int f): val(v), freq(f) {}
};


struct myComp
{
  bool ascending;
  myComp(const bool &ascend = false){
    ascending = ascend;
  }

  bool operator() (const mynode* a, const mynode* b) const {
    if (ascending)
      return (a->freq) > (b->freq);
    else
      return (a->freq) < (b->freq);
  }
  
};

// frequency sort
void freqSort(vector<int>& nums) {
  if (nums.empty() || nums.size() < 2)
    return;

  priority_queue<mynode, vector<mynode*>, myComp> node_vec(true);
  map<int, mynode*> hash;

  int len = nums.size();
  for (int i = 0; i < len; i ++) {
    int cur = nums[i];
    if (hash.count(cur) > 0)
      hash[cur]->freq ++;
    else {
      mynode* newele = new mynode(cur, 1);
      hash[cur] = newele;
    }
  }

  for (map<int, mynode*>::iterator it = hash.begin(); it != hash.end(); it ++) {
    node_vec.push(it->second);
  }

  vector<int> res;
  while (!node_vec.empty()) {
    res.push_back(node_vec.top()->val);

    cout << "the val is: " << node_vec.top()->val << " and the freq is: " << node_vec.top()->freq << endl;
    node_vec.pop();
  }

  for (int i = 0; i < res.size(); i ++)
    cout << res[i] << " ";
  cout << "\n";

  // return res;
}


int main () {
  vector<int> nums {1, 1, 2, 2, 1, 1, 4, 4, 2, 2, 5, 3, 3, 2};
  // vector<int> res = freqSort(nums);
  freqSort(nums);

  // for (int i = 0; i < res.size(); i ++)
  //   cout << res[i] << " ";
  // cout << "\n";

}

