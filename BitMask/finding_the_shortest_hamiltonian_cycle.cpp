/*
        task:           Search for the shortest Hamiltonian cycle.
                        Let the directed graph G = (V,
                        E) have n vertices, and each
                        edge have weight d(i, j). We
                        want to find a Hamiltonian cycle for which the sum of
                        weights of its edges is minimal.

        complexity:     O(2^n * n^2)

        notes:          Let dp[msk][v] be the length of the shortest Hamiltonian
                        walk on the subgraph generated
                        by vertices in msk beginning in
   verex 0 and ending in vertex v.
*/

#define BIT(n) (1 << n)

using namespace std;

const int MAXN = 20, INF = 0x1fffffff;

int n, m, u, v, w, g[MAXN][MAXN], dp[BIT(MAXN)][MAXN], ans = INF;

int main() {
  cin >> n >> m;

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j)
      g[i][j] = INF;
  }

  for (int i = 0; i < BIT(n); ++i) {
    for (int j = 0; j < n; ++j)
      dp[i][j] = INF;
  }

  for (int i = 0; i < m; ++i) {
    cin >> u >> v;
    cin >> g[u][v];
  }

  dp[1][0] = 0;

  for (int msk = 2; msk < BIT(n); ++msk) {
    for (int i = 0; i < n; ++i)
      if (msk & BIT(i)) {
        int tmsk = msk ^ BIT(i);

        for (int j = 0; tmsk && j < n; ++j)
          dp[msk][i] = min(dp[msk][i], dp[tmsk][j] + g[j][i]);
      }
  }

  for (int i = 1; i < n; ++i)
    ans = min(ans, dp[BIT(n) - 1][i] + g[i][0]);

  cout << ans << endl;
  return 0;
}
