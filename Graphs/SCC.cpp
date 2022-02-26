const int MaxN = 10000;

struct edge {

  int src, dst, w;
  edge(int a, int b, int c) : src(a), dst(b), w(c) {}
};

typedef vector<edge> Graph;
int n, m;
Graph g[MaxN];
Graph gt[MaxN];
int order[MaxN], mk[MaxN];
int scc[MaxN];
int vcount[MaxN];
int cur;
int cur_scc;

void dfs(int u) {
  mk[u] = true;
  for (int i = 0; i < (int)g[u].size(); ++i) {
    int v = g[u][i].dst;
    if (!mk[v])
      dfs(v);
  }
  order[n - 1 - cur++] = u;
}

void dfs_rev(int u) {
  scc[u] = cur_scc;
  ++vcount[cur_scc];
  mk[u] = true;

  for (int i = 0; i < (int)gt[u].size(); ++i) {
    int v = gt[u][i].dst;
    if (!mk[v])
      dfs_rev(v);
  }
}

void make_scc() {
  cur = 0;
  memset(mk, 0, sizeof(mk));
  for (int i = 0; i < n; ++i)
    if (!mk[i])
      dfs(i);

  cur_scc = 0;
  memset(mk, 0, sizeof(mk));

  for (int i = 0; i < n; ++i) {
    int v = order[i];
    if (!mk[v]) {
      dfs_rev(v);
      ++cur_scc;
    }
  }
}

void init() {
  for (int i = 0; i < n; ++i) {
    g[i].clear();
    gt[i].clear();
    vcount[i] = 0;
  }
}
