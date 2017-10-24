#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

// insert sort
void insertSort(vector<int>& nums) {
  if (nums.empty() || nums.size() < 2)
    return;

  for (int i = 1; i < nums.size(); i ++) {
    int temp = nums[i];
    int j = i - 1;

    while (j >= 0) {
      if (nums[j] > temp)
        nums[j + 1] = nums[j];
      else
        break;

      j --;
    }

    nums[j + 1] = temp;
  }
  return;
}

// use binary search to get the insert position
void insertSortBS(vector<int>& nums) {
  if (nums.empty() || nums.size() < 2)
    return;

  for (int i = 1; i < nums.size(); i ++) {
    int temp = nums[i];
    int left = 0, right = i - 1;

    while (left < right) {
      int mid = left + (right - left) / 2;

      if (nums[mid] <= temp)
        left = mid + 1;
      else
        right = mid;
    }

    left = (nums[left] > temp)? left : left + 1;

    int start = i;
    while (start > left) {
      nums[start] = nums[start - 1];
      start --;
    }

    nums[left] = temp;
  }

  return;
}

// select sort: get the smallest element then put into the headest position
void selectSort(vector<int>& nums) {
  if (nums.empty() || nums.size() < 2)
    return;

  for (int i = 0; i < nums.size(); i ++) {
    int ind_min = i;
    for (int j = i + 1; j < nums.size(); j ++) {
      if (nums[j] < nums[ind_min])
        ind_min = j;
    }

    // swap
    int temp = nums[ind_min];
    nums[ind_min] = nums[i];
    nums[i] = temp;
  }

  return;

}

// bubble sort: start from the end of array
// swap towards if current element is smaller than previous one
void bubbleSort(vector<int>& nums) {
  if (nums.empty() || nums.size() < 2)
    return;

  for (int i = 0; i < nums.size(); i ++) {
    for (int j = nums.size() - 1; j > i; j --) {
      if (nums[j] < nums[j - 1]) {
        int temp = nums[j];
        nums[j] = nums[j - 1];
        nums[j - 1] = temp;
      }  // end if
    }  // end inner for
  }  // end outer for

  return;
}


int main() {
  vector<int> nums {2, 1, 10, 4, 3, 10, 5};
  bubbleSort(nums);

  for (int i = 0; i < nums.size(); i ++) 
    cout << nums[i] << ", ";
  cout << "\n";

}