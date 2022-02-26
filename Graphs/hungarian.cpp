/*
        Maximum assignment (Kuhn-Munkres)

        Description:
        - We are given a cost table of size n times m with n <= m.
        - It finds a maximum cost assignment, i.e.,
                                max sum_{ij} c(i,j) x(i,j)
                where   sum_{i in [n]} x(i,j) = 1,
                                sum_{j in [n]} x(i,j) <= 1.

        Complexity: O(n^3)

        Tested: http://www.spoj.com/problems/SCITIES/
*/

template <typename T> T max_assignment(const vector<vector<T>> &a) {
  int n = a.size(), m = a[0].size();
  assert(n <= m);

  vector<int> x(n, -1), y(m, -1);
  vector<T> px(n, numeric_limits<T>::min()), py(m, 0);

  for (int u = 0; u < n; ++u)
    for (int v = 0; v < m; ++v)
      px[u] = max(px[u], a[u][v]);

  for (int u = 0, p, q; u < n;) {
    vector<int> s(n + 1, u), t(m, -1);

    for (p = q = 0; p <= q && x[u] < 0; ++p)
      for (int k = s[p], v = 0; v < m && x[u] < 0; ++v)
        if (px[k] + py[v] == a[k][v] && t[v] < 0) {
          s[++q] = y[v], t[v] = k;
          if (s[q] < 0)
            for (p = v; p >= 0; v = p)
              y[v] = k = t[v], p = x[k], x[k] = v;
        }

    if (x[u] < 0) {
      T delta = numeric_limits<T>::max();

      for (int i = 0; i <= q; ++i)
        for (int v = 0; v < m; ++v)
          if (t[v] < 0)
            delta = min(delta, px[s[i]] + py[v] - a[s[i]][v]);

      for (int i = 0; i <= q; ++i)
        px[s[i]] -= delta;

      for (int v = 0; v < m; ++v)
        py[v] += (t[v] < 0 ? 0 : delta);
    } else
      ++u;
  }

  T cost = 0;

  for (int u = 0; u < n; ++u)
    cost += a[u][x[u]];

  return cost;
}
