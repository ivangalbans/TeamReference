//============================================================================
// Name        : Heap_Sort.cpp
// Time		   : O(n*log n)
// Author      : Iván Galbán Smith
// Version     : 3.1415926535897932384626433832795
// Copyright   : All rights reserved
// Description : Sorting
//============================================================================

#include <bits/stdc++.h>
using namespace std;

int N, heap_size;

// O(log n)
void max_heapyfi(int *A, int i) {
  int l, r, largest = i;
  do {
    i = largest;
    l = (i << 1) + 1;
    r = (i << 1) + 2;
    if (l < heap_size && A[l] > A[largest])
      largest = l;
    if (r < heap_size && A[r] > A[largest])
      largest = r;

    swap(A[largest], A[i]);
  } while (largest != i);
}

// O(n)
void build_max_heap(int *A) {
  heap_size = N;
  for (int i = N / 2; i >= 0; --i)
    max_heapyfi(A, i);
}

int main() {
  cout << "N = ";
  cin >> N;

  int A[N];

  for (int i = 0; i < N; ++i) {
    cout << "A[" << i << "] = ";
    cin >> A[i];
  }

  build_max_heap(A);

  // Mostrar max_heap
  for (int i = 0, x = 2; i < N; ++i) {
    cout << A[i] << " ";

    if (i == x - 2) {
      x <<= 1;
      cout << endl;
    } else if (i == N - 1)
      cout << endl;
  }

  // heapsort
  for (int i = N - 1; i >= 0; --i) {
    swap(A[0], A[i]);
    --heap_size;
    max_heapyfi(A, 0);
  }

  // Mostrar arreglo ordenado
  for (int i = 0; i < N; ++i)
    cout << A[i] << " ";
  cout << endl;

  return 0;
}
