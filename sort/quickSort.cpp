#include <vector>
#include <iostream>

using namespace std;

// recursive partition method
void partition(vector<int>& nums, int start, int end) {
  if (start >= end)
    return;

  int l = start, r = end;
  int pivot = nums[l];

  while (l < r) {
    while (l < r && nums[r] >= pivot)
      r --;
    nums[l] = nums[r];

    while (l < r && nums[l] <= pivot)
      l ++;
    nums[r] = nums[l];
  }

  nums[l] = pivot;
  partition(nums, start, l - 1);
  partition(nums, l + 1, end);

  return;
}


// quick sort using partition method
void quickSort(vector<int>& nums) {
  if (nums.empty() || nums.size() < 2)
    return;
  
  // partition approach
  partition(nums, 0, nums.size() - 1);
  return;
}

int main() {
  vector<int> nums {1, 0};

  quickSort(nums);

  for (int i = 0; i < nums.size(); i ++)
    cout << nums[i] << " ";
  cout << endl;
}