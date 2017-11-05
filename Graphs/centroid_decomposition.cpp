/*
    Centroid decomposition of a tree.
    Find the centroid of the subtree that contains node c.
    
    Nodes availables are those which aren't marked, i.e mk[u] == False
*/

vi adj[maxn];
bool mk[maxn];
int q[maxn], p[maxn], sz[maxn], mc[maxn];

int centroid(int c){
	int b = 0, e = 0;
	q[e++] = c,	p[c] = -1, sz[c] = 1, mc[c] = 0;

	while (b < e){
		int u = q[b++];
		for (auto v : adj[u]) if (v != p[u] && !mk[v])
				p[v] = u, sz[v] = 1, mc[v] = 0, q[e++] = v;
	}

	for (int i = e - 1; ~i; --i){
		int u = q[i];
		int bc = max(e - sz[u], mc[u]);
		if (2 * bc <= e) return u;
		sz[p[u]] += sz[u], mc[p[u]] = max(mc[p[u]], sz[u]);
	}

	assert(false);
	return -1;
}