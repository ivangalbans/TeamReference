#define MAX 100
int rank[MAX], LCP[MAX];

// ""[ (i-d)/2 , (i+d)/2 )""    l[i] = d
vector<int> manacher(string text) {
  int n = text.size(), i, j, k = 0;
  vector<int> rad(n << 1);

  for (i = 0, j = 0; i < (n << 1); i += k, j = max(j - k, 0)) {
    while (i - j >= 0 && i + j + 1 < (n << 1) &&
           text[(i - j) >> 1] == text[(i + j + 1) >> 1])
      ++j;
    rad[i] = j;
    for (k = 1; i - k >= 0 && rad[i] - k >= 0 && rad[i - k] != rad[i] - k; ++k)
      rad[i + k] = min(rad[i - k], rad[i] - k);
  }
  rad.insert(rad.begin(), 0);
  return rad;
}
