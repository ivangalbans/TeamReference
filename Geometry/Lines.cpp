struct line : public vector<point> {
  line(const point &a, const point &b) {
    if (a < b) {
      push_back(a);
      push_back(b);
    } else {
      push_back(b);
      push_back(a);
    }
  }
};

bool intersectLL(const line &l, const line &m) {
  return abs(cross(l[1] - l[0], m[1] - m[0])) > EPS || // non-parallel
         abs(cross(l[1] - l[0], m[0] - l[0])) < EPS;   // same line
}

bool intersectLP(const line &l, const point &p) {
  return abs(cross(l[1] - p, l[0] - p)) < EPS;
}

point projectionPL(const point &p, const line &l) {
  double t = dot(p - l[0], l[0] - l[1]) / norm(l[0] - l[1]);
  return l[0] + t * (l[0] - l[1]);
}

point reflectPL(const point &p, const line &l) {
  point z = p - l[0];
  point w = l[1] - l[0];
  return conj(z / w) * w + l[0];
}

double distancePL(const point &p, const line &l) {
  return abs(p - projectionPL(p, l));
}

double distanceLL(const line &l, const line &m) {
  return intersectLL(l, m) ? 0 : distancePL(m[0], l);
}

// Punto interseccion recta recta
point crosspoint(const line &l, const line &m) {
  double A = cross(l[1] - l[0], m[1] - m[0]);
  double B = cross(l[1] - l[0], l[1] - m[0]);
  if (abs(A) < EPS && abs(B) < EPS)
    return m[0]; // Same line
  if (abs(A) < EPS)
    return point(0, 0); // parallels
  return m[0] + B / A * (m[1] - m[0]);
}

bool parallelLL(const line &l, const line &m) {
  return !cmp_double(cross(l[1] - l[0], m[0] - m[1]));
}

bool collinearLL(const line &l, const line &m) {
  return parallelLL(l, m) && !cmp_double(cross(l[0] - l[1], l[0] - m[0])) &&
         !cmp_double(cross(m[0] - m[1], m[0] - l[0]));
}
