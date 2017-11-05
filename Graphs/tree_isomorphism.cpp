/*
	Tested: SPOJ TREEISO
	Complexity: O(n log n)
*/

#define all(c) (c).begin(), (c).end()

struct tree
{
	int n;
	vector<vector<int>> adj;

	tree(int n) : n(n), adj(n) {}

	void add_edge(int src, int dst)
	{
		adj[src].push_back(dst);
		adj[dst].push_back(src);
	}

	vector<int> centers()
	{
		vector<int> prev;
		int u = 0;
		for (int k = 0; k < 2; ++k)
		{
			queue<int> q;
			prev.assign(n, -1);
			for (q.push(prev[u] = u); !q.empty(); q.pop())
			{
				u = q.front();
				for (auto v : adj[u])
				{
					if (prev[v] >= 0)
						continue;
					q.push(v);
					prev[v] = u;
				}
			}
		}

		vector<int> path = { u };
		while (u != prev[u])
			path.push_back(u = prev[u]);

		int m = path.size();
		if (m % 2 == 0)
			return {path[m/2-1], path[m/2]};
		else
			return {path[m/2]};
	}

	vector<vector<int>> layer;
	vector<int> prev;

	int levelize(int r)
	{
		prev.assign(n, -1);
		prev[r] = n;
		layer = {{r}};
		while (1)
		{
			vector<int> next;
			for (int u : layer.back())
				for (int v : adj[u])
				{
					if (prev[v] >= 0)
						continue;
					prev[v] = u;
					next.push_back(v);
				}

			if (next.empty())
				break;
			layer.push_back(next);
		}
		return layer.size();
	}
};

bool isomorphic(tree S, int s, tree T, int t)
{
	if (S.n != T.n)
		return false;
	if (S.levelize(s) != T.levelize(t))
		return false;

	vector<vector<int>> longcodeS(S.n + 1), longcodeT(T.n + 1);
	vector<int> codeS(S.n), codeT(T.n);
	for (int h = (int) S.layer.size() - 1; h >= 0; --h)
	{
		map<vector<int>, int> bucket;
		for (int u : S.layer[h])
		{
			sort(all(longcodeS[u]));
			bucket[longcodeS[u]] = 0;
		}
		for (int u : T.layer[h])
		{
			sort(all(longcodeT[u]));
			bucket[longcodeT[u]] = 0;
		}

		int id = 0;
		for (auto &p : bucket)
			p.second = id++;
		for (int u : S.layer[h])
		{
			codeS[u] = bucket[longcodeS[u]];
			longcodeS[S.prev[u]].push_back(codeS[u]);
		}
		for (int u : T.layer[h])
		{
			codeT[u] = bucket[longcodeT[u]];
			longcodeT[T.prev[u]].push_back(codeT[u]);
		}
	}

	return codeS[s] == codeT[t];
}

bool isomorphic(tree S, tree T)
{
	auto x = S.centers(), y = T.centers();
	if (x.size() != y.size())
		return false;
	if (isomorphic(S, x[0], T, y[0]))
		return true;
	return x.size() > 1 && isomorphic(S, x[1], T, y[0]);
}
