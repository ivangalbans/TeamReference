const int MaxV = 10005;

enum { White, Gray, Black };

vi g[MaxV];
int d[MaxV], low[MaxV], pi[MaxV];
int step = 0;
bool puntoArticulacion[MaxV];
set<pii> aristaPuente;
int dfsRoot, rootChildren;

int n, m;

void DFS(int u) {
  low[u] = d[u] = ++step;
  REP(i, g[u].size()) {
    int v = g[u][i];
    if (d[v] == White) {
      pi[v] = u;
      if (u == dfsRoot)
        ++rootChildren;

      DFS(v);

      if (low[v] >= d[u]) // for articulation point
        puntoArticulacion[u] = true;
      if (low[v] > d[u]) // for bridge
        aristaPuente.insert(pii(u, v));

      low[u] = min(low[u], low[v]);
    } else if (v != pi[u])
      low[u] = min(low[u], d[v]);
  }
}

void articulationPointAndBridge() {
  step = 0;
  REP(i, n - 1) {
    if (d[i] == White) {
      dfsRoot = i;
      rootChildren = 0;
      DFS(i);
      puntoArticulacion[dfsRoot] = (rootChildren > 1);
    }
  }
}
