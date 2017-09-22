/*
	Tested: MIT 2008 Team Contest 1 (Rectangles) 
	Complexity: O(n log n)
*/

typedef long long ll;

struct rectangle
{
	ll xl, yl, xh, yh;
};

ll rectangle_area(vector<rectangle> &rs)
{
	vector<ll> ys; // coordinate compression
	for (auto r : rs)
	{
		ys.push_back(r.yl);
		ys.push_back(r.yh);
	}
	sort(ys.begin(), ys.end());
	ys.erase(unique(ys.begin(), ys.end()), ys.end());

	int n = ys.size(); // measure tree
	vector<ll> C(8 * n), A(8 * n);
	function<void(int, int, int, int, int, int)> aux =
			[&](int a, int b, int c, int l, int r, int k)
			{
				if ((a = max(a,l)) >= (b = min(b,r))) return;
				if (a == l && b == r) C[k] += c;
				else
				{
					aux(a, b, c, l, (l+r)/2, 2*k+1);
					aux(a, b, c, (l+r)/2, r, 2*k+2);
				}
				if (C[k]) A[k] = ys[r] - ys[l];
				else A[k] = A[2*k+1] + A[2*k+2];
			};

	struct event
	{
		ll x, l, h, c;
	};
	// plane sweep
	vector<event> es;
	for (auto r : rs)
	{
		int l = lower_bound(ys.begin(), ys.end(), r.yl) - ys.begin();
		int h = lower_bound(ys.begin(), ys.end(), r.yh) - ys.begin();
		es.push_back({ r.xl, l, h, +1 });
		es.push_back({ r.xh, l, h, -1 });
	}
	sort(es.begin(), es.end(), [](event a, event b)
			{return a.x != b.x ? a.x < b.x : a.c > b.c;});
	ll area = 0, prev = 0;
	for (auto &e : es)
	{
		area += (e.x - prev) * A[0];
		prev = e.x;
		aux(e.l, e.h, e.c, 0, n, 0);
	}
	return area;
}
