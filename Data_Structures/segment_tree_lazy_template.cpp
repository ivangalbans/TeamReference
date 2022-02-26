#define Left(x) ((x << 1) + 1)
#define Right(x) ((x << 1) + 2)

struct Node {
  bool null;
  vector<int> digits;
  bool active;
  Node operator+(const Node &n) const {
    if (null)
      return n;
    if (n.null)
      return *this;

    vector<int> dig(10, 0);
    for (int i = 0; i < 10; ++i)
      dig[i] = digits[i] + n.digits[i];
    return {false, dig};
  }
  Node operator*(const int n) const {
    if (null)
      return *this;
    vector<int> dig(10, 0);
    for (int i = 0; i < 10; ++i)
      dig[i] = digits[i] * n;
    return {false, dig};
  }
  int answer();
  void init(const string &k) // inicializa un nodo del st
  {
    digits = vector<int>(10, 0);
    for (auto x : k)
      digits[x - '0']++;
    null = false;
  }
};

template <typename T> struct ST {
private:
  vector<T> st, lazy;
  int size;
  void build(int node, int nodeL, int nodeR, const vector<string> &v) {
    if (nodeL == nodeR) {
      st[node].init(v[nodeL]);
      return;
    }
    int m = (nodeL + nodeR) / 2;
    build(Left(node), nodeL, m, v);
    build(Right(node), m + 1, nodeR, v);
    st[node] = st[Left(node)] + st[Right(node)];
  }
  void push(int node, int nodeL, int nodeR) {
    if (lazy[node].active) {
      int m = (nodeL + nodeR) / 2;
      lazy[Left(node)] = lazy[node];
      lazy[Right(node)] = lazy[node];
      lazy[Left(node)].active = true;
      lazy[Right(node)].active = true;
      st[Left(node)] = lazy[node] * (m - nodeL + 1);
      st[Right(node)] = lazy[node] * (nodeR - m);
      lazy[node].active = false;
    }
  }

  void update(int node, int nodeL, int nodeR, int l, int r, const T &val) {
    if (l > nodeR || r < nodeL)
      return;
    if (nodeL >= l && nodeR <= r) {
      st[node] = val * (nodeR - nodeL + 1);
      lazy[node] = val;
      lazy[node].active = true;
      return;
    }
    push(node, nodeL, nodeR);

    int m = (nodeL + nodeR) / 2;
    update(Left(node), nodeL, m, l, r, val);
    update(Right(node), m + 1, nodeR, l, r, val);
    st[node] = st[Left(node)] + st[Right(node)];
  }

  T query(int node, int nodeL, int nodeR, int l, int r) {
    if (l > nodeR || r < nodeL)
      return {true};
    if (nodeL >= l && nodeR <= r)
      return st[node];
    push(node, nodeL, nodeR);
    int m = (nodeL + nodeR) / 2;
    return query(Left(node), nodeL, m, l, r) +
           query(Right(node), m + 1, nodeR, l, r);
  }

public:
  ST(const vector<string> &v) {
    size = v.size();
    st = lazy = vector<T>(4 * size, {true});
    build(0, 0, size - 1, v);
  }
  void update(int l, int r, const T &val) { update(0, 0, size - 1, l, r, val); }
  T query(int l, int r) { return query(0, 0, size - 1, l, r); }
};

vector<string> dats;

int main() {
  // build
  dats = vector<string>(N); // read
  ST<Node> st = ST<Node>(dats);
  //****
  // update ***
  Node tmp;
  tmp.init(value); /*string this case*/
  st.update(b - 1, c - 1, tmp);
  //*****
  st.query(b - 1, c - 1).answer();
  return 0;
}
