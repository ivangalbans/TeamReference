/*
	Tested: USACO OPEN08 (Cow Neighborhoods)
	Complexity: O(n log n)
*/

typedef long long ll;
typedef complex<ll> point;

ll rectilinear_mst(vector<point> ps)
{
	vector<int> id(ps.size());
	iota(id.begin(), id.end(), 0);

	struct edge
	{
		int src, dst;
		ll weight;
	};

	vector<edge> edges;
	for (int s = 0; s < 2; ++s)
	{
		for (int t = 0; t < 2; ++t)
		{
			sort(id.begin(), id.end(), [&](int i, int j)
			{
				return real(ps[i] - ps[j]) < imag(ps[j] - ps[i]);
			});

			map<ll, int> sweep;

			for (int i : id)
			{
				for (auto it = sweep.lower_bound(-imag(ps[i]));
						it != sweep.end(); sweep.erase(it++))
				{
					int j = it->second;
					if (imag(ps[j] - ps[i]) < real(ps[j] - ps[i]))
						break;
					ll d = abs(real(ps[i] - ps[j])) 
							+ abs(imag(ps[i] - ps[j]));
					edges.push_back({ i, j, d });
				}
				sweep[-imag(ps[i])] = i;
			}

			for (auto &p : ps)
				p = point(imag(p), real(p));
		}

		for (auto &p : ps)
			p = point(-real(p), imag(p));
	}

	ll cost = 0;
	sort(edges.begin(), edges.end(), [](edge a, edge b)
	{
		return a.weight < b.weight;
	});

	union_find uf(ps.size());
	for (edge e : edges)
		if (uf.join(e.src, e.dst))
			cost += e.weight;

	return cost;
}
