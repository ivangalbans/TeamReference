const int oo = 1 << 30;

int matrix_chain(const vector<int> &p) {
  int n = p.size() - 1;
  int dp[n + 1][n + 1];

  for (int i = 1; i <= n; ++i)
    dp[i][i] = 0;

  for (int len = 2; len <= n; ++len) {
    for (int i = 1, j = i + len - 1; j <= n; ++i, ++j) {
      dp[i][j] = oo;
      for (int k = i; k < j; ++k)
        dp[i][j] =
            min(dp[i][j], dp[i][k] + dp[k + 1][j] + p[i - 1] * p[k] * p[j]);
    }
  }

  return dp[1][n];
}
