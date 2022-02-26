/*
[TESTED COJ 2536 05/11/2014]
*/
const int MAXN = 110;
const int oo = (1 << 30);
const double EPS = 1e-6;

double a[MAXN][MAXN];
double ans[MAXN];

int n; // ecuations
int m; // variables

void init(int _n, int _m) {
  n = _n;
  m = _m;
  memset(a, 0, sizeof a);
  memset(ans, 0, sizeof ans);
}

int solve() {
  vector<int> where(m, -1);
  for (int col = 0, row = 0; col < m && row < n; ++col) {
    int sel = row;
    for (int i = row; i < n; ++i)
      if (abs(a[i][col]) > abs(a[sel][col]))
        sel = i;

    if (abs(a[sel][col]) < EPS)
      continue;

    for (int i = col; i <= m; ++i)
      swap(a[sel][i], a[row][i]);

    where[col] = row;

    for (int i = 0; i < n; ++i) {
      if (i != row) {
        double c = a[i][col] / a[row][col];
        for (int j = col; j <= m; ++j)
          a[i][j] -= a[row][j] * c;
      }
    }
    ++row;
  }

  for (int i = 0; i < m; ++i)
    if (where[i] != -1)
      ans[i] = a[where[i]][m] / a[where[i]][i];

  for (int i = 0; i < n; ++i) {
    double sum = 0;
    for (int j = 0; j < m; ++j)
      sum += ans[j] * a[i][j];
    if (abs(sum - a[i][m]) > EPS)
      return 0;
  }
  for (int i = 0; i < m; ++i)
    if (where[i] == -1)
      return oo;
  return 1;
}
