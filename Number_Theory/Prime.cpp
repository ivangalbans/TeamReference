const int N = 16000000;
const int sqrtN = sqrt(N);
bool isP[N];

O(N log log N)
void sieve() {
  fill(isP, isP + N, true);
  isP[0] = isP[1] = false;

  for (int i = 4; i < N; i += 2)
    isP[i] = false;

  for (Int i = 3; i < sqrtN; i += 2)
    if (isP[i])
      for (Int j = i * i; j < N; j += 2ll * i)
        isP[j] = false;
}

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
Miller Rabin
[Tested SPOJ PON]
*/
bool witness(Int a, Int s, Int d, Int n) {
  Int x = mod_pow(a, d, n);
  if (x == 1 || x == n - 1)
    return false;
  for (int i = 0; i < s - 1; i++) {
    x = mod_mult(x, x, n);
    if (x == 1)
      return true;
    if (x == n - 1)
      return false;
  }
  return true;
}

bool isPrime(Int n) {
  if (n < 2)
    return false;
  if (n == 2)
    return true;
  if (n % 2 == 0)
    return false;
  Int d = n - 1, s = 0;
  while (d % 2 == 0)
    ++s, d /= 2;
  Int test[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 0};
  for (int i = 0; test[i] && test[i] < n; ++i)
    if (witness(test[i], s, d, n))
      return false; // composite
  return true;      // probably prime
}

/*
Integer Factorization Pollard's Rho
*/
uint64 pollar_rho(uint64 n) // n shouldn't be prime
{
  if (!(n & 1))
    return 2;

  while (true) {
    uint64 x = (uint64)rand() % n, y = x, c = rand() % n;

    if (c == 0 || c == 2)
      c = 1;

    for (int i = 1, k = 2;; i++) {
      x = mod_mult(x, x, n);
      if (x >= c)
        x -= c;
      else
        x += n - c;
      if (x == n)
        x = 0;
      if (x == 0)
        x = n - 1;
      else
        x--;

      uint64 d = __gcd(x > y ? x - y : y - x, n);

      if (d == n)
        break;
      if (d != 1)
        return d;
      if (i == k) {
        y = x;
        k <<= 1;
      }
    }
  }
}

// fact primos de n
vector<pair<Int, Int>> fact(Int n) {
  vector<pair<Int, Int>> fp;
  for (int i = 2; i <= n; ++i) {
    pair<Int, Int> pp = make_pair(i, 0);
    while (!(n % i)) {
      n /= i;
      pp.second++;
    }
    if (pp.second)
      fp.push_back(pp);
  }

  if (n > 1)
    fp.push_back(make_pair(n, 1));

  return fp;
}

vector<Int> primes;

// fact primos de n!
vector<pair<Int, Int>> factF(Int n) {
  vector<pair<Int, Int>> fp;
  Int p;
  for (int i = 0; i < (int)primes.size(); ++i) {
    p = primes[i];
    if (p > n)
      break;

    Int k = n;
    pair<Int, Int> pp = make_pair(p, 0);
    while (k) {
      pp.second += k / p;
      k /= p;
    }
    fp.push_back(pp);
  }

  return fp;
}

/*
        Tested: SPOJ PRIME1, ETFS
        Complexity: O(n log log n)
*/

typedef long long ll;

// primes in [lo, hi)
vector<ll> primes(ll lo, ll hi) {
  const ll M = 1 << 14, SQR = 1 << 16;
  vector<bool> composite(M), small_composite(SQR);
  vector<pair<ll, ll>> sieve;
  for (ll i = 3; i < SQR; i += 2)
    if (!small_composite[i]) {
      ll k = i * i + 2 * i * max(0.0, ceil((lo - i * i) / (2.0 * i)));
      sieve.push_back({2 * i, k});
      for (ll j = i * i; j < SQR; j += 2 * i)
        small_composite[j] = 1;
    }
  vector<ll> ps;
  if (lo <= 2) {
    ps.push_back(2);
    lo = 3;
  }
  for (ll k = lo | 1, low = lo; low < hi; low += M) {
    ll high = min(low + M, hi);
    fill(composite.begin(), composite.end(), 0);
    for (auto &z : sieve)
      for (; z.second < high; z.second += z.first)
        composite[z.second - low] = 1;
    for (; k < high; k += 2)
      if (!composite[k - low])
        ps.push_back(k);
  }
  return ps;
}

vector<ll> primes(ll hi) { return primes(0, hi); }
