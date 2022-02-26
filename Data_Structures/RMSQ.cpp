/*
          TASK  : Range Minimum-Sum Segment Query Problem
                  With two intervals too.

          Compute arrays C, P and M --> O(N)
          Preprocess RMQ            --> O(N log N)
          Answer RMSQ queries       --> O(1)
*/
#define MAXN 50005
#define LGN 16

int A[MAXN];
int C[MAXN], P[MAXN], M[MAXN], L[MAXN];
int RMQ[MAXN][LGN][2];

// for two intervals
int rmqMAXC[MAXN][LGN];

int N;

// Compute arrays C, P, L and M
// C[i] = sum(A[1]...A[i])
// L[i] = max{k | C[k] >= C[i] k[1, i-1]}
//			{0 			    otherwise  }
// P[i] = max{k | k[L[i]+1, i] and C[k-1] <= C[l] forall l[L[i], i-1]}
// M[i] = sum(P[i], i)
void buildCLPM() {
  for (int i = 1; i <= N; ++i) {
    C[i] = C[i - 1] + A[i];
    L[i] = i - 1;
    P[i] = i;
    while (C[L[i]] < C[i] && L[i]) {
      if (C[P[L[i]] - 1] < C[P[i] - 1])
        P[i] = P[L[i]];
      L[i] = L[L[i]];
    }
    M[i] = C[i] - C[P[i] - 1];
  }
}

// Preprocess array C for RMQmin and array M for RMQmax
// RMQ[i][j][0] holds the minimum, while RMQ[i][j][1] holds
// the maximum
void buildRMQ() {
  for (int i = 0; i <= N; ++i)
    RMQ[i][0][0] = RMQ[i][0][1] = i;

  for (int j = 1; j <= __lg(N + 1); ++j)
    for (int i = 0; i + (1 << j) - 1 <= N + 1; ++i) {
      if (C[RMQ[i][j - 1][0]] <= C[RMQ[i + (1 << (j - 1))][j - 1][0]])
        RMQ[i][j][0] = RMQ[i][j - 1][0];
      else
        RMQ[i][j][0] = RMQ[i + (1 << (j - 1))][j - 1][0];
      if (M[RMQ[i][j - 1][1]] >= M[RMQ[i + (1 << (j - 1))][j - 1][1]])
        RMQ[i][j][1] = RMQ[i][j - 1][1];
      else
        RMQ[i][j][1] = RMQ[i + (1 << (j - 1))][j - 1][1];
    }
}

int queryRMQ(int l, int r, int b) {

  int k = __lg(r - l + 1);

  // For two Intervals
  if (b == 2)
    return max(rmqMAXC[l][k], rmqMAXC[r - (1 << k) + 1][k]);

  if (!b)
    return C[RMQ[l][k][b]] <= C[RMQ[r - (1 << k) + 1][k][b]]
               ? RMQ[l][k][b]
               : RMQ[r - (1 << k) + 1][k][b];
  else
    return M[RMQ[l][k][b]] >= M[RMQ[r - (1 << k) + 1][k][b]]
               ? RMQ[l][k][b]
               : RMQ[r - (1 << k) + 1][k][b];
}

pair<int, int> queryRMSQ(int l, int r) {
  int x = queryRMQ(l, r, 1);
  if (P[x] < l) {
    int y = queryRMQ(x + 1, r, 1);
    int z = queryRMQ(l - 1, x - 1, 0) + 1;
    if (C[x] - C[z - 1] < M[y])
      return pair<int, int>(P[y], y);
    return pair<int, int>(z, x);
  }
  return pair<int, int>(P[x], x);
}

// RMSQ with two intervals
// Return i <= x <= j, k <= y <= l
//  max{ Sum(x, y) }

void buildRMSQ2() {
  // Apply RMSQ preprocessing to A
  // Apply RMQmin and RMQmax preprocessing to C[]
  for (int i = 0; i <= N; ++i)
    rmqMAXC[i][0] = i;
  for (int j = 1; j <= __lg(N + 1); ++j)
    for (int i = 0; i + (1 << j) - 1 <= N + 1; ++i) {
      if (C[rmqMAXC[i][j - 1]] >= C[rmqMAXC[i + (1 << (j - 1))][j - 1]])
        rmqMAXC[i][j] = rmqMAXC[i][j - 1];
      else
        rmqMAXC[i][j] = rmqMAXC[i + (1 << (j - 1))][j - 1];
    }
}

pair<int, int> queryRMSQ(int i, int j, int k, int l) {
  if (j <= k)
    return pair<int, int>(queryRMQ(i - 1, j - 1, 0) + 1, queryRMQ(k, l, 2));

  int x[4], y[4];

  x[1] = queryRMQ(i - 1, k - 1, 0) + 1;
  y[1] = queryRMQ(k, l, 2);

  x[2] = queryRMQ(k, j - 1, 0) + 1;
  y[2] = queryRMQ(j, l, 2);

  pair<int, int> tmp = queryRMSQ(k, j);
  x[3] = tmp.first;
  y[3] = tmp.second;

  int maxSum = max(C[x[1]] - C[y[1] - 1],
                   max(C[x[2]] - C[y[2] - 1], C[x[3]] - C[y[3] - 1]));

  if (C[x[1]] - C[y[1] - 1] == maxSum)
    return pair<int, int>(x[1], y[1]);
  if (C[x[2]] - C[y[2] - 1] == maxSum)
    return pair<int, int>(x[2], y[2]);
  return pair<int, int>(x[3], y[3]);
}

int main() {

  cin >> N;
  for (int i = 1; i <= N; ++i)
    cin >> A[i];

  buildCLPM();
  buildRMQ();
  buildRMSQ2();

  int q;
  cin >> q;
  for (int i = 0; i < q; ++i) {
    /*int l, r;	cin >> l >> r;
    pair<int, int> ans = queryRMSQ(l, r);
    cout << ans.first << " " << ans.second << endl;*/
    int a, b, c, d;
    cin >> a >> b >> c >> d;
    pair<int, int> ans = queryRMSQ(a, b, c, d);
    cout << ans.first << " " << ans.second << endl;
  }
  return 0;
}
