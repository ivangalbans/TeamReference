/*
  TASK  : Coding a kd-tree

  Remarks: The data structure is used in this code to
           answer 2D range queries on a set of n 2D
           points of the type "report all points inside
           a rectangle [a,b]x[c,d]". The points' coordinates
           are assumed to be integers.
  Performance:
           Build kd-tree: O(n log n)*
           Query: O(sqrt(n) + k)
           k: number of points inside query region

           * expected
*/
#define MAXN 10000
#define oo 1000000000

struct point {
  int x, y;
};
struct region {
  int xlo, xhi, ylo, yhi;
};

struct node {
  point p;
  node *l, *r;
  region R;
  node(point p, node *l, node *r, int xlo, int xhi, int ylo, int yhi)
      : p(p), l(l), r(r) {
    R = (region){xlo, xhi, ylo, yhi};
  }
} * root;

int N, Q;
int xlo, ylo;
int xhi, yhi;
region R;

point p[MAXN];

inline bool leaf(node *x) { return !x->l && !x->r; }
inline bool less_than(const point &a, const point &b, bool byX) {
  return byX ? a.x < b.x : a.y < b.y;
}

void partition(point a[], int lo, int hi, const int &k, bool byX) {

  int l = lo, r = hi - 1, mid = (lo + hi) >> 1;

  if (less_than(a[mid], a[lo], byX))
    swap(a[mid], a[lo]);
  if (less_than(a[hi], a[lo], byX))
    swap(a[hi], a[lo]);
  if (less_than(a[hi], a[mid], byX))
    swap(a[hi], a[mid]);

  if (hi - lo + 1 <= 3)
    return;

  swap(a[mid], a[hi - 1]);
  point pivot = a[hi - 1];

  for (;;) {
    while (less_than(a[++l], pivot, byX))
      ;
    while (less_than(pivot, a[--r], byX))
      ;
    if (l < r)
      swap(a[l], a[r]);
    else
      break;
  }

  swap(a[l], a[hi - 1]);

  if (k < l)
    partition(a, lo, l - 1, k, byX);
  if (k > l)
    partition(a, l + 1, hi, k, byX);
}

node *build_kd_tree(point p[], int len, int depth, int xlo, int xhi, int ylo,
                    int yhi) {

  if (len == 1)
    return new node(p[0], 0, 0, p[0].x, p[0].x, p[0].y, p[0].y);

  int mid = (len - 1) / 2;
  partition(p, 0, len - 1, mid, !(depth & 1));

  int c1 = 0, c2 = 0;
  point p1[MAXN], p2[MAXN];
  for (int i = 0; i <= mid; i++)
    p1[c1++] = p[i];
  for (int i = mid + 1; i < len; i++)
    p2[c2++] = p[i];

  int xlo1 = xlo, xhi1 = xhi, ylo1 = ylo, yhi1 = yhi, xlo2 = xlo, xhi2 = xhi,
      ylo2 = ylo, yhi2 = yhi;

  if (!(depth & 1))
    xhi1 = p[mid].x, xlo2 = p[mid].x + 1;
  else
    yhi1 = p[mid].y, yhi2 = p[mid].y + 1;

  node *left = build_kd_tree(p1, mid + 1, depth + 1, xlo1, xhi1, ylo1, yhi1);
  node *right =
      build_kd_tree(p2, len - mid - 1, depth + 1, xlo2, xhi2, ylo2, yhi2);

  return new node(p[mid], left, right, xlo, xhi, ylo, yhi);
}

void report(node *t) {
  if (!t)
    return;
  if (leaf(t))
    printf("(%d,%d) ", t->p.x, t->p.y);
  else {
    report(t->l);
    report(t->r);
  }
}

region make_region(node *t) {
  return (region){t->R.xlo, t->R.xhi, t->R.ylo, t->R.yhi};
}

bool contained(const region &a, const region &b) {
  return (b.xlo <= a.xlo && a.xlo <= b.xhi && b.xlo <= a.xhi &&
          a.xhi <= b.xhi && b.ylo <= a.ylo && a.ylo <= b.yhi &&
          b.ylo <= a.yhi && a.yhi <= b.yhi);
}

bool intersect(const region &a, const region &b) {
  bool okX = ((a.xlo <= b.xlo && b.xlo <= a.xhi) ||
              (a.xlo <= b.xhi && b.xhi <= a.xhi));
  bool okY = ((a.ylo <= b.ylo && b.ylo <= a.yhi) ||
              (a.ylo <= b.yhi && b.yhi <= a.yhi));
  return okX && okY;
}

void query(node *t, const region &R) {

  if (leaf(t)) {
    if (contained(t->R, R))
      report(t);
  } else {

    region lc = make_region(t->l);
    if (contained(lc, R))
      report(t->l);
    else if (intersect(lc, R))
      query(t->l, R);

    region rc = make_region(t->r);
    if (contained(rc, R))
      report(t->r);
    else if (intersect(rc, R))
      query(t->r, R);
  }
}

int main() {

  scanf("%d", &N);
  for (int i = 0; i < N; i++)
    scanf("%d %d", &p[i].x, &p[i].y);

  root = build_kd_tree(p, N, 0, -oo, oo, -oo, oo);

  for (scanf("%d", &Q); Q--;) {
    scanf("%d %d %d %d", &xlo, &ylo, &xhi, &yhi);
    R = (region){xlo, xhi, ylo, yhi};
    query(root, R);
    printf("\n");
  }

  return 0;
}
