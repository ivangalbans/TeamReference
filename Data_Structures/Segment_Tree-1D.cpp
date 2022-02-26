/*
        In this example update is in a position and the query is
        the sum of interval. item[N], st[4*N]
*/
#define Left(x) ((x << 1) + 1)
#define Right(x) ((x << 1) + 2)
#define MaxN 1000

int item[MaxN];

void build(int *st, int node, int nodeL, int nodeR) {
  if (nodeL == nodeR) {
    st[node] = item[nodeL];
    return;
  }
  int m = (nodeL + nodeR) / 2;
  build(st, Left(node), nodeL, m);
  build(st, Right(node), m + 1, nodeR);
  st[node] = st[Left(node)] + st[Right(node)];
}

void update(int *st, int node, int nodeL, int nodeR, int pos, int val) {
  if (nodeL == nodeR) {
    st[node] = val;
    return;
  }
  int m = (nodeL + nodeR) / 2;
  if (pos <= m)
    update(st, Left(node), nodeL, m, pos, val);
  else
    update(st, Right(node), m + 1, nodeR, pos, val);
  st[node] = st[Left(node)] + st[Right(node)];
}

int query(int *st, int node, int nodeL, int nodeR, int l, int r) {
  if (nodeL == l && nodeR == r)
    return st[node];
  int m = (nodeL + nodeR) / 2;
  if (r <= m)
    return query(st, Left(node), nodeL, m, l, r);
  if (l > m)
    return query(st, Right(node), m + 1, nodeR, l, r);
  return query(st, Left(node), nodeL, m, l, m) +
         query(st, Right(node), m + 1, nodeR, m + 1, r);
}
