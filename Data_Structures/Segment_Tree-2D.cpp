/*
        2D Segment tree (Not verified)
        Description: Given a binary associative function f and
        a matrix of elements M[0 n][0 m] and 4 integers
        l, r, t, b, determine the value of f evaluated in the
        elements of submatrix M[l r][t b]. It’s admitted
        to modify the elements in the matrix. Examples of such
        are: max, min , gcd, lcm, sum, product.
        complexity: init = O(NM) update = O(logn*logm)
        query = O(logn*logm)
*/
// n: count row, m: count column

const int MAXN = 1005;
int a[MAXN][MAXN], t[4 * MAXN][4 * MAXN], n, m, neuter;
int (*funct)(int, int);

void initY(int nx, int lx, int rx, int ny, int ly, int ry) {
  if (ly == ry) {
    if (lx == ly)
      t[nx][ny] = a[lx][ly];
    else
      t[nx][ny] = funct(t[nx * 2][ny], t[nx * 2 + 1][ny]);
  } else {
    int m = (ly + ry) / 2;
    initY(nx, lx, rx, ny * 2, ly, m);
    initY(nx, lx, rx, ny * 2 + 1, m + 1, ry);
    t[nx][ny] = funct(t[nx][ny * 2], t[nx][ny * 2 + 1]);
  }
}

void init(int nx, int l, int r) {
  if (l < r) {
    int m = (l + r) / 2;
    init(2 * nx, l, m);
    init(2 * nx + 1, m + 1, r);
  }
  initY(nx, l, r, 1, 0, n - 1);
}

void updateY(int nx, int lx, int rx, int ny, int ly, int ry, int row, int col) {
  if (ly == ry) {
    if (lx == rx)
      t[nx][ny] = a[row][col];
    else
      t[nx][ny] = funct(t[2 * nx][ny], t[2 * nx + 1][ny]);
  } else {
    int m = (ly + ry) / 2;
    if (row <= m)
      updateY(nx, lx, rx, 2 * ny, ly, m, row, col);
    else
      updateY(nx, lx, rx, 2 * ny + 1, m + 1, ry, row, col);
    t[nx][ny] = funct(t[nx][2 * ny], t[nx][2 * ny + 1]);
  }
}

void update(int nx, int l, int r, int row, int col) {
  if (l < r) {
    int m = (l + r) / 2;
    if (col <= m)
      update(2 * nx, l, m, row, col);
    else
      update(2 * nx + 1, m + 1, r, row, col);
  }
  updateY(nx, l, r, 1, 0, n - 1, row, col);
}

int queryY(int nx, int ny, int tly, int tryy, int ly, int ry) {
  if (ly > ry)
    return neuter;
  if (tly == ly && tryy == ry)
    return t[nx][ny];
  int m = (tly + tryy) / 2;
  int op1 = queryY(nx, 2 * ny, tly, m, ly, min(m, ry));
  int op2 = queryY(nx, 2 * ny + 1, m + 1, tryy, max(m + 1, ly), ry);
  return funct(op1, op2);
}

int query(int nx, int tlx, int trx, int lx, int rx, int ly, int ry) {
  if (lx > rx)
    return neuter;
  if (tlx == lx && trx == rx)
    return queryY(nx, 1, 0, n - 1, ly, ry);
  int m = (tlx + trx) / 2;
  int op1 = query(2 * nx, tlx, m, lx, min(rx, m), ly, ry);
  int op2 = query(2 * nx + 1, m + 1, trx, max(m + 1, lx), rx, ly, ry);
  return funct(op1, op2);
}

int sum(int a, int b) { return a + b; }

void out() {
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (j)
        cout << " ";
      cout << a[i][j];
    }
    cout << endl;
  }
  cout << endl;
}

int main() {
  funct = sum;
  n = 4, m = 7;
  int row, col, val, l, r, t, b;
  char c;
  while (1) {
    cin >> c;
    if (c == 'q') {
      cin >> l >> r >> t >> b; // left, right, top, bottom
      cout << query(1, 0, m - 1, l, r, t, b) << endl;
    } else {
      cin >> row >> col >> val;
      a[row][col] = val;
      update(1, 0, m - 1, row, col);
      out();
    }
  }

  return 0;
}
