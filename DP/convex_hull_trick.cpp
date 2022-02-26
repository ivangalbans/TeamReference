typedef pair<int, int> pii;
typedef long long ll;

struct line {
  ll m, b;
  line(ll m, ll b) : m(m), b(b) {}
};

struct ConvexHullTrick {

  int len, ptr;
  vector<line> r;
  ConvexHullTrick(int n) {
    r.assign(n, line(0, 0));
    ptr = len = 0;
  }

  bool bad(line l1, line l2, line l3) {
    return (l3.b - l1.b) * (l1.m - l2.m) < (l2.b - l1.b) * (l1.m - l3.m);
  }

  void add(line x) {
    while (len >= 2 && bad(r[len - 2], r[len - 1], x))
      --len;
    r[len++] = x;
  }

  ll query(int x) {
    ptr = min(ptr, len - 1);
    while (ptr + 1 < len &&
           r[ptr + 1].m * x + r[ptr + 1].b < r[ptr].m * x + r[ptr].b)
      ++ptr;
    return r[ptr].m * x + r[ptr].b;
  }
};
