/*
                RMQ with SQRT descomposition
                Proprocesing -> O( n )
                Queries      -> O( sqrt( n ) )
                Memory       -> O( n )
 */
// 1651 - Finding Minimum COJ

const int MaxN = 10000, sqrtN = 101, oo = (1 << 30);
int N;
int array[MaxN];
int rmq[sqrtN];
int root;

void build() {
  root = 1;
  while (root * root < N)
    ++root;

  for (int i = 0; i * root < N; i++) {
    rmq[i] = array[i * root];
    for (int j = 1; j < root && i * root + j < N; j++)
      rmq[i] = min(rmq[i], array[i * root + j]);
  }
}

int query(int l, int r) {
  int ans = oo;
  int lo = l / root;
  int hi = r / root;

  if (lo == hi) {
    for (int i = l; i <= r; ++i)
      ans = min(ans, array[i]);
  } else {
    // pedazos enteros del centro
    for (int i = lo + 1; i <= hi - 1; i++)
      ans = min(ans, rmq[i]);

    // pedacito izquierda
    for (int i = l; i < (lo + 1) * root; i++)
      ans = min(ans, array[i]);

    // pedacito derecha
    for (int i = hi * root; i <= r; i++)
      ans = min(ans, array[i]);
  }

  return ans;
}
