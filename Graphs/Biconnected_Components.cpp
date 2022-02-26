const int MaxN = 10000;

int n, m;
vector<int> g[MaxN];
int d[MaxN], low[MaxN], pi[MaxN];
int step;

stack<pii> bicon;

void BiconComp(int u) {
  d[u] = low[u] = ++step;
  REP(i, g[u].size()) {
    int w = g[u][i];
    if (w != pi[u] && d[w] < d[u]) // foward edge
    {
      bicon.push(pii(u, w));
      if (d[w] == 0) {
        BiconComp(w);
        low[u] = min(low[u], low[w]);
        if (low[w] >= d[u]) {
          printf("New Biconnected Component:\n");
          pii tmp;
          do {
            tmp = bicon.top();
            bicon.pop();
            printf("%d %d\n", tmp.F, tmp.S);
          } while (!(tmp.F == u && tmp.S == w));
          printf("\n");
        }
      } else if (w != pi[u]) // back edge
        low[u] = min(low[u], d[w]);
    }
  }
}

void init() {
  step = 0;
  REP(i, n) {
    d[i] = low[i] = 0;
    pi[i] = -1;
  }
}
