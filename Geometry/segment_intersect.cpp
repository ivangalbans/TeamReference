#define _GLIBCXX_DEBUG
#include <algorithm>
#include <complex>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <stdio.h>
#include <string.h>
#include <string>
#include <vector>
using namespace std;
#define REP(i, n) for (int i = 0; i < (int)n; ++i)
#define FOR(i, c)                                                              \
  for (__typeof((c).begin()) i = (c).begin(); i != (c).end(); ++i)
#define ALL(c) (c).begin(), (c).end()
#define Y(c) imag(c)
#define X(c) real(c)
#define INF 100000000
// Graph Only
typedef int Weight;
struct Edge {
  int src, dst;
  Weight weight;
  Edge(int src, int dst, Weight weight) : src(src), dst(dst), weight(weight) {}
};
bool operator<(const Edge &e, const Edge &f) {
  return e.weight != f.weight ? e.weight > f.weight
         : e.src != f.src     ? e.src < f.src
                              : e.dst < f.dst;
}
typedef vector<Edge> Edges;
typedef vector<Edges> Graph;
typedef vector<Weight> Array;
typedef vector<Array> Matrix;
#define P complex<double>
typedef vector<P> Pol;
bool operator<(const P &a, const P &b) {
  return X(a) != X(b) ? X(a) < X(b) : Y(a) < Y(b);
}
struct L : public vector<P> {
  L(const P &a, const P &b) {
    if (a < b) {
      push_back(a);
      push_back(b);
    } else {
      push_back(b);
      push_back(a);
    }
  }
};
const double EPS = 1e-8, oo = 1e12;

bool op_min(const P &a, const P &b) {
  return X(a) != X(b) ? X(a) < X(b) : Y(a) < Y(b);
}

double cross(P a, P b) { return Y(conj(a) * b); }
double dot(P a, P b) { return X(conj(a) * b); }

int ccw(P a, P b, P c) { // Orientacion de 3 puntos
  b -= a;
  c -= a;
  if (cross(b, c) > 0)
    return +1; // counter clockwise
  if (cross(b, c) < 0)
    return -1; // clockwise
  if (dot(b, c) < 0)
    return +2; // c - a - b line
  if (norm(b) < norm(c))
    return -2; // a - b - c line
  return 0;
}

bool intersectSS(L s, L t) { // Inters de 2 segm
  if (abs(s[0] - t[0]) < EPS || abs(s[0] - t[1]) < EPS ||
      abs(s[1] - t[0]) < EPS || abs(s[1] - t[1]) < EPS)
    return 1; // Puntos Iguales
  return ccw(s[0], s[1], t[0]) * ccw(s[0], s[1], t[1]) <= 0 &&
         ccw(t[0], t[1], s[0]) * ccw(t[0], t[1], s[1]) <= 0;
}

P crosspoint(L l, L m) { // Punto inters /2 rectas
  double A = cross(l[1] - l[0], m[1] - m[0]);
  double B = cross(l[1] - l[0], l[1] - m[0]);
  if (abs(A) < EPS && abs(B) < EPS)
    return m[0]; // Same L
  if (abs(A) < EPS)
    return P(0, 0); // parallels
  return m[0] + B / A * (m[1] - m[0]);
}

struct event {
  double x;
  int type;
  L seg;
  event(double x, int type, const L &seg) : x(x), type(type), seg(seg) {}
  bool operator<(const event &e) const {
    return x != e.x ? x > e.x : type > e.type;
  }
};
struct segComp {
  bool operator()(const L &a, const L &b) {
    if (a[0] < b[0])
      return true;
    if (a[1] < b[1])
      return true;
    return false;
  }
};
int segment_intersects(const vector<L> &segs, vector<P> &out) {
  priority_queue<event> Q;
  for (int i = 0; i < segs.size(); ++i) {
    double x1 = real(segs[i][0]), x2 = real(segs[i][1]);
    Q.push(event(min(x1, x2), 0, segs[i]));
    Q.push(event(max(x1, x2), 1, segs[i]));
  }
  int count = 0;
  set<L, segComp> T;
  while (!Q.empty()) {
    event e = Q.top();
    Q.pop();
    if (e.type == 0) {
      for (set<L, segComp>::iterator itr = T.begin(); itr != T.end(); ++itr)
        if (intersectSS(*itr, e.seg)) {
          out.push_back(crosspoint(*itr, e.seg));
          ++count;
        }
      T.insert(e.seg);
    } else
      T.erase(e.seg);
  }
  return count;
}

bool merge_if_able(L &s, L t) {
  if (abs(cross(s[1] - s[0], t[1] - t[0])) > EPS)
    return false;
  if (ccw(s[0], t[0], s[1]) == +1 || ccw(s[0], t[0], s[1]) == -1)
    return false; // not on the same line
  if (ccw(s[0], s[1], t[0]) == -2 || ccw(t[0], t[1], s[0]) == -2)
    return false; // separated
  s = L(min(s[0], t[0], op_min), max(s[1], t[1], op_min));
  return true;
}
void merge_segments(vector<L> &segs) {
  for (int i = 0; i < segs.size(); ++i)
    for (int j = i + 1; j < segs.size(); ++j)
      if (merge_if_able(segs[i], segs[j]))
        segs[j--] = segs.back(), segs.pop_back();
}

pair<P, P> closestPair(vector<P> &p) {
  int n = p.size(), s = 0, t = 1, m = 2, S[n];
  S[0] = 0, S[1] = 1;
  sort(ALL(p), op_min); //"p<q"<=>"px<qx"
  double d = norm(p[s] - p[t]);
  for (int i = 2; i < n; S[m++] = i++)
    REP(j, m) {
      if (norm(p[S[j]] - p[i]) < d)
        d = norm(p[s = S[j]] - p[t = i]);
      if (real(p[S[j]]) < real(p[i]) - d)
        S[j--] = S[--m];
    }
  return make_pair(p[s], p[t]);
}

int main() {
  P p1(0, 1);
  P p2(-1, 0);
  P p3(0, 2);
  P p4(4, 2);
  P p5(1, 0);
  P p6(-1, 0);
  vector<L> segs;
  vector<P> out;
  segs.push_back(L(p1, p2));
  segs.push_back(L(p3, p4));
  segs.push_back(L(p5, p6));
  cout << segment_intersects(segs, out) << endl;
  FOR(i, out) cout << *i << endl;
  return 0;
}
