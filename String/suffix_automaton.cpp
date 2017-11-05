/*
	Generalized Suffix Automaton

	Complexity: O(n)

	Tested:
	- http://codeforces.com/contest/616/problem/F
	- http://codeforces.com/contest/452/problem/E
	- http://codeforces.com/contest/204/problem/E
*/


template<size_t maxlen, size_t alpha>
struct SuffixAutomaton
{
	int go[2 * maxlen][alpha], slink[2 * maxlen], length[2 * maxlen];
	int size, last;

	int new_node()
	{
		memset(go[size], 0, sizeof go[size]);
		slink[size] = length[size] = 0;
		return size++;
	}

	SuffixAutomaton() { reset(); }

	void reset()
	{
		size = last = 0;
		new_node();
		slink[0] = -1;
	}

	int _extend(int c)
	{
		int p, q, np, nq;
		if (q = go[last][c])
		{
			if (length[q] == 1 + length[last]) return q;
			int nq = new_node();
			length[nq] = 1 + length[last];
			memcpy(go[nq], go[q], sizeof go[q]);
			slink[nq] = slink[q];
			slink[q] = nq;
			for (p = last; p != -1 && go[p][c] == q; p = slink[p])
				go[p][c] = nq;
			return nq;
		}
		np = new_node();
		length[np] = 1 + length[last];
		for (p = last; p != -1 && !go[p][c]; p = slink[p])
			go[p][c] = np;
		if (p == -1) return slink[np] = 0, np;
		if (length[q = go[p][c]] == 1 + length[p]) return slink[np] = q, np;
		nq = new_node();
		length[nq] = 1 + length[p];
		memcpy(go[nq], go[q], sizeof go[q]);
		slink[nq] = slink[q];
		slink[q] = slink[np] = nq;
		for (; p != -1 && go[p][c] == q; p = slink[p])
			go[p][c] = nq;
		return np;
	}

	void extend(int c) { last = _extend(c); }

	int bucket[maxlen + 1], order[2 * maxlen];

	void top_sort()
	{
		int maxl = 0;
		for (int e = 0; e < size; ++e)
			maxl = max(maxl, length[e]);
		for (int l = 0; l <= maxl; ++l)
			bucket[l] = 0;
		for (int e = 0; e < size; ++e)
			++bucket[length[e]];
		for (int l = 1; l <= maxl; ++l)
			bucket[l] += bucket[l - 1];
		for (int e = 0; e < size; ++e)
			order[--bucket[length[e]]] = e;
	}
};
