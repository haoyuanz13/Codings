#include <vector>
#include <queue>
#include <iostream>
#include <algorithm>
// #include <functional>

using namespace std;

// define a new strcuture edge 
struct Edge
{
  int from, to, weight;
  
  Edge(int w): weight(w), from(0), to(0) {}

  // define operator that compare based on weight
  // the naturally one which is the deflaut comparator operation 
  bool operator<(Edge other) const
  {
    return weight > other.weight;
  }
};

// define a comp function by users based on the requirements
bool cmp (Edge& a, Edge& b) {
  return a.weight < b.weight;
}

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

// max and min heap to find the median
float findMedian(vector<float> nums) {
  if (nums.empty() || nums.size() == 0) {
    cout << "ERROR: The input is invalid." << endl;
    return 0.0;
  }

  // create a max heap for the first half
  priority_queue<float, vector<float>, myComparison> max_heap;
  // create a min heap for the second half
  priority_queue<float, vector<float>, myComparison> min_heap (myComparison(true));

  for (int i = 0; i < nums.size(); i ++) {
    float cur = nums[i];
    max_heap.push(cur);
    min_heap.push(max_heap.top());
    max_heap.pop();

    // keep the size of max_heap larger than min heap
    if (max_heap.size() < min_heap.size()) {
      max_heap.push(min_heap.top());
      min_heap.pop();
    }
  }

  // even case
  if ( max_heap.size() == min_heap.size() )
    return (max_heap.top() + min_heap.top()) / 2;
  else
    return max_heap.top();

}


int main() {
  vector<float> vv = {3.0, 2.1, 1, 4, 5, 3.8, 7};
  cout << findMedian(vv) << endl;

  // priority_queue<int, vector<int>, myComparison> v(myComparison(true));
  // for (int i = 10; i >= 0; i --)
  //   v.push(i);

  // while (!v.empty()) {
  //   cout << v.top() << endl;
  //   v.pop();
  // }


  // Edge e1(10);
  // Edge e2(11);
  // Edge e3(2);
  // Edge e4(7);

  // vector<Edge> vv;

  // vv.push_back(e2);
  // vv.push_back(e3);
  // vv.push_back(e1);
  // vv.push_back(e4);

  // // sort(vv.begin(), vv.end(), cmp);
  // sort (vv.begin(), vv.end());

  // for (int i = 0; i < vv.size(); i ++) {
  //   cout << vv.at(i).weight << endl;
  // }

  // priority_queue<Edge> v;

  // Edge e1(10);
  // Edge e2(11);
  // Edge e3(2);
  // Edge e4(7);

  // v.push(e2);
  // v.push(e3);
  // v.push(e1);
  // v.push(e4);

  // // sort<v.begin(), v.begin() + 4>;
  // while (!v.empty()) {
  //   cout << v.top().weight << endl;
  //   v.pop();
  // }


  return 0;

}