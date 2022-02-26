/*
        task:           Check for existence of Hamiltonian walk in the
                        directed graph G = <V, E>.

        complexity:     O(2^n * n)

        notes:          Let dp[msk] be the mask of the subset consisting
                        of those vertices v for which exist a
   Hamiltonian walk over the subset msk ending in v.
*/

#define BIT(n) (1 << n)
const int MAXN = 20;

int n, m, u, v, g[MAXN], dp[BIT(MAXN)];

int main() {
  cin >> n >> m;

  for (int i = 0; i < m; ++i) {
    cin >> u >> v;
    g[v] |= BIT(u);
  }

  for (int i = 0; i < n; ++i)
    dp[BIT(i)] = BIT(i);

  for (int msk = 1; msk < BIT(n); ++msk) {
    for (int i = 0; i < n; ++i) {
      if ((msk & BIT(i)) && (dp[msk ^ BIT(i)] & g[i]))
        dp[msk] |= BIT(i);
    }
  }

  cout << (dp[BIT(n) - 1] != 0) << endl;
  return 0;
}
