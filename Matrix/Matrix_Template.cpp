#define maxn 500

template <class T> struct Matrix {

  vector<vector<T>> data;
  int m, n;

  Matrix(int m, int n) {
    this->m = m;
    this->n = n;
    data = vector<vector<T>>(m);
    for (int i = 0; i < m; ++i)
      data[i] = vector<T>(n, 0);
  }

  void ident() {
    for (int i = 0; i < m; ++i)
      data[i][i] = 1;
  }

  Matrix<T> operator*(Matrix<T> &mtx) {
    Matrix<T> ans(m, mtx.n);
    for (int i = 0; i < ans.m; ++i)
      for (int j = 0; j < ans.n; ++j)
        for (int k = 0; k < n; ++k)
          ans.data[i][j] += data[i][k] * mtx.data[k][j];
    return ans;
  }

  Matrix<T> operator^(int exp) {
    Matrix<T> ret(m, n);
    Matrix<T> a = *this;

    ret.ident();

    if (exp == 0)
      return ret;
    if (exp == 1)
      return a;

    while (exp) {
      if (exp & 1)
        ret = ret * a;
      a = (a * a);
      exp >>= 1;
    }
    return ret;
  }
};

template <class T> istream &operator>>(istream &in, Matrix<T> &mtx) {
  for (int i = 0; i < mtx.m; ++i)
    for (int j = 0; j < mtx.n; ++j)
      in >> mtx.data[i][j];
  return in;
}

template <class T> ostream &operator<<(ostream &out, Matrix<T> &mtx) {
  for (int i = 0; i < mtx.m; ++i) {
    for (int j = 0; j < mtx.n; j++) {
      if (j)
        out << " ";
      out << mtx.data[i][j];
    }
    out << endl;
  }
  return out;
}

const double eps = 1e-7;

// Determinante
template <class T> double det(Matrix<T> M0) {
  double ans = 1;
  int size = M0.m;

  for (int i = 0, r = 0; i < size; ++i) {
    bool found = false;

    for (int j = r; j < size; ++j)
      if (fabs(M0.data[j][i]) > eps) {
        found = true;

        if (j > r)
          ans = -ans;
        else
          break;

        for (int k = 0; k < size; ++k)
          swap(M0.data[r][k], M0.data[j][k]);
        break;
      }
    if (found) {
      for (int j = r + 1; j < size; ++j) {
        double aux = M0.data[j][i] / M0.data[r][i];
        for (int k = i; k < size; ++k)
          M0.data[j][k] -= aux * M0.data[r][k];
      }
      r++;
    } else
      return 0;
  }

  for (int i = 0; i < size; ++i)
    ans *= M0.data[i][i];
  return ans;
}
