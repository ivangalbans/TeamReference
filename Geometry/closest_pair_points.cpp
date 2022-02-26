/*
        Compute distance between closest points.

        Tested: AIZU(judge.u-aizu.ac.jp) CGL.5A
        Complexity: O(n log n)
*/

double closest_pair_points(vector<point> &P) {
  auto cmp = [](point a, point b) {
    return make_pair(a.imag(), a.real()) < make_pair(b.imag(), b.real());
  };

  int n = P.size();
  sort(P.begin(), P.end(), cmp_point);

  set<point, decltype(cmp)> S(cmp);
  const double oo = 1e9; // adjust
  double ans = oo;

  for (int i = 0, ptr = 0; i < n; ++i) {
    while (ptr < i && abs(P[i].real() - P[ptr].real()) >= ans)
      S.erase(P[ptr++]);

    auto lo = S.lower_bound(point(-oo, P[i].imag() - ans - eps));
    auto hi = S.upper_bound(point(-oo, P[i].imag() + ans + eps));

    for (decltype(lo) it = lo; it != hi; ++it)
      ans = min(ans, abs(P[i] - *it));

    S.insert(P[i]);
  }

  return ans;
}
