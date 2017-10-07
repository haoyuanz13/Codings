#include <vector>
#include <iostream>

using namespace std;

// partition extracts idea from quick sort
// good tool to find kth largest or smallest element
void swapEle(vector<int>& nums, int id1, int id2) {
  int temp = nums[id1];
  nums[id1] = nums[id2];
  nums[id2] = temp;
  return;
}

// find the order index of the last element in the vetcor using partition
int findOrder(vector<int>& nums, int start, int end) {
  int pivot = nums[end];

  int l = start, r = end - 1;
  while (l < r) {
    while (l < r && nums[l] < pivot)
      l ++;
    while (l < r && nums[r] >= pivot)
      r --;

    swapEle(nums, l, r);
  }

  if (nums[l] >= pivot)
    swapEle(nums, l, end);
  else
    l ++;

  return l;
}

int KthLargest(vector<int> nums, int K) {
  K = nums.size() - K;
  int l = 0, r = nums.size() - 1;
  int pos = 0;

  while (l < r) {
    pos = findOrder(nums, l, r);

    if (pos == K)
      break;
    else if (pos < K)
      l = pos + 1;
    else
      r = pos - 1;
  }

  return nums[K];
}


// partition
void partition(vector<int>& arr, int left, int right) {
  if (left >= right)
    return;

  int l = left, r = right;
  int pivot = arr[left];

  while (l < r) {
    while (l < r && arr[r] >= pivot)
      r --;
    arr[l] = arr[r];

    while (l < r && arr[l] <= pivot)
      l ++;
    arr[r] = arr[l];
  }

  arr[l] = pivot;

  partition(arr, left, l - 1);
  partition(arr, l + 1, right);

  return;
}

// quick sort
void quickSort(vector<int>& arr) {
  partition(arr, 0, arr.size() - 1);
  return;
}
int main(int argc, char** argv) {
  vector<int> nums {3, 2, 1, 5, 6, 4};
  quickSort(nums);

  for (vector<int>::iterator it = nums.begin(); it != nums.end(); it ++)
    cout << *it << ", ";

}