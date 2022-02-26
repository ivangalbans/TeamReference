/*
    Computing all subset of subset.
    Time: 3^n
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
  int N = 4;
  for (int i = 0; i < (1 << N); ++i) {
    bitset<8> n(i);
    cout << "MASK: " << n << endl;
    cout << "SUBMASK:" << endl;
    for (int j = i; j; j = (j - 1) & i) {
      bitset<8> p(j);
      cout << p << endl;
    }
    cout << endl;
  }
  return 0;
}
