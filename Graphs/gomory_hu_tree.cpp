/*
	Gomory-Hu tree

	Tested: SPOj MCQUERY
	Complexity: O(n-1) max-flow call
*/

template<typename flow_type>
struct edge
{
	int src, dst;
	flow_type cap;
};

template<typename flow_type>
vector<edge<flow_type>> gomory_hu(dinic<flow_type> &adj)
{
	int n = adj.n;

	vector<edge<flow_type>> tree;
	vector<int> parent(n);

	for (int u = 1; u < n; ++u)
	{
		tree.push_back({ u, parent[u], adj.max_flow(u, parent[u]) });
		for (int v = u + 1; v < n; ++v)
			if (adj.level[v] == -1 && parent[v] == parent[u])
				parent[v] = u;
	}

	return tree;
}