//============================================================================
// Name        : Binary Search.cpp
// Time		   : O(log n)
// Author      : Iván Galbán Smith
// Version     : 3.1415926535897932384626433832795
// Copyright   : All rights reserved
// Description : Structure Disjoint Set union by cont
//============================================================================

#include <bits/stdc++.h>
using namespace std;

int bin(vector<int> &arr, int n) {
  int lo = 0, hi = 17;
  while (lo <= hi) {
    int mid = (lo + hi) / 2;
    if (arr[mid] < n)
      lo = mid + 1;
    else
      hi = mid - 1;
  }
  return lo;
}

int main() {

  int array[] = {2,  3,  5,  7,  7,  7,  11, 13, 17,
                 19, 23, 29, 31, 37, 41, 43, 47, 49};
  vector<int> arr(array, array + 18);

  int n;
  cin >> n;
  cout << "Lower Bound " << lower_bound(arr.begin(), arr.end(), n) - arr.begin()
       << endl;
  cout << "Upper Bound " << upper_bound(arr.begin(), arr.end(), n) - arr.begin()
       << endl;
  cout << "My " << bin(arr, n) << endl;

  return 0;
}
