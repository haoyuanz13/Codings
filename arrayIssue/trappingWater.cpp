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


int main(int argc, char** argv) {
  vector<int> walls {0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};
   

}
