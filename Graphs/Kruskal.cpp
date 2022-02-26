struct Edge {
  int src, dst, weight;
  Edge(int a, int b, int c) : src(a), dst(b), weight(c) {}
};

const int MaxN = 10000;

vector<Edge> mst;
vector<Edge> edge;

bool cmp(Edge x, Edge y) { return x.weight < y.weight; }

int cost = 0;
void Kruskal() {
  mst.clear();
  initDisjointSet();

  sort(ALL(edge), cmp);

  for (int i = 0; i < (int)edge.size(); ++i) {
    int u = edge[i].src;
    int v = edge[i].dst;
    if (SetOf(u) != SetOf(v)) {
      cost += edge[i].weight;
      Merge(u, v);
    }
  }
}
