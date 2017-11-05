/*
	Tested: ??????
*/

// n-cantidad de personas, m es la longitud del salto.
// comienza en la k-esima persona.
ll josephus(ll n, ll m, ll k)
{
	ll x = -1;
	for (ll i = n - k + 1; i <= n; ++i)
		x = (x + m) % i;
	return x;
}

ll josephus_inv(ll n, ll m, ll x)
{
	for (ll i = n;; i--)
	{
		if (x == i)
			return n - i;
		x = (x - m % i + i) % i;
	}
	return -1;
}
