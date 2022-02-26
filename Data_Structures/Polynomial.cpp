template <class T> struct polynomial {
  int deg;
  vector<T> coef;

  polynomial() {}

  polynomial(int _deg) {
    deg = _deg;
    coef = vector<T>(deg + 1, 0);
  }

  polynomial(int _deg, vector<T> _coef) {
    deg = _deg;
    coef = _coef;
  }

  T eval(double x) {
    T y = 0;
    double pow = 1;
    for (int i = 0; i <= deg; ++i) {
      y = y + coef[i] * pow;
      pow = pow * x;
    }
    return y;
  }
};

template <class T> istream &operator>>(istream &in, polynomial<T> &pol) {
  in >> pol.deg;
  pol.coef = vector<T>(pol.deg + 1);

  for (int i = 0; i <= pol.deg; ++i)
    in >> pol.coef[i];
  return in;
}

void literal(ostream &out, int i) {
  if (i == 0)
    return;
  if (i == 1) {
    out << "x";
    return;
  }
  out << "x^" << i;
}

template <class T> ostream &operator<<(ostream &out, polynomial<T> pol) {
  bool first = true;
  for (int i = pol.deg; i > 0; --i) {
    if (pol.coef[i] != 0) {
      if (first) {
        if (pol.coef[i] != 1 && pol.coef[i] != -1)
          out << pol.coef[i];
        else if (pol.coef[i] == -1)
          out << "-";
      } else {
        if (pol.coef[i] == 1)
          out << "+";
        else if (pol.coef[i] == -1)
          out << "-";
        else if (pol.coef[i] > 0)
          out << "+" << pol.coef[i];
        else
          out << pol.coef[i];
      }

      if (i == 1)
        out << "x";
      else if (i > 1)
        out << "x^" << i;

      first = false;
    }
  }

  if (first) {
    out << pol.coef[0];
    return out;
  } else {
    if (pol.coef[0] != 0) {
      if (pol.coef[0] > 0)
        out << "+";
      out << pol.coef[0];
    }
  }

  return out;
}

template <class T> polynomial<T> operator+(polynomial<T> &a, polynomial<T> &b) {
  polynomial<T> sum;

  if (a.deg >= b.deg)
    sum = a;
  else
    sum = b;

  for (int i = 0; i <= min(a.deg, b.deg); ++i)
    sum.coef[i] = a.coef[i] + b.coef[i];
  return sum;
}

template <class T>
polynomial<T> operator*(polynomial<T> &p1, polynomial<T> &p2) {
  polynomial<T> mult(p1.deg + p2.deg);
  for (int i = 0; i <= p1.deg; ++i)
    for (int j = 0; j <= p2.deg; ++j)
      mult.coef[i + j] = mult.coef[i + j] + p1.coef[i] * p2.coef[j];
  return mult;
}
