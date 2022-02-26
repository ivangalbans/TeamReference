/*
        Lowest Common Ancestor Problem
        implemented with SQRT DESCOMPOSITION.
        Root = 0
        Running time: <O(N), O(sqrt(N))>
*/
#define MAXN 50000

int N, queries;
int u, v;
int height, sqrt_height;

int p[MAXN], level[MAXN];
int parent[MAXN], ancestor[MAXN];
bool mark[MAXN];

struct edge {
  int v, next;
} edges[2 * (MAXN - 1)];

void readTree() {
  memset(p, -1, sizeof(p));

  scanf("%d", &N);
  for (int i = 0; i < N - 1; i++) {

    scanf("%d %d", &u, &v);
    u--;
    v--;

    edges[i] = (edge){v, p[u]};
    p[u] = i;
    edges[i + N - 1] = (edge){u, p[v]};
    p[v] = i + N - 1;
  }
}

// BFS to assign levels.
void assignLevels() {
  queue<int> Q;

  level[0] = height = 0;
  mark[0] = true;
  Q.push(0);

  while (!Q.empty()) {

    u = Q.front();
    Q.pop();

    for (int i = p[u]; i != -1; i = edges[i].next) {
      v = edges[i].v;
      if (!mark[v]) {
        mark[v] = true;
        parent[v] = u;
        level[v] = level[u] + 1;
        height = max(height, level[v]);
        Q.push(v);
      }
    }
  }
}

void dfs(int u) {

  if (level[u] < sqrt_height)
    ancestor[u] = 0;
  else if (level[u] % sqrt_height == 0)
    ancestor[u] = parent[u];
  else
    ancestor[u] = ancestor[parent[u]];

  mark[u] = true;
  for (int i = p[u]; i != -1; i = edges[i].next)
    if (!mark[edges[i].v])
      dfs(edges[i].v);
}

int LCA(int u, int v) {

  while (ancestor[u] != ancestor[v])
    if (level[u] > level[v])
      u = ancestor[u];
    else
      v = ancestor[v];

  while (u != v)
    if (level[u] > level[v])
      u = parent[u];
    else
      v = parent[v];

  return u;
}

int main() {

  readTree();
  assignLevels();
  sqrt_height = (int)sqrt(height);
  memset(mark, 0, sizeof(mark));
  dfs(0);

  cin >> queries;
  for (int i = 0; i < queries; ++i) {
    cin >> u >> v;
    printf("LCA(%d,%d) = %d\n", u, v, LCA(u - 1, v - 1) + 1);
  }

  return 0;
}
