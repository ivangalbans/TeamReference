typedef vector<point> polygon;

/*
        Convex Hull of a set of points
        O(N logN)
        Not includes colinear points
*/
polygon convex_hull(polygon &pol) {
  int n = pol.size(), k = 0;
  polygon hull(2 * n);

  sort(pol.begin(), pol.end(), cmp_point);
  // lower-hull
  for (int i = 0; i < n; hull[k++] = pol[i++])
    while (k >= 2 && ccw(hull[k - 2], hull[k - 1], pol[i]) <= EPS)
      --k;
  // upper-hull
  for (int i = n - 2, t = k + 1; i >= 0; hull[k++] = pol[i--])
    while (k >= t && ccw(hull[k - 2], hull[k - 1], pol[i]) <= EPS)
      --k;

  hull.resize(k - 1);
  return hull;
}

/*
        Area of a polygon
        The polygon must be in counterclockwise
*/
double poly_area(const polygon &T) {
  double s = 0;
  int n = T.size();
  for (int i = 0; i < n; i++)
    s += cross(T[i], T[NEXT(i)]);
  return s / 2;
}

/*
        Centroid of a (possibly nonconvex) polygon
        Coordinates must be listed in a cw or ccw.

        Tested: SPOJ STONE
        Complexity: O(n)
*/
point centroid(const polygon &p) {
  point c(0, 0);
  double scale = 6.0 * poly_area(p);
  for (int i = 0; i < (int)p.size(); i++) {
    int j = (i + 1) % p.size();
    c = c + (p[i] + p[j]) * (cross(p[i], p[j]));
  }
  return c / scale;
}

/*
       Checks if a point is inside a convex polygon. CCW
       O(log n)
*/
bool is_in_convex(polygon &a, const point &p) {
  int n = a.size(), lo = 1, hi = a.size() - 1;

  if (signed_area(a[0], a[1], p) <= 0)
    return 0;
  if (signed_area(a[n - 1], a[0], p) <= 0)
    return 0;

  while (hi - lo > 1) {
    int mid = (lo + hi) / 2;
    if (signed_area(a[0], a[mid], p) > 0)
      lo = mid;
    else
      hi = mid;
  }

  return signed_area(a[lo], a[hi], p) > 0;
}

inline int cmp(double x, double y = 0) {
  return (x <= y + EPS) ? (x + EPS < y) ? -1 : 0 : 1;
}

inline int ccw1(point p, point q, point r) { return cmp(cross(p - r, q - r)); }

/*
       Intersection of a convex polygon with a half plane
       The polygon must be in ccw
       O(n)
*/
polygon convex_cut(polygon pol, line l) {
  point p = l[0], q = l[1];
  polygon Q;
  int N = pol.size();
  for (int i = 0; i < N; i++) {
    point A = pol[i], B = pol[(i + 1) % N];
    if (ccw1(p, q, A) != -1)
      Q.push_back(A);
    if (ccw1(p, q, A) * ccw1(p, q, B) < 0)
      Q.push_back(crosspoint(line(A, B), line(p, q)));
  }
  return Q;
}

/*
        Pick's theorem
        A = I + B/2 - 1:
        A = Area of the polygon
        I = Number of integer coordinates points inside
        B = Number of integer coordinates points on the boundary
        Polygon's vertex must have integer coordinates
        Add this function for every edge of the polygon
        Tested [Light OJ 1418]
        Complexity: O(n)
*/

int points_on_segment(const line &l) {
  point p = l[0] - l[1];
  return __gcd(abs(p.x()), abs(p.y()));
}

typedef long long Int;
// <Lattice points (not in boundary), Lattice points on boundary>
pair<Int, Int> pick_theorem(polygon &P) {
  Int A = 2 * poly_area(P), B = 0, I = 0;
  int n = P.size();
  for (int i = 0; i < n; ++i) {
    B += points_on_segment(line(P[i], P[NEXT(i)]));
  }
  A = abs(A);
  I = (A - B) / 2 + 1;

  return make_pair(I, B);
}

/*
 * Determina si un poligono es convexo O(n)
 */
bool is_convex(const polygon &pol) {
  int n = pol.size(), pos = 0, neg = 0;
  for (int i = 0; i < n; ++i) {
    int j = PREV(i), k = NEXT(i);
    point ik = point(pol[k].x() - pol[i].x(), pol[k].y() - pol[i].y());
    point ij = point(pol[j].x() - pol[i].x(), pol[j].y() - pol[i].y());

    if (cross(ik, ij) < 0)
      neg++;
    else
      pos++;
  }
  return pos == 0 || neg == 0;
}

/*
        Determine the position of a point relative
        to a polygon.

        Tested: AIZU(judge.u-aizu.ac.jp) CGL.3C
        Complexity: O(n)
*/

enum { OUT, ON, IN };
int contains(const polygon &P, const point &p) {
  bool in = false;
  for (int i = 0, n = P.size(); i < n; ++i) {
    point a = P[i] - p, b = P[NEXT(i)] - p;
    if (imag(a) > imag(b))
      swap(a, b);
    if (imag(a) <= 0 && 0 < imag(b))
      if (cross(a, b) < 0)
        in = !in;
    if (cross(a, b) == 0 && dot(a, b) <= 0)
      return ON;
  }
  return in ? IN : OUT;
}
