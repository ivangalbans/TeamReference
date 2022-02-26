typedef vector<point> triangle;

triangle make_triangle(const point &a, const point &b, const point &c) {
  triangle ret(3);
  ret[0] = a;
  ret[1] = b;
  ret[2] = c;
  return ret;
}

bool triangle_contains(const triangle &tri, const point &p) {
  return ccw(tri[0], tri[1], p) >= 0 && ccw(tri[1], tri[2], p) >= 0 &&
         ccw(tri[2], tri[0], p) >= 0;
}

bool ear_Q(int i, int j, int k, const polygon &P) {
  triangle tri = make_triangle(P[i], P[j], P[k]);
  if (ccw(tri[0], tri[1], tri[2]) <= 0)
    return false;
  for (int m = 0; m < (int)P.size(); ++m)
    if (m != i && m != j && m != k)
      if (triangle_contains(tri, P[m]))
        return false;
  return true;
}

void triangulate(const polygon &P, vector<triangle> &t) {
  const int n = P.size();
  vector<int> l, r;

  for (int i = 0; i < n; ++i) {
    l.push_back((i - 1 + n) % n);
    r.push_back((i + 1 + n) % n);
  }

  int i = n - 1;
  while ((int)t.size() < n - 2) {
    i = r[i];
    if (ear_Q(l[i], i, r[i], P)) {
      t.push_back(make_triangle(P[l[i]], P[i], P[r[i]]));
      l[r[i]] = l[i];
      r[l[i]] = r[i];
    }
  }
}

/*
        Perturbative deformation of a polygon.
        Each side of the polygon in counterclockwise
        polygon len making just the right translation.
*/
#define curr(P, i) P[i]
#define prev(P, i) P[((i - 1) + P.size()) % P.size()]
#define next(P, i) P[(i + 1) % P.size()]

polygon shrink_polygon(const polygon &P, double len) {
  polygon res;
  for (int i = 0; i < (int)P.size(); ++i) {
    point a = prev(P, i), b = curr(P, i), c = next(P, i);
    point u = (b - a) / abs(b - a);
    double th = arg((c - b) / u) * 0.5;
    point tmp(-sin(th), cos(th));
    res.push_back(b + u * tmp * len / cos(th));
  }
  return res;
}
