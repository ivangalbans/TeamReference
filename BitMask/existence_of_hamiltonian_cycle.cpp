/*
        task:        Check for existence of Hamiltonian cycle in a
                     directed graph G = <V, E>.
        complexity:  O(2^n * n)
        notes:       Let dp[msk] be the mask of the subset consisting
                     of those vertices j such that exist a
   Hamiltonian walk over the subset msk beginning in vertex 0 and ending in j.
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

  dp[1] = 1;

  for (int msk = 2; msk < BIT(n); ++msk) {
    for (int i = 0; i < n; ++i) {
      if ((msk & BIT(i)) && (dp[msk ^ BIT(i)] & g[i]))
        dp[msk] |= BIT(i);
    }
  }

  cout << ((dp[BIT(n) - 1] & g[0]) != 0) << endl;
  return 0;
}
