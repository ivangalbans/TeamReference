/*
	Maximum Flow (Goldberg-Tarjan)

	Complexity: O(n^3) faster than Dinic in most cases

	Tested: http://www.spoj.com/problems/FASTFLOW/
*/

template<typename flow_type>
struct goldberg_tarjan
{
	struct edge
	{
		size_t src, dst, rev;
		flow_type flow, cap;
	};

	int n;
	vector<vector<edge>> adj;

	goldberg_tarjan(int n) : n(n), adj(n) {}

	void add_edge(size_t src, size_t dst, flow_type cap, flow_type rcap = 0)
	{
		adj[src].push_back({ src, dst, adj[dst].size(), 0, cap });
		if (src == dst)	adj[src].back().rev++;
		adj[dst].push_back({ dst, src, adj[src].size() - 1, 0, rcap });
	}

	flow_type max_flow(int source, int sink)
	{
		vector<flow_type> excess(n);
		vector<int> dist(n), active(n), count(2 * n);
		queue<int> q;
		auto enqueue = [&](int v)
		{
			if (!active[v] && excess[v] > 0)
			{
				active[v] = true;
				q.push(v);
			}
		};
		auto push = [&](edge &e)
		{
			flow_type f = min(excess[e.src], e.cap - e.flow);
			if (dist[e.src] <= dist[e.dst] || f == 0) return;
			e.flow += f;
			adj[e.dst][e.rev].flow -= f;
			excess[e.dst] += f;
			excess[e.src] -= f;
			enqueue(e.dst);
		};
		dist[source] = n;
		active[source] = active[sink] = true;
		count[0] = n - 1;
		count[n] = 1;
		for (int u = 0; u < n; ++u)
			for (edge &e : adj[u]) e.flow = 0;
		for (edge &e : adj[source])
		{
			excess[source] += e.cap;
			push(e);
		}
		for (int u; !q.empty(); q.pop())
		{
			active[u = q.front()] = false;
			for (auto &e : adj[u]) push(e);
			if (excess[u] > 0)
			{
				if (count[dist[u]] == 1)
				{
					int k = dist[u]; // Gap Heuristics
					for (int v = 0; v < n; v++)
					{
						if (dist[v] < k)
							continue;
						count[dist[v]]--;
						dist[v] = max(dist[v], n + 1);
						count[dist[v]]++;
						enqueue(v);
					}
				}
				else
				{
					count[dist[u]]--; // Relabel
					dist[u] = 2 * n;
					for (edge &e : adj[u])
						if (e.cap > e.flow)
							dist[u] = min(dist[u],
								 dist[e.dst] + 1);
					count[dist[u]]++;
					enqueue(u);
				}
			}
		}
		flow_type flow = 0;
		for (edge e : adj[source])
			flow += e.flow;
		return flow;
	}
};
