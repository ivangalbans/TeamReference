/*
        Binary Multiplication
        [Tested Timus 1141,1204]**
*/
Int mod_mult(Int a, Int b, Int mod) {
  Int x = 0;
  while (b) {
    if (b & 1)
      x = (x + a) % mod;
    a = (a << 1) % mod;
    b >>= 1;
  }
  return x;
}

/*
        Binary Exponentiation
        [Tested Timus 1141,1204]**
*/
Int mod_pow(Int a, Int n, Int mod) {
  Int x = 1;
  while (n) {
    if (n & 1)
      x = mod_mult(x, a, mod);
    a = mod_mult(a, a, mod);
    n >>= 1;
  }
  return x;
}

/*
        Extended Euclidean algorithm
        Solve ax+by = (a,b)
        Works well even for negative numbers
        [Tested Timus 1141,1204]**
*/
int gcd(int a, int b, int &x, int &y) {
  if (b == 0) {
    x = 1;
    y = 0;
    return a;
  }
  int r = gcd(b, a % b, y, x);
  y -= a / b * x;
  return r;
}

/*
Euler's function
phi(p^a) = p^a - p^(a-1)
(a,b) = 1 => phi(a*b) = phi(a)*phi(b)
[Tested Timus 1141]*
*/
int phi(int a) {
  int b = a;
  for (int i = 2; i * i <= a; ++i)
    if (a % i == 0) {
      b = b / i * (i - 1);
      do
        a /= i;
      while (a % i == 0);
    }
  if (a > 1)
    b = b / a * (a - 1);
  return b;
}

/*
Modular Inverse
        (a,m) = 1
        Solves a*x = 1 (m)
        [Tested Timus 1141, 1204]**
*/
int inverse(int a, int m) {
  int x, y;
  if (gcd(a, m, x, y) != 1)
    return 0;
  return (x % m + m) % m;
}

/*
        Baby-Step-Giant-Step Algorithm
        O(sqrt(m)log(m))
        Solve a^x = b(mod m)
        [TESTED LightOJ 1325 05/11/2014]
*/
Int discrete_log(Int a, Int b, Int m) {
  map<Int, Int> hash;
  Int n = phi(m), k = sqrt(n);

  for (Int i = 0, t = 1; i < k; i++) {
    hash[t] = i;
    t = (t * a) % m;
  }
  Int c = mod_pow(a, n - k, m);
  for (Int i = 0; i * k < n; i++) {
    if (hash.find(b) != hash.end())
      return (i * k + hash[b]) % n;

    b = (b * c) % m;
  }
  return -1;
}

/*
        Solves a*x = b (mod p)
        [Tested CodeChef Quadratic Equations]
*/
long solve_linear(long a, long b, int p) { return (b * inverse(a, p)) % p; }

/*
        Solve x=ai(mod mi)
        For any i and j, (mi,mj)|ai-aj.
        Return x0 in [0,[M]).
        M = m1m2..mn
        All solutions are x=x0+t[M].
*/
int linear_con(int a[], int m[], int n) {
  int u = a[0], v = m[0], p, q, r, t;
  for (int i = 1; i < n; i++) {
    r = gcd(v, m[i], p, q);
    t = v;
    v = v / r * m[i];
    u = ((a[i] - u) / r * p * t + u) % v;
  }
  if (u < 0)
    u += v;
  return u;
}

/*
        Solve x = ai(mod mi)
        For any i and j, (mi,mj)==1.
        Returns x0 in [0,M).
        M = m1m2..mn
        All solutions are x=x0 + tM.
*/
int chinese(int a[], int m[], int n) {
  int s = 1, t, ans = 0, p, q;
  for (int i = 0; i < n; i++)
    s *= m[i];
  for (int i = 0; i < n; i++) {
    t = s / m[i];
    gcd(t, m[i], p, q);
    ans = (ans + t * p * a[i]) % s;
  }
  if (ans < 0)
    ans += s;
  return ans;
}

/*
Kth discrete roots of a (mod n)
x^k = a (n)
When (k, phi(n)) = 1
[Tested Timus 1141]**
*/
int discrete_root(int k, int a, int n) {
  int _phi = phi(n);
  int s = (int)inverse(k, _phi);
  return (int)mod_pow(a, s, n);
}

/*
Tonelli Shank's algorithm
Solves x^2=a (mod p)
[Tested CodeChef Quadratic Equations, Timus 1132]
Warning: Precompute primes to avoid TLE
*/
int solve_quadratic(int a, int p) {
  if (a == 0)
    return 0;
  if (p == 2)
    return a;
  if (mod_pow(a, (p - 1) / 2, p) != 1)
    return -1;

  int phi = p - 1;
  int n = 0, k = 0;

  while (phi % 2 == 0) {
    phi /= 2;
    n++;
  }

  k = phi;
  int q = 0;

  for (int j = 2; j < p; j++)
    if (mod_pow(j, (p - 1) / 2, p) == p - 1) {
      q = j;
      break;
    }

  int t = mod_pow(a, (k + 1) / 2, p);
  int r = mod_pow(a, k, p);

  while (r != 1) {
    int i = 0, v = 1;
    while (mod_pow(r, v, p) != 1) {
      v *= 2;
      i++;
    }

    int e = mod_pow(2, n - i - 1, p);
    int u = mod_pow(q, k * e, p);

    t = (t * u) % p;
    r = (r * u * u) % p;
  }

  return t;
}

/*
Solves a*x^2 + b*x + c = 0 (mod p)
[Tested CodeChef Quadratic Equations]
*/
set<Int> solve_quadratic(Int a, Int b, Int c, int p) {
  set<Int> ans;
  if (c == 0)
    ans.insert(0L);
  if (a == 0)
    ans.insert(solve_linear((p - b) % p, c, p));
  else if (p == 2 && (a + b + c) % 2 == 0)
    ans.insert(1L);
  else {
    Int r = ((b * b) % p - (4 * a * c) % p + p) % p;
    Int x = solve_quadratic(r, p);
    if (x == -1)
      return ans;
    Int w = solve_linear((2 * a) % p, (x - b + p) % p, p);
    ans.insert(w);
    w = solve_linear((2 * a) % p, (p - x - b + p) % p, p);
    ans.insert(w);
  }
  return ans;
}

/*
Primitive roots
[Tested Timus 1268]
Warning: Precompute primes to avoid TLE
Only: m = 1, p^k , n = 2p^k (p prime > 2),
          m = 2, m = 4
*/
int primitive_root(int m, int p[]) {
  if (m == 1)
    return 0;
  if (m == 2)
    return 1;
  if (m == 4)
    return 3;

  int t = m;
  if ((t & 1) == 0)
    t >>= 1;

  for (int i = 0; p[i] * p[i] <= t; ++i) {
    if (t % p[i])
      continue;
    do
      t /= p[i];
    while (t % p[i] == 0);
    if (t > 1 || p[i] == 2)
      return 0;
  }

  int f[100];
  int x = phi(m), y = x, n = 0;

  for (int i = 0; p[i] * p[i] <= y; ++i) {
    if (y % p[i])
      continue;
    do
      y /= p[i];
    while (y % p[i] == 0);
    f[n++] = p[i];
  }

  if (y > 1)
    f[n++] = y;

  for (int i = 1; i < m; ++i) {
    if (__gcd(i, m) > 1)
      continue;
    bool flag = true;

    for (int j = 0; j < n; ++j)
      if (mod_pow(i, x / f[j], m) == 1) {
        flag = false;
        break;
      }

    if (flag)
      return i;
  }
  return 0;
}

typedef long long ll;

ll divisor_sigma(ll n) {
  ll sigma = 0, d = 1;
  for (; d * d < n; ++d)
    if (n % d == 0)
      sigma += d + n / d;
  if (d * d == n)
    sigma += d;
  return sigma;
}

// sigma(n) for all n in [lo, hi)
vector<ll> divisor_sigma(ll lo, ll hi) {
  vector<ll> ps = primes(sqrt(hi) + 1);
  vector<ll> res(hi - lo), sigma(hi - lo, 1);
  iota(res.begin(), res.end(), lo);
  for (ll p : ps)
    for (ll k = ((lo + (p - 1)) / p) * p; k < hi; k += p) {
      ll b = 1;
      while (res[k - lo] > 1 && res[k - lo] % p == 0) {
        res[k - lo] /= p;
        b = 1 + b * p;
      }
      sigma[k - lo] *= b;
    }
  for (ll k = lo; k < hi; ++k)
    if (res[k - lo] > 1)
      sigma[k - lo] *= (1 + res[k - lo]);
  return sigma; // sigma[k-lo] = sigma(k)
}

typedef long long ll;

ll mobius_mu(ll n) {
  if (n == 0)
    return 0;
  ll mu = 1;
  for (ll x = 2; x * x <= n; ++x)
    if (n % x == 0) {
      mu = -mu;
      n /= x;
      if (n % x == 0)
        return 0;
    }
  return n > 1 ? -mu : mu;
}

// phi(n) for all n in [lo, hi)
vector<ll> mobius_mu(ll lo, ll hi) {
  vector<ll> ps = primes(sqrt(hi) + 1);
  vector<ll> res(hi - lo), mu(hi - lo, 1);
  iota(res.begin(), res.end(), lo);
  for (ll p : ps)
    for (ll k = ((lo + (p - 1)) / p) * p; k < hi; k += p) {
      mu[k - lo] = -mu[k - lo];
      if (res[k - lo] % p == 0) {
        res[k - lo] /= p;
        if (res[k - lo] % p == 0) {
          mu[k - lo] = 0;
          res[k - lo] = 1;
        }
      }
    }
  for (ll k = lo; k < hi; ++k)
    if (res[k - lo] > 1)
      mu[k - lo] = -mu[k - lo];
  return mu; // mu[k-lo] = mu(k)
}
