int oo = (1 << 30);
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

// O(1)
int parent(int i) { return (i - 1) / 2; }

// O(log n)
void max_heapyfiUp(int *A, int i) {
  while (i >= 0 && A[i] > A[parent(i)]) {
    swap(A[i], A[parent(i)]);
    i = parent(i);
  }
}

// O(n)
void build_max_heap(int *A) {
  heap_size = N;
  for (int i = N / 2; i >= 0; --i)
    max_heapyfi(A, i);
}

// O(1)
int max_heap(int *A) { return A[0]; }

// O(log n)
int heap_extract_max(int *A) {
  if (heap_size < 1)
    return oo;

  int max = A[0];

  swap(A[0], A[heap_size - 1]);
  --heap_size;

  max_heapyfi(A, 0);

  return max;
}

// O(log n)
void heap_increase_key(int *A, int i, int key) {
  if (key <= A[i])
    return;

  A[i] = key;
  max_heapyfiUp(A, i);
}
