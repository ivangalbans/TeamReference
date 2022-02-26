// pi[1...m]
vector<int> buildFail(string p) {
  int m = p.size();
  vector<int> pi(m + 1, 0);

  int j = pi[0] = -1;

  for (int i = 1; i <= m; ++i) {
    while (j >= 0 && p[j] != p[i - 1])
      j = pi[j];
    pi[i] = ++j;
  }
  return pi;
}
// KMP Cuenta la cantidad de veces que aparece una
// sub-cadena (p) en la cadena (t)
int match(string t, string p, vector<int> &pi) {
  int n = t.size(), m = p.size();
  int count = 0;

  for (int i = 0, k = 0; i < n; ++i) {
    while (k >= 0 && p[k] != t[i])
      k = pi[k];
    if (++k >= m) {
      ++count;
      k = pi[k];
    }
  }
  return count;
}
