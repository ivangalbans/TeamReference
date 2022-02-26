template <class T> struct fraction {
  T n, d;

  fraction() {
    n = 0;
    d = 1;
  }

  fraction(T _n, T _d) {
    n = _n;
    d = _d;
  }
};

template <class T> fraction<T> operator+(fraction<T> &a, fraction<T> &b) {
  T mcm = a.d * b.d;
  return fraction<T>(mcm / a.d * a.n + mcm / b.d * b.n, mcm);
}

template <class T> fraction<T> operator*(fraction<T> &a, fraction<T> &b) {
  return fraction<T>(a.n * b.n, a.d * b.d);
}

template <class T> istream &operator>>(istream &in, fraction<T> &frac) {
  in >> frac.n >> frac.d;
  return in;
}

template <class T> ostream &operator<<(ostream &out, fraction<T> &frac) {
  out << frac.n << "/" << frac.d;
  return out;
}

template <class T> bool operator<(fraction<T> a, fraction<T> b) {
  return a.n * b.d < a.d * b.n;
}
