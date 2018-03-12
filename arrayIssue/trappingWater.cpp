#include <vector>
#include <iostream>

using namespace std;

// the trapping water problem 

// Leetcode 11: Container with most water
// two pointer approach
int maxArea(vector<int>& height) {
  int num_wall = height.size();
  if (num_wall < 2)
    return 0;
  
  int lp = 0, rp = num_wall - 1;
  int max_area = 0;
  
  while (lp < rp) {
    int width = rp - lp;
    int pivot = (height[lp] < height[rp])? height[lp] : height[rp];
    
    // update max area if necessary
    int cur_area = pivot * width;
    max_area = (max_area < cur_area)? cur_area : max_area;
    
    if (height[lp] > height[rp])
      rp --;
    else
      lp ++;
  }

  return max_area;
}


// Leetcode 42: Trapping Rain Water (2D)
// - method 1: two pointers, count storage once meet shorter wall
int trap_1(vector<int>& height) {
  int num_wall = height.size();
  if (num_wall < 3)
    return 0;

  int lp = 0, rp = num_wall - 1;
  int storage = 0;
  
  int l_w = height[lp], r_w = height[rp];
  while (lp < rp) {
    if (l_w < r_w) {
      lp ++;
      if (l_w > height[lp])
        storage += l_w - height[lp];
      else
        l_w = height[lp];
	
    }
    
    else {
      rp --;
      if (r_w > height[rp])
        storage += r_w - height[rp];
      else
        r_w = height[rp];  
    }

  }
  return storage;

}

// - method 2: two times traversing (left->right, right->left)
int trap(vector<int>& height) {
  int num_wall = height.size();
  if (num_wall < 3)
    return 0;
  
  // create left and right bar array
  vector<int> left_bar;
  left_bar.reserve(num_wall);

  vector<int> right_bar;
  right_bar.reserve(num_wall);

  // compute left highest bar at each wall
  int pivot = height[0];
  left_bar[0] = 0;  // since the front one has no left neighbor
  for (int i = 0; i < num_wall; i ++) {
    left_bar[i] = pivot;
    pivot = (pivot < height[i])? height[i] : pivot;
  }

  // compute left highest bar at each wall
  pivot = height.back();
  left_bar.back() = 0;  // since the back one has no righter neighbor
  for (int i = num_wall - 1; i >= 0; i --) {
    right_bar[i] = pivot;
    pivot = (pivot < height[i])? height[i] : pivot;
  }

  // traverse each wall position to obtain the most trapped water
  int storage = 0;
  for (int i = 0; i < num_wall; i ++) {
    int cur_w = height[i];
    if (cur_w >= left_bar[i] || cur_w >= right_bar[i])
      continue;
    
    int pivot_bar = (left_bar[i] < right_bar[i])? left_bar[i] : right_bar[i];
    storage += pivot_bar - cur_w;
  }

  return storage;

} 


 





