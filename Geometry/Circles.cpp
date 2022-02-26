struct circle {
  point center;
  double ratio;

  circle(point center, double ratio) : center(center), ratio(ratio) {}
};

// Tested [BAPC 2010 Clocks]
vector<point> circles_intersection(const circle &c1, const circle &c2) {
  vector<point> ret;
  double d = dist(c1.center, c2.center);
  if (d > c1.ratio + c2.ratio ||
      d + min(c1.ratio, c2.ratio) < max(c1.ratio, c2.ratio))
    return ret;
  double x = (d * d - c2.ratio * c2.ratio + c1.ratio * c1.ratio) / (2 * d);
  double y = sqrt(c1.ratio * c1.ratio - x * x);
  point v = (c2.center - c1.center) / d;
  ret.push_back(c1.center + v * x + rotateCCW90(v) * y);
  if (y > 0)
    ret.push_back(c1.center + v * x - rotateCCW90(v) * y);
  return ret;
}

// Interseccion Linea-Circulo
vector<point> intersectLC(line l, circle c) {
  point a = l[0], b = l[1];
  vector<point> ret;
  b = b - a;
  a = a - c.center;
  double A = dot(b, b);
  double B = dot(a, b);
  double C = dot(a, a) - c.ratio * c.ratio;
  double D = B * B - A * C;

  if (cmp(D) < 0)
    return ret;
  ret.push_back(c.center + a + b * (-B + sqrt(D + EPS)) / A);
  if (cmp(D) > 0)
    ret.push_back(c.center + a + b * (-B - sqrt(D)) / A);

  return ret;
}

/*
        Area of the intersection of a circle with a polygon
        Circle's center lies in (0,0)
        Polygon must be given counterclockwise
        Tested [Light OJ 1358]
*/

#define xx(_t) (xa + (_t)*a)
#define yy(_t) (ya + (_t)*b)

double radian(double xa, double ya, double xb, double yb) {
  return atan2(xa * yb - xb * ya, xa * xb + ya * yb);
}

double part(double xa, double ya, double xb, double yb, double r) {
  double l = sqrt((xa - xb) * (xa - xb) + (ya - yb) * (ya - yb));
  double a = (xb - xa) / l, b = (yb - ya) / l, c = a * xa + b * ya;
  double d = 4.0 * (c * c - xa * xa - ya * ya + r * r);
  if (d < EPS)
    return radian(xa, ya, xb, yb) * r * r * 0.5;
  else {
    d = sqrt(d) * 0.5;
    double s = -c - d, t = -c + d;
    if (s < 0.0)
      s = 0.0;
    else if (s > l)
      s = l;
    if (t < 0.0)
      t = 0.0;
    else if (t > l)
      t = l;
    return (xx(s) * yy(t) - xx(t) * yy(s) +
            (radian(xa, ya, xx(s), yy(s)) + radian(xx(t), yy(t), xb, yb)) * r *
                r) *
           0.5;
  }
}

double area_intersectionPC(polygon P, double r) {
  double s = 0.0;
  int n = (int)P.size();
  P.push_back(P[0]);
  for (int i = 0; i < n; ++i)
    s += part(P[i].x(), P[i].y(), P[NEXT(i)].x(), P[NEXT(i)].y(), r);
  return fabs(s);
}

// circle tangents through point
vector<point> tangent(point p, circle C) {
  // not tested enough

  double D = abs(p - C.p);

  if (D + eps < C.r)
    return {};
  point t = C.p - p;

  double theta = asin(C.r / D);
  double d = cos(theta) * D;

  t = t / abs(t) * d;
  if (abs(D - C.r) < eps)
    return {p + t};
  point rot(cos(theta), sin(theta));
  return {p + t * rot, p + t * conj(rot)};
}

bool incircle(point a, point b, point c, point p) {
  a -= p;
  b -= p;
  c -= p;
  return norm(a) * cross(b, c) + norm(b) * cross(c, a) +
             norm(c) * cross(a, b) >=
         0;
  // < : inside, = cocircular, > outside
}

point three_point_circle(point a, point b, point c) {
  point x = 1.0 / conj(b - a), y = 1.0 / conj(c - a);
  return (y - x) / (conj(x) * y - x * conj(y)) + a;
}

/*
    Get the center of the circles that pass through p0 and p1
    and has ratio r.

    Be careful with epsilon.
*/
vector<point> two_point_ratio_circle(point p0, point p1, double r) {
  if (abs(p1 - p0) > 2 * r + eps) // Points are too far.
    return {};

  point pm = (p1 + p0) / 2.0l;
  point pv = p1 - p0;

  pv = point(-pv.imag(), pv.real());

  double x1 = p1.real(), y1 = p1.imag();
  double xm = pm.real(), ym = pm.imag();
  double xv = pv.real(), yv = pv.imag();

  double A = (sqr(xv) + sqr(yv));
  double C = sqr(xm - x1) + sqr(ym - y1) - sqr(r);
  double D = sqrt(-4 * A * C);
  double t = D / 2.0 / A;

  if (abs(t) <= eps)
    return {pm};

  return {c1, c2};
}
