const double EPS = 1e-6;

// Romberg
// Assume F' = f
// input: interval [a,b] and a function f
// ouput: F(b)-F(a)

inline int cmp(double x, double y = 0) {
  return (x <= y + EPS) ? (x + EPS < y) ? -1 : 0 : 1;
}

int pow(int a, int n) {
  int x = 1;
  while (n) {
    if (n & 1)
      x *= a;
    n >>= 1;
    a *= a;
  }
  return x;
}

long double romberg(int a, int b, double (*func)(double)) {
  long double approx[2][50];
  long double *cur = approx[1], *prev = approx[0];

  prev[0] = 1 / 2.0 * (b - a) * (func(a) + func(b));

  for (int it = 1; it < 25; ++it, swap(cur, prev)) {
    if (it > 1 && cmp(prev[it - 1], prev[it - 2]) == 0)
      return prev[it - 1];

    cur[0] = 1 / 2.0 * prev[0];
    long double div = (b - a) / pow(2, it);

    for (long double sample = a + div; sample < b; sample += 2 * div)
      cur[0] += div * func(a + sample);

    for (int j = 1; j <= it; ++j)
      cur[j] = cur[j - 1] + 1 / (pow(4, it) - 1) * (cur[j - 1] + prev[j - 1]);
  }

  return prev[24];
}
