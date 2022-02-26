/*
        Start in 0.
        TASK  : Range Minimum Query Problem: Given a sequence S of real numbers,
                RMQ(i,j) returns the index of element in S[i...j] with
                smallest value.

        Preprocess Sparse Table --> O(N log N)
        Answer query            --> O(1)
*/

// Tested 1651 - Finding Minimum COJ
//	  	  1082 - Array Queries Lightoj

const int Max = 10005, MaxLog = 15;

int N;
int rmq[Max][MaxLog], array[Max];

void build() {
  for (int i = 0; i < N; ++i)
    rmq[i][0] = i;
  for (int i = 1; (1 << i) <= N; ++i)
    for (int j = 0; j + (1 << i) <= N; ++j) {
      if (array[rmq[j][i - 1]] < array[rmq[j + (1 << (i - 1))][i - 1]])
        rmq[j][i] = rmq[j][i - 1];
      else
        rmq[j][i] = rmq[j + (1 << (i - 1))][i - 1];
    }
}

int query(int l, int r) {
  int k = __lg(r - l + 1);
  return array[rmq[l][k]] < array[rmq[r - (1 << k) + 1][k]]
             ? rmq[l][k]
             : rmq[r - (1 << k) + 1][k];
}
