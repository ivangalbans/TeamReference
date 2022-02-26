/*
 *   Performance:
 *   0-based
 *   To start the index on 1
 *   lowbit  --> O(1)
 *   query  --> O( log (N+M) )
 *   update --> O( log (N+M) )
 */

// Tested 1904 - Again Making Queries III COJ
#define MOD 10000
#define MaxN 4005
int N, U, Q;
int ft[MaxN][MaxN];

int lowbit(int x) { return x & -x; }

bool Valid(int r, int c) {
  if (r < 1 || r > N)
    return false;
  if (c < 1 || c > N)
    return false;
  return true;
}
void update(int r, int c, int val) {
  if (!Valid(r, c))
    return;
  for (int i = r; i <= N; i += lowbit(i))
    for (int j = c; j <= N; j += lowbit(j))
      ft[i][j] += val;
}

int query(int r, int c) {
  if (!Valid(r, c))
    return 0;
  int sum = 0;
  for (int i = r; i > 0; i -= lowbit(i))
    for (int j = c; j > 0; j -= lowbit(j))
      sum += ft[i][j];
  return sum;
}
int query(int r, int c, int R, int C) {
  return query(R, C) - query(R, c - 1) - query(r - 1, C) + query(r - 1, c - 1);
}
