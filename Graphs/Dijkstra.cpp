const int MaxN = 1000;

int n, m;

vector<pii> g[MaxN];
int pi[MaxN];

priority_queue<pii, vector<pii>, greater<pii>> pq;

vector<int> Dijkstra(int s) {
  vector<int> d(n, oo);
  pq = priority_queue<ii, vector<ii>, greater<ii>>();

  d[s] = 0;
  pq.push(ii(0, s));

  while (!pq.empty()) {
    int dist = pq.top().F, u = pq.top().S;
    pq.pop();

    if (dist == d[u]) {
      for (int i = 0; i < (int)g[u].size(); ++i) {
        int v = g[u][i].S;
        int w = g[u][i].F;
        if (d[u] + w < d[v]) {
          d[v] = d[u] + w;
          pq.push(ii(d[v], v));
        }
      }
    }
  }
  return d;
}
