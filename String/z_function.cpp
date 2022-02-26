// Z[i] is the length of the longest substring
// starting from S[i] which is also a prefix of S.
vector<int> z_function(string s) {
  int n = (int)s.length();
  vector<int> z(n);

  for (int i = 1, l = 0, r = 0; i < n; ++i) {
    if (i <= r)
      z[i] = min(r - i + 1, z[i - l]);
    while (i + z[i] < n && s[z[i]] == s[i + z[i]])
      ++z[i];
    if (i + z[i] - 1 > r)
      l = i, r = i + z[i] - 1;
  }
  return z;
}

// suff[i] = length of the longest common suffix of s and s[0..i]
vector<int> suffixes(const string &s) {
  int n = s.length();

  vector<int> suff(n, n);

  for (int i = n - 2, g = n - 1, f; i >= 0; --i) {
    if (i > g && suff[i + n - 1 - f] != i - g)
      suff[i] = min(suff[i + n - 1 - f], i - g);
    else {
      for (g = min(g, f = i); g >= 0 && s[g] == s[g + n - 1 - f]; --g)
        ;
      suff[i] = f - g;
    }
  }

  return suff;
}
