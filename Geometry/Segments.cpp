// Interseccion recta y segmento
bool intersectLS(const line &l, const line &s) {
  return cross(l[1] - l[0], s[0] - l[0]) * // s[0] is left of l
             cross(l[1] - l[0], s[1] - l[0]) <
         EPS; // s[1] is right of l
}

bool intersectSS(const line &s, const line &t) {
  return ccw(s[0], s[1], t[0]) * ccw(s[0], s[1], t[1]) <= 0 &&
         ccw(t[0], t[1], s[0]) * ccw(t[0], t[1], s[1]) <= 0;
}

bool intersectPS(const point &p, const line &s) {
  return abs(s[0] - p) + abs(s[1] - p) - abs(s[1] - s[0]) <
         EPS; // triangle inequality
}

double distanceLS(const line &l, const line &s) {
  if (intersectLS(l, s))
    return 0;
  return min(distancePL(s[0], l), distancePL(s[1], l));
}

double distancePS(const point &p, const line &s) {
  const point r = projectionPL(p, s);
  if (intersectPS(r, s))
    return abs(r - p);
  return min(abs(s[0] - p), abs(s[1] - p));
}

double distanceSS(const line &s, const line &t) {
  if (intersectSS(s, t))
    return 0;
  return min(min(distancePS(t[0], s), distancePS(t[1], s)),
             min(distancePS(s[0], t), distancePS(s[1], t)));
}

point projectionPS(const point &p, const line &l) {
  double r = dot(l[1] - l[0], l[1] - l[0]);
  if (cmp_double(r, 0) == 0)
    return l[0];
  r = dot(p - l[0], l[1] - l[0]) / r;
  if (r < 0)
    return l[0];
  if (r > 1)
    return l[1];
  return l[0] + (l[1] - l[0]) * r;
}

bool merge_if_able(line &s, line t) {
  if (abs(cross(s[1] - s[0], t[1] - t[0])) > EPS)
    return false;

  if (ccw(s[0], t[0], s[1]) == +1 || ccw(s[0], t[0], s[1]) == -1)
    return false; // nsame line

  if (ccw(s[0], s[1], t[0]) == -2 || ccw(t[0], t[1], s[0]) == -2)
    return false; // separated

  s = line(min(s[0], t[0], cmp_point), max(s[1], t[1], cmp_point));

  return true;
}

/*
        Tested: STRAZA
        Contest 2 - COCI 2006-2007
*/
void merge_segments(vector<line> &segs) {
  bool changed = true;
  while (changed) {
    changed = false;
    for (int i = 0; i < (int)segs.size(); ++i)
      for (int j = i + 1; j < (int)segs.size(); ++j) {
        line a = segs[i], b = segs[j];
        if (merge_if_able(segs[i], segs[j])) {
          changed = true;
          segs.erase(segs.begin() + j);
          break;
        }
      }
  }
}
