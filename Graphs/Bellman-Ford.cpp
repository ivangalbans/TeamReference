int n, m;

const int MaxN = 1000;

vector<pii> g[MaxN];

struct Edge {

  int src, dst, weight;
  Edge(int a, int b, int c) : src(a), dst(b), weight(c) {}
};

vector<Edge> edges;
vector<int> dist;

bool Bellman_Ford(int s) {
  dist = vector<int>(n, oo);
  dist[s] = 0;

  for (int i = 0; i < n - 1; ++i) {
    foreach (e, edges) {
      int u = e->src;
      int v = e->dst;
      int w = e->weight;

      if (dist[u] + w < dist[v])
        dist[v] = dist[u] + w;
    }
  }

  foreach (e, edges) {
    int u = e->src;
    int v = e->dst;
    int w = e->weight;

    if (dist[u] + w < dist[v])
      return false; // negative_cycle_exist
  }
  return true;
}
