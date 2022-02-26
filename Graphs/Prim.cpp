const int MaxN = 10000;

int n, m;
typedef pair<int, pii> par;
priority_queue<par, vector<par>, greater<par>> pq;
vi taken;
vector<pii> g[MaxN];
int mstCost;
vector<pii> mstEdge;

void process(int u) {
  taken[u] = 1;
  for (int i = 0; i < (int)g[u].size(); ++i) {
    pii v = g[u][i];
    if (!taken[v.S])
      pq.push(par(v.F, pii(u, v.S)));
  }
}

void Prim(int s) {
  taken.assign(n, 0);
  pq = priority_queue<par, vector<par>, greater<par>>();

  process(s);
  mstCost = 0;

  while (!pq.empty()) {
    par top = pq.top();
    pq.pop();
    pii node = top.S;

    int w = top.F;
    int u = node.F;
    int v = node.S;

    if (!taken[v]) {
      mstCost += w;
      mstEdge.pb(pii(u, v));
      process(v);
    }
  }
}
