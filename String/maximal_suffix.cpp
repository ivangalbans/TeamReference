/*
        Complexity: O(n)
*/

int maximal_suffix(const string &s) {
  int n = s.length(), i = 0, j = 1;

  for (int k = 0; j < n - 1; k = 0) {
    while (j + k < n - 1 && s[i + k] == s[j + k])
      ++k;

    if (s[i + k] < s[j + k]) {
      i += (k / (j - i) + 1) * (j - i);
      j = i + 1;
    } else
      j += k + 1;
  }

  return i;
}
