#include <vector>
#include <iostream>

using namespace std;


// merge operation
void merge(vector<int>& nums, vector<int>& temp, int left, int mid, int right) {
  int s1 = left, e1 = mid;
  int s2 = mid + 1, e2 = right;
  int newlen = 0;

  while (s1 <= e1 && s2 <= e2) {
    if (nums[s1] < nums[s2])
      temp[newlen ++] = nums[s1 ++];
    else
      temp[newlen ++] = nums[s2 ++];
  }

  while (s1 <= e1)
    temp[newlen ++] = nums[s1 ++];
  while (s2 <= e2)
    temp[newlen ++] = nums[s2 ++];

  for (int i = 0; i < newlen; i ++)
    nums[left + i] = temp[i];

  return;
}

// divide the original array layer by layer until the min size which is 2
void divideMerge(vector<int>& nums, vector<int>& temp, int left, int right) {
  if (left == right)
    return;

  int mid = (left + right) / 2;
  
  divideMerge(nums, temp, left, mid);
  divideMerge(nums, temp, mid + 1, right);

  merge(nums, temp, left, mid, right);

  return;
}

// recursive
void mergeSort(vector<int>& nums) {
  if (nums.empty() || nums.size() < 2)
    return;

  vector<int> temp;
  temp.reserve(nums.size());

  divideMerge(nums, temp, 0, nums.size() - 1);
  return;
}

// merge sort includes dividing and merging two steps
int main() {
  vector<int> nums {3, 7, 8, 5, 2, 1, 9, 5, 4, 6, -2, 4, 1};

  mergeSort(nums);

  for (int i = 0; i < nums.size(); i ++)
    cout << nums[i] << " ";
  cout << endl;
}