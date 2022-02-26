/*
        Gabow's strongly connected component

        Complexity: O(n + m)

        Tested: http://www.spoj.com/problems/CAPCITY/
*/

struct graph {
  int n;
  vector<vector<int>> adj;

  graph(int n) : n(n), adj(n) {}

  void add_edge(int u, int v) { adj[u].push_back(v); }

  vector<int> &operator[](int u) { return adj[u]; }
};

vector<vector<int>> scc_gabow(graph &adj) {
  int n = adj.n;

  vector<vector<int>> scc;
  vector<int> S, B, I(n);

  function<void(int)> dfs = [&](int u) {
    B.push_back(I[u] = S.size());
    S.push_back(u);

    for (int v : adj[u])
      if (!I[v])
        dfs(v);
      else
        while (I[v] < B.back())
          B.pop_back();

    if (I[u] == B.back()) {
      scc.push_back({});
      for (B.pop_back(); I[u] < S.size(); S.pop_back()) {
        scc.back().push_back(S.back());
        I[S.back()] = n + scc.size();
      }
    }
  };

  for (int u = 0; u < n; ++u)
    if (!I[u])
      dfs(u);

  return scc; // in reverse topological order
}
