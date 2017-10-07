#include <string>
#include <cstring>
#include <iostream>
#include <vector>

using namespace std;


// reverse certain string
void reverse(vector<char>& arr, int start, int end) {
  while (start < end) {
    char temp = arr[start];
    arr[start ++] = arr[end];
    arr[end --] = temp;
  }
  return;
}

// reverse words in the string
void reverseWord(vector<char>& arr, int len) {
  int l = 0, r = 0;
  while (r < len) {
    while (l < len && arr[l] == ' ')
      l ++;

    r = l;

    while (r < len && arr[r] != ' ')
      r ++;

    reverse(arr, l, r - 1);
    l = r;
  }
  return;

}

// clean up white space
string cleanUp(vector<char>& arr, int len) {
  int l = 0, r = 0;
  while (r < len && arr[r] == ' ')
    r ++;

  while (r < len) {
    while (r < len && arr[r] != ' ')
      arr[l ++] = arr[r ++];

    while (r < len && arr[r] == ' ')
      r ++;

    if (r < len)
      arr[l ++] = ' ';
  }

  string res(arr.begin(), arr.begin() + l);
  return res;
}

// reverse the word string
string reverseStrs(string& str) {
  if (str.empty() || str.size() == 0)
    return str;

  int len = str.size();
  // convert string to char array
  char str_arr [len];
  strcpy(str_arr, str.c_str());

  vector<char> str_vec(str_arr, str_arr + len);

  // reverse the string function
  reverse(str_vec, 0, len - 1);

  // reverse each word in the string
  reverseWord(str_vec, len);

  // clean up white space
  string res = cleanUp(str_vec, len);

  return res;
}

int main() {
  string input = "the sky is   blue";
  cout << reverseStrs(input) << endl;
}