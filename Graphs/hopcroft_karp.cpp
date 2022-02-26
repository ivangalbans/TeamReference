/*
        Tested: SPOJ MATCHING
        Complexity: O(m n^0.5)
*/

struct graph {
  int L, R;
  vector<vector<int>> adj;

  graph(int L, int R) : L(L), R(R), adj(L + R) {}

  void add_edge(int u, int v) {
    adj[u].push_back(v + L);
    adj[v + L].push_back(u);
  }

  int maximum_matching() {
    vector<int> level(L), mate(L + R, -1);

    function<bool(void)> levelize = [&]() {
      queue<int> Q;
      for (int u = 0; u < L; ++u) {
        level[u] = -1;
        if (mate[u] < 0) {
          level[u] = 0;
          Q.push(u);
        }
      }
      while (!Q.empty()) {
        int u = Q.front();
        Q.pop();
        for (int w : adj[u]) {
          int v = mate[w];
          if (v < 0)
            return true;
          if (level[v] < 0) {
            level[v] = level[u] + 1;
            Q.push(v);
          }
        }
      }
      return false;
    };

    function<bool(int)> augment = [&](int u) {
      for (int w : adj[u]) {
        int v = mate[w];
        if (v < 0 || (level[v] > level[u] && augment(v))) {
          mate[u] = w;
          mate[w] = u;
          return true;
        }
      }
      return false;
    };
    int match = 0;
    while (levelize())
      for (int u = 0; u < L; ++u)
        if (mate[u] < 0 && augment(u))
          ++match;
    return match;
  }
};
