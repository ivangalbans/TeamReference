struct RMQ {
  vector<int> rmq;
  int n;
  RMQ(vector<int> &a) {
    n = a.size();
    buildRMQ(a);
  }
  void buildRMQ(vector<int> &a) {
    int logn = 1;
    for (int k = 1; k < n; k <<= 1)
      ++logn;
    rmq = vector<int>(n * logn);
    vector<int>::iterator b = rmq.begin();
    copy(ALL(a), b);
    for (int k = 1; k < n; k <<= 1) {
      copy(b, b + n, b + n);
      b += n;
      REP(i, n - k) b[i] = min(b[i], b[i + k]);
    }
  }
  int minimum(int x, int y) {
    int z = y - x, k = 0, e = 1, s; // y-x>=e=2^k k up to a
    s = ((z & 0xffff0000) != 0) << 4;
    z >>= s;
    e <<= s;
    k |= s;
    s = ((z & 0x0000ff00) != 0) << 3;
    z >>= s;
    e <<= s;
    k |= s;
    s = ((z & 0x000000f0) != 0) << 2;
    z >>= s;
    e <<= s;
    k |= s;
    s = ((z & 0x0000000c) != 0) << 1;
    z >>= s;
    e <<= s;
    k |= s;
    s = ((z & 0x00000002) != 0) << 0;
    z >>= s;
    e <<= s;
    k |= s;
    return min(rmq[x + n * k], rmq[y + n * k - e + 1]);
  }
};
