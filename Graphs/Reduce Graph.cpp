//============================================================================
// Name        : Reduce.cpp
// Author      : Ivan Galban Smith
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

/////////////////////////////////////////////////
typedef complex<double> P;
typedef vector<P> Pol;
typedef long long Int;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<vi> Graph;
/////////////////////////////////////////////////
#define REP(i, n) for (int i = 0; i < (int)n; ++i)
#define FOR(i, n) for (int i = 1; i <= (int)n; ++i)
#define ITR(c) __typeof((c).begin())
#define foreach(i, c) for (ITR(c) i = (c).begin(); i != (c).end(); ++i)
#define ALL(c) (c).begin(), (c).end()
#define DB(x) cout << #x << " = " << x << endl

#define X(c) real(c)
#define Y(c) imag(c)
#define endl '\n'
#define F first
#define S second
#define pb push_back
#define mp make_pair
#define BIT(n) (1 << n)
/////////////////////////////////////////////////
const double EPS = 1e-15;
const int oo = (1 << 30);
const double PI = M_PI;
const int MOD = 1000000000 + 7;
/////////////////////////////////////////////////

const int MaxN = 1000;

struct Edge {
  int src, dst, wt;
  Edge(int a, int b, int c) : src(a), dst(b), wt(c) {}
};

int n, m;

vector<Edge> g[MaxN];
vector<Edge> gt[MaxN];
vector<Edge> gr[MaxN];

int cur, cur_scc;

int mk[MaxN];
int order[MaxN];

int scc[MaxN];
int vcountSCC[MaxN];

void dfs(int u) {
  mk[u] = true;
  REP(i, g[u].size()) {
    int v = g[u][i].dst;
    if (!mk[v])
      dfs(v);
  }
  order[n - 1 - cur++] = u;
}

void dfs_rev(int u) {
  scc[u] = cur_scc;
  ++vcountSCC[cur_scc];
  mk[u] = true;

  REP(i, gt[u].size()) {
    int v = gt[u][i].dst;
    if (!mk[v])
      dfs_rev(v);
  }
}

void make_scc() {
  cur = 0;
  memset(mk, 0, sizeof(mk));
  REP(i, n)
  if (!mk[i])
    dfs(i);

  cur_scc = 0;
  memset(mk, 0, sizeof(mk));

  REP(i, n) {
    int v = order[i];
    if (!mk[v]) {
      dfs_rev(v);
      ++cur_scc;
    }
  }
}

void build_reduce_graph() {
  make_scc();
  REP(i, n)
  REP(j, g[i].size())
  if (scc[i] != scc[g[i][j].dst])
    gr[scc[i]].pb(Edge(scc[i], scc[g[i][j].dst], g[i][j].wt));
}

int main() {
  // ios_base::sync_with_stdio(false);
  // cin.tie(0);

  cin >> n >> m;
  REP(i, m) {
    int a, b, c;
    cin >> a >> b >> c;
    g[a].pb(Edge(a, b, c));
    gt[b].pb(Edge(b, a, c));
  }

  build_reduce_graph();

  cout << "V " << cur_scc << "\nEdges:\n";
  REP(u, cur_scc)
  REP(i, gr[u].size()) {
    Edge e = gr[u][i];
    cout << e.src << " " << e.dst << " " << e.wt << endl;
    ;
  }

  return 0;
}
