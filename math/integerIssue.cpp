#include <vector>
#include <iostream>
#include <limits>

using namespace std;

// math algroithm applied in the integer problems

// reverse integer
int reverse(int x) {
  long res = 0;
  while (x != 0) {
    res = res * 10 + x % 10;
    x /= 10;

    // check whether overflow
    if (res > numeric_limits<int>::max() || res < numeric_limits<int>::min())
      return 0;
  }

  return (int)res;
}


// palindrome number
// ddetermine an integer is a palindrome or not
// not to convert integer to string
bool isPalindrome(int x) {
  if (x < 0 || (x != 0 && x % 10 == 0))
    return false;

  int rev = 0;
  while (x > rev) {
    rev = rev * 10 + x % 10;
    x /= 10;
  }

  return (x == rev || x == rev / 10);
}

// reverse bits
// uint is a type that cannot store negative types but can store twice longer of int
// uint32: 0 to 4294967295
uint32_t reverseBits_1(uint32_t n) {
  uint32_t res = 0;
  for (int i = 0; i < 32; i ++) {
    res = (res << 1) + (n & 1);
    n >>= 1;
  }
  return res;
}

// optimal solution: deque method
// swap 2 neighbors first, then 4, then 8, and so on
uint32_t reverseBits(uint32_t n) {
  n = (n >> 16) | (n << 16);
  n = ((n & 0xff00ff00) >> 8) | ((n & 0x00ff00ff) << 8);
  n = ((n & 0xf0f0f0f0) >> 4) | ((n & 0x0f0f0f0f) << 4);
  n = ((n & 0xcccccccc) >> 2) | ((n & 0x33333333) << 2);
  n = ((n & 0xaaaaaaaa) >> 1) | ((n & 0x55555555) << 1);
  return n;
}