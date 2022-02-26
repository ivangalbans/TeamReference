double TernarySearchMin(double l, double r) {
  while (r - l > EPS) {
    double m1 = (2 * l + r) / 3.0;
    double m2 = (l + 2 * r) / 3.0;

    if (f(m1) < f(m2))
      r = m2;
    else
      l = m1;
  }
  return (l + r) / 2.0;
}

double TernarySearchMax(double l, double r) {
  while (r - l > EPS) {
    double m1 = (2 * l + r) / 3.0;
    double m2 = (l + 2 * r) / 3.0;

    if (f1(m1) < f1(m2))
      l = m1;
    else
      r = m2;
  }
  return (l + r) / 2.0;
}

// Discrette
int SearchMin(vector<int> &y) {
  int l = 0, r = y.size() - 1;
  while (r - l < 3) {
    int m1 = (2 * l + r) / 3;
    int m2 = (l + 2 * r) / 3;

    if (y[m1] < y[m2])
      r = m2;
    else
      l = m1;
  }
  return min_element(y.begin() + l, y.begin() + r) - y.begin();
}
