#define x(c) real(c)
#define y(c) imag(c)
#define NEXT(i) (((i) + 1) % n)

const double EPS = 1e-7;
const int oo = (1 << 30);
typedef complex<double> point;

int cmp_double(double x, double y = 0) {
  return (x <= y + EPS) ? (x + EPS < y) ? -1 : 0 : 1;
}

bool cmp_point(const point &a, const point &b) {
  return (a.x() != b.x()) ? (cmp_double(a.x(), b.x()) == -1)
                          : (cmp_double(a.y(), b.y()) == -1);
}

bool operator<(const point &a, const point &b) { return cmp_point(a, b); }

// a1*b2 - a2*b1 = axb = |a||b|*sin()
double cross(const point &a, const point &b) { return imag(conj(a) * b); }

// a1*b1 + a2*b2 = a.b = |a||b|*cos(a,b)
double dot(const point &a, const point &b) { return real(conj(a) * b); }

int ccw(point a, point b, point c) {
  b -= a;
  c -= a;
  if (cross(b, c) > 0)
    return +1; // counter clockwise
  if (cross(b, c) < 0)
    return -1; // clockwise
  if (dot(b, c) < 0)
    return +2; // c - a - b on line
  if (cmp_double(norm(b), norm(c)) == -1)
    return -2; // a - b - c on line
  return 0;    // a - c - b on line;
}

int cw(point a, point b, point c) { return -ccw(a, b, c); }

double sq(double x) { return x * x; }

double dist2(const point &a, const point &b) {
  return sq(a.x() - b.x()) + sq(a.y() - b.y());
}

double dist(const point &a, const point &b) { return abs(a - b); }

/*
Compares to 2D points by angle
Angle -90 is the first
Tested: LightOJ 1292
*/
bool polar_cmp(point a, point b) {
  if (a.x() >= 0 && b.x() < 0)
    return true;
  if (a.x() < 0 && b.x() >= 0)
    return false;
  if (a.x() == 0 && b.x() == 0) {
    if (a.y() > 0 && b.y() < 0)
      return false;
    if (a.y() < 0 && b.y() > 0)
      return true;
  }
  return cross(a, b) > 0;
}

// p-q-r: clockwise
double angle(point p, point q, point r) {
  point u = p - q, v = r - q;
  return atan2(cross(u, v), dot(u, v));
}

point rotateCCW90(point p) { return point(-p.imag(), p.real()); }

point rotate_by(const point &p, const point &about, double radians) {
  return (p - about) * exp(point(0, radians)) + about;
}
