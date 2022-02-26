/*
 *   Performance:
 *   0-based
 *   To start the index on 1
 *   lowbit  --> O(1)
 *   query  --> O(log N)
 *   update --> O(log N)
 */
template <class T> struct abi {

  vector<T> ft;
  abi(int n) : ft(n + 1, 0) {}

  int lowbit(int x) { return x & -x; }

  // item[pos] += val
  void update(int pos, T val) {
    for (; pos < (int)ft.size(); pos += lowbit(pos))
      ft[pos] += val;
  }

  // Give sum[0...pos]
  T query(int pos) {
    T sum = 0;
    for (; pos > 0; pos -= lowbit(pos))
      sum += ft[pos];
    return sum;
  }

  // Give sum[l...r]
  T query(int l, int r) {
    l = (l > 0) ? l - 1 : 0;
    return query(r) - query(l);
  }

  int highestOneBit(int n) {
    int shift = 31 - (__builtin_clz(n));
    int ans = 1;
    ans <<= shift;
    return ans;
  }

  // Return min(p|sum[0,p]>=sum)
  int lower_bound(int sum) {
    --sum;
    int pos = 0;
    for (int blockSize = highestOneBit(ft.size()); blockSize; blockSize >>= 1) {
      int nextPos = pos + blockSize;
      if (nextPos < (int)ft.size() && sum >= ft[nextPos]) {
        sum -= ft[nextPos];
        pos = nextPos;
      }
    }
    return pos + 1;
  }

  // number of free places in [0, x]
  int getZeros(int x) { return x < 0 ? 0 : x + 1 - query(x); }

  int getZeros(int x1, int x2) {
    int s = getZeros(x2) - getZeros(x1 - 1);
    return x1 <= x2 ? s : s + getZeros(ft.size() - 1);
  }
};
