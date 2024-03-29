/*
        task:           Finding the number of simple cycles in a
                        directed graph G = <V, E>.

        complexity:     O(2^n * n^2)

        notes:          Let dp[msk][v] be the number of Hamiltonian
                        walks in the subgraph generated by vertices
                        in msk that begin in the lowest vertex in
                        msk and end in vertex v.
*/

#define BIT(n) (1 << n)
#define ONES(n) __builtin_popcount(n)

const int MAXN = 20;

int n, m, u, v, g[MAXN];
long long dp[BIT(MAXN)][MAXN], ans;

int main() {
  cin >> n >> m;

  for (int i = 0; i < m; ++i) {
    cin >> u >> v;
    g[u] |= BIT(v);
  }

  for (int i = 0; i < n; ++i)
    dp[BIT(i)][i] = 1;

  for (int msk = 1; msk < BIT(n); ++msk) {
    for (int i = 0; i < n; ++i) {
      if ((msk & BIT(i)) && !(msk & -msk & BIT(i))) {
        int tmsk = msk ^ BIT(i);

        for (int j = 0; tmsk && j < n; ++j)
          if (g[j] & BIT(i))
            dp[msk][i] += dp[tmsk][j];

        if (ONES(msk) > 2 && (g[i] & msk & -msk))
          ans += dp[msk][i];
      }
    }
  }
  cout << ans << endl;
  return 0;
}
