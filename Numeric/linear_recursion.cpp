/*
	Linear Recurrence Solver

	Description: Consider 
	x[i+n] = a[0] x[i] + a[1] x[i+1] + ... + a[n-1] x[i+n-1]
	with initial solution x[0], x[1], ..., x[n-1]
	We compute k-th term of x in O(n^2 log k) time.

	Tested: SPOJ REC
	Complexity: O(n^2 log k) time, O(n log k) space
*/

typedef long long ll;

ll linear_recurrence(vector<ll> a, vector<ll> x, ll k)
{
	int n = a.size();
	vector<ll> t(2 * n + 1);
	function<vector<ll>(ll)> rec = [&](ll k)
	{
		vector<ll> c(n);
		if (k < n) c[k] = 1;
		else
		{
			vector<ll> b = rec(k / 2);
			fill(t.begin(), t.end(), 0);
			for (int i = 0; i < n; ++i)
				for (int j = 0; j < n; ++j)
					t[i+j+(k&1)] += b[i]*b[j];
			for (int i = 2*n-1; i >= n; --i)
				for (int j = 0; j < n; ++j)
					t[i-n+j] += a[j]*t[i];
			for (int i = 0; i < n; ++i)
				c[i] = t[i];
		}
		return c;
	};
	vector<ll> c = rec(k);
	ll ans = 0;
	for (int i = 0; i < x.size(); ++i)
		ans += c[i] * x[i];
	return ans;
}

