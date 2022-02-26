const int oo = 99999999;

#define index_of(as, x)                                                        \
  distance(as.begin(), lower_bound(as.begin(), as.end(), x))

/*
    Tested: LISTA
    Contest 3 COCI 2006-2007
*/
vector<int> lis_fast(const vector<int> &a) {
  const int n = a.size();
  vector<int> A(n, oo), id(n);

  for (int i = 0; i < n; ++i) {
    id[i] = index_of(A, a[i]);
    A[id[i]] = a[i];
  }

  int m = *max_element(id.begin(), id.end());
  vector<int> b(m + 1);

  for (int i = n - 1; i >= 0; --i)
    if (id[i] == m)
      b[m--] = a[i];

  return b;
}
