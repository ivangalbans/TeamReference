/*
        In this example:
        update item[l...r] + val
        query sum(item[l...r])
*/

#define MaxN 1000
#define Left(x) ((x << 1) + 1)
#define Right(x) ((x << 1) + 2)

int st[4 * MaxN], lazy[4 * MaxN];

void push(int node, int nodeL, int nodeR) {
  int m = (nodeL + nodeR) / 2;

  lazy[Left(node)] += lazy[node];
  lazy[Right(node)] += lazy[node];

  st[Left(node)] += (m - nodeL + 1) * lazy[node];
  st[Right(node)] += (nodeR - m) * lazy[node];

  lazy[node] = 0;
}

void update(int node, int nodeL, int nodeR, int l, int r, int val) {
  if (l > nodeR || r < nodeL)
    return;
  if (nodeL >= l && nodeR <= r) {
    st[node] += (nodeR - nodeL + 1) * val;
    lazy[node] += val;
    return;
  }
  push(node, nodeL, nodeR);

  int m = (nodeL + nodeR) / 2;
  update(Left(node), nodeL, m, l, r, val);
  update(Right(node), m + 1, nodeR, l, r, val);
  st[node] = st[Left(node)] + st[Right(node)];
}

int query(int node, int nodeL, int nodeR, int l, int r) {
  if (l > nodeR || r < nodeL)
    return 0;
  if (nodeL >= l && nodeR <= r)
    return st[node];
  push(node, nodeL, nodeR);
  int m = (nodeL + nodeR) / 2;
  return query(Left(node), nodeL, m, l, r) +
         query(Right(node), m + 1, nodeR, l, r);
}
