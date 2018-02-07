#include <iostream>
#include <vector>
using namespace std;

/*
 * Binary search for rotated array, sorted array equals to the binary search
 * Left and right pointers, deal with two cases
 * Two cases, with or without duplicates.
 */

// find index in array of target element, without duplicates
int searchNoDup(vector<int>& nums, int target){
  // int len_nums = (sizeof(nums) / sizeof(int));
  int len_nums = nums.size();

  int left = 0, right = len_nums - 1;
  int mid;

  while (left < right) {
    mid = left + (right - left) / 2;
    if (nums[mid] == target)
      return mid;

    else if (nums[mid] < nums[right]) {
      if (target > nums[mid] && target <= nums[right])
        left = mid + 1;
      else
        right = mid - 1;
    }

    else {
      if (target >= nums[left] && target < nums[mid])
        right = mid - 1;
      else
        left = mid + 1;
    }
  }

  return (nums[left] == target)? left : -1;
}

// find index in array of target element, with duplicates
bool searchWithDup(vector<int>& nums, int target){
  int len_nums = nums.size();

  int l = 0, r = len_nums - 1;
  int m;

  while (l < r) {
    m = l + (r - l) / 2;
    if (nums[m] == target)
      return true;

    else if (nums[m] < nums[r]) {
      if (target > nums[m] && target <= nums[r])
        l = m + 1;
      else
        r = m - 1;
    }

    else if (nums[m] > nums[r]) {
      if (target >= nums[l] && target < nums[m])
        r = m - 1;
      else
        l = m + 1;
    }

    // nums[m] == nums[r]
    else { 
      // the special case that cannot drop either half part
      if (nums[l] == nums[m]) {
        l ++;
        r --;
      } else {
        r = m - 1;
      }

    }
  }

  return nums[l] == target;
}

// main code to call the function
int main(int argv, char** agrc){
  int a [] = {6, 7, 7, 9, 1, 1, 2, 3};
  vector<int> nums (a, a + sizeof(a) / sizeof(int));
  int target = 10;

  // int res = searchNoDup(nums, target); 
  bool hasEle = searchWithDup(nums, target);
  cout << hasEle << endl;

  return 0;
}
