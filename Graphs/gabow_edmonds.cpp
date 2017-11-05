/*
	Tested: Timus 1099
	Complexity: O(n^3)
*/

struct graph
{
	int n;
	vector<vector<int>> adj;

	graph(int n) : n(n), adj(n) {}

	void add_edge(int u, int v)
	{
		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	queue<int> q;
	vector<int> label, mate, cycle;

	void rematch(int x, int y)
	{
		int m = mate[x];
		mate[x] = y;
		if (mate[m] == x)
		{
			if (label[x] < n)
				rematch(mate[m] = label[x], m);
			else
			{
				int s = (label[x] - n) / n, t = (label[x] - n) % n;
				rematch(s, t);
				rematch(t, s);
			}
		}
	}

	void traverse(int x)
	{
		vector<int> save = mate;
		rematch(x, x);
		for (int u = 0; u < n; ++u)
			if (mate[u] != save[u])
				cycle[u] ^= 1;
		save.swap(mate);
	}

	void relabel(int x, int y)
	{
		cycle = vector<int>(n, 0);
		traverse(x);
		traverse(y);
		for (int u = 0; u < n; ++u)
		{
			if (!cycle[u] || label[u] >= 0)
				continue;
			label[u] = n + x + y * n;
			q.push(u);
		}
	}

	int augment(int r)
	{
		label.assign(n, -2);
		label[r] = -1;
		q = queue<int>();
		for (q.push(r); !q.empty(); q.pop())
		{
			int x = q.front();
			for (int y : adj[x])
			{
				if (mate[y] < 0 && r != y)
				{
					rematch(mate[y] = x, y);
					return 1;
				}
				else if (label[y] >= -1)
					relabel(x, y);
				else if (label[mate[y]] < -1)
				{
					label[mate[y]] = x;
					q.push(mate[y]);
				}
			}
		}
		return 0;
	}

	int maximum_matching()
	{
		mate.assign(n, -2);
		int matching = 0;
		for (int u = 0; u < n; ++u)
			if (mate[u] < 0)
				matching += augment(u);
		return matching;
	}
};
