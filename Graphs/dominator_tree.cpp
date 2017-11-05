/*
	Dominator Tree (Lengauer-Tarjan)

	Tested: SPOJ EN
	Complexity: O(m log n)
*/

struct graph
{
	int n;
	vector<vector<int>> adj, radj;

	graph(int n) : n(n), adj(n), radj(n) {}

	void add_edge(int src, int dst)
	{
		adj[src].push_back(dst);
		radj[dst].push_back(src);
	}

	vector<int> rank, semi, low, anc;

	int eval(int v)
	{
		if (anc[v] < n && anc[anc[v]] < n)
		{
			int x = eval(anc[v]);
			if (rank[semi[low[v]]] > rank[semi[x]])
				low[v] = x;
			anc[v] = anc[anc[v]];
		}
		return low[v];
	}

	vector<int> prev, ord;

	void dfs(int u)
	{
		rank[u] = ord.size();
		ord.push_back(u);
		for (auto v : adj[u])
		{
			if (rank[v] < n)
				continue;
			dfs(v);
			prev[v] = u;
		}
	}

	vector<int> idom; // idom[u] is an immediate dominator of u

	void dominator_tree(int r)
	{
		idom.assign(n, n);
		prev = rank = anc = idom;
		semi.resize(n);
		iota(semi.begin(), semi.end(), 0);
		low = semi;
		ord.clear();
		dfs(r);

		vector<vector<int>> dom(n);
		for (int i = (int) ord.size() - 1; i >= 1; --i)
		{
			int w = ord[i];
			for (auto v : radj[w])
			{
				int u = eval(v);
				if (rank[semi[w]] > rank[semi[u]])
					semi[w] = semi[u];
			}
			dom[semi[w]].push_back(w);
			anc[w] = prev[w];
			for (int v : dom[prev[w]])
			{
				int u = eval(v);
				idom[v] = (rank[prev[w]] > rank[semi[u]] 
					? u : prev[w]);
			}
			dom[prev[w]].clear();
		}

		for (int i = 1; i < (int) ord.size(); ++i)
		{
			int w = ord[i];
			if (idom[w] != semi[w])
				idom[w] = idom[idom[w]];
		}
	}

	vector<int> dominators(int u)
	{
		vector<int> S;
		for (; u < n; u = idom[u])
			S.push_back(u);
		return S;
	}
};
