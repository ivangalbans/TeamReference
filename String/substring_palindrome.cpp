using System;
namespace hash {
class Program {
  static int MAXN = 100000 + 10;
  static long[] fh, bh, prime;
  static long mod = 1000000009;
  static long x = 1223;
  static string s;
  static int n;

  static void prime_power(int n) {
    prime[0] = 1;
    for (int i = 1; i <= n + 5; i++)
      prime[i] = (prime[i - 1] * x) % mod;
  }

  static void compute_hash(string s) {
    for (int i = 1, j = n; i <= n; j--, i++) {
      fh[i] = (fh[i - 1] + s[i - 1] * prime[i]) % mod;
      bh[j] = (bh[j + 1] + s[j - 1] * prime[i]) % mod;
    }
  }

  static bool subtring_palindrome(int l, int r) {
    ++l;
    ++r;
    long h1 = (fh[r] - fh[l - 1] + mod) % mod;
    long h2 = (bh[l] - bh[r + 1] + mod) % mod;

    if (l <= n - r + 1) {
      int pow = (n - r + 1) - l;
      h1 = (h1 * prime[pow]) % mod;
    } else {
      int pow = l - (n - r + 1);
      h2 = (h2 * prime[pow]) % mod;
    }
    return h1 == h2;
  }

  static void Main(string[] args) {
    fh = new long[MAXN];
    bh = new long[MAXN];
    prime = new long[MAXN];

    string s = Console.ReadLine();
    n = s.Length;
    prime_power(s.Length);
    compute_hash(s);

    int q = int.Parse(Console.ReadLine());
    for (int i = 0; i < q; ++i) {
      int[] query = Array.ConvertAll(Console.ReadLine().Split(), int.Parse);
      Console.WriteLine("{0}",
                        subtring_palindrome(query[0], query[1]) ? "YES" : "NO");
    }
  }
}
} // namespace hash
