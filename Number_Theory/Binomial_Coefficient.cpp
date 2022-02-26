/*
    CALCULA COMBINATORIA DE n en k
    USANDO EL TRIANGULO DE PASCAL
*/
#include <cstdio>
#include <iostream>

#define MAX 10000

using namespace std;

int C[MAX][MAX];

void Pascal(int level) {
  for (int n = 0; n <= level; ++n) {
    C[n][0] = C[n][n] = 1;
    for (int k = 1; k < n; ++k)
      C[n][k] = C[n - 1][k] + C[n - 1][k - 1];
  }
}

int main() {
  int n, k;
  cin >> n >> k;
  Pascal(n);
  cout << C[n][k];

  return 0;
}
