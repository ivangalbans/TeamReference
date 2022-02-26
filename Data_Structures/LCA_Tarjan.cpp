// Tarjan's offline LCA algorithm

const int MaxN = 5000, MaxQ = 5000;
int N, Q;

vector<vector<int>> g(MaxN);
int ancestor[MaxN];
vector<vector<int>> query(MaxQ);
bool visited[MaxN], mk[MaxN];

int cont[MaxN], parent[MaxN];

void initDSU() {
  for (int i = 0; i < N; ++i) {
    parent[i] = i;
    cont[i] = 1;
  }
}

int SetOf(int x) { return parent[x] == x ? x : parent[x] = SetOf(parent[x]); }

void Merge(int x, int y) {
  x = SetOf(x);
  y = SetOf(y);

  if (x == y)
    return;
  if (cont[x] < cont[y])
    swap(x, y);

  parent[y] = x;
  cont[x] += cont[y];
}

void DFS(int u) {
  visited[u] = true;
  ancestor[SetOf(u)] = u;

  for (int i = 0; i < (int)g[u].size(); ++i) {
    int v = g[u][i];
    if (!visited[v]) {
      DFS(v);
      Merge(u, v);
      ancestor[SetOf(u)] = u;
    }
  }

  mk[u] = true;
  for (int i = 0; i < (int)query[u].size(); ++i) {
    int v = query[u][i];
    if (mk[v])
      printf("LCA(%d,%d) = %d\n", u + 1, v + 1, ancestor[SetOf(v)] + 1);
  }
}

int main() {
  cin >> N;
  for (int i = 0; i < N - 1; ++i) {
    int u, v;
    cin >> u >> v;
    u--;
    v--;
    g[u].push_back(v);
    g[v].push_back(u);
  }

  cin >> Q;
  for (int i = 0; i < Q; ++i) {
    int u, v;
    cin >> u >> v;
    u--;
    v--;

    query[u].push_back(v);
    query[v].push_back(u);
  }

  initDSU();
  DFS(0);
  return 0;
}
