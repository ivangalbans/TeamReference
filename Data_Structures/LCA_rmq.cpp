/*
          Task  : Lowest Common Ancestor Problem: reduction to RMQ
          Preprocessing --> O(N log N)
          Answer query  --> O(1)
*/
#define MAXN 50005
#define LOGMAXN 16
#define DB(x) cout << #x << " = " << x << endl
using namespace std;

vector<vector<int>> ady(MAXN);
bool mk[MAXN];

int N;
int RMQ[MAXN][LOGMAXN];
int tour[2 * MAXN - 1], level[2 * MAXN - 1], pos[MAXN];

int index = 0;

void DFS(int u) {
  mk[u] = true;
  pos[u] = index;
  tour[index++] = u;

  for (int i = 0; i < (int)ady[u].size(); ++i) {
    int v = ady[u][i];
    if (!mk[v]) {
      level[index] = level[index - 1] + 1;
      DFS(v);
      level[index] = level[pos[u]];
      tour[index++] = u;
    }
  }
}

void buildRMQ() {
  int N2 = 2 * N - 1;
  for (int i = 0; i < N2; ++i)
    RMQ[i][0] = i;
  for (int j = 1; (1 << j) <= N2; ++j)
    for (int i = 0; i + (1 << j) - 1 < N2; ++i)
      if (level[RMQ[i][j - 1]] <= level[RMQ[i + (1 << (j - 1))][j - 1]])
        RMQ[i][j] = RMQ[i][j - 1];
      else
        RMQ[i][j] = RMQ[i + (1 << (j - 1))][j - 1];
}

int queryRMQ(int x, int y) {
  int k = __lg(y - x + 1);
  return level[RMQ[x][k]] < level[RMQ[y - (1 << k) + 1][k]]
             ? RMQ[x][k]
             : RMQ[y - (1 << k) + 1][k];
}

int queryLCA(int x, int y) {
  if (pos[x] > pos[y])
    swap(x, y);

  int idLCA = queryRMQ(pos[x], pos[y]);
  return tour[idLCA] + 1;
}

int main() {

  cin >> N;
  for (int i = 0; i < N - 1; ++i) {
    int u, v;
    cin >> u >> v;
    --u;
    --v;
    ady[u].push_back(v);
    ady[v].push_back(u);
  }

  // Euler Tour
  DFS(0);
  buildRMQ();

  int q;
  cin >> q;
  for (int i = 0; i < q; ++q) {
    int x, y;
    cin >> x >> y;
    printf("LCA(%d, %d) = %d\n", x, y, queryLCA(x - 1, y - 1));
  }

  return 0;
}
