/*
	Palindromic Tree

	Complexity: O(n)

	Tested: ??
*/

template<size_t maxlen, size_t alpha>
struct PalindromicTree
{
	int go[maxlen + 2][alpha], slink[maxlen + 2], length[maxlen + 2];
	int s[maxlen], slength, size, last;

	int new_node()
	{
		memset(go[size], 0, sizeof go[size]);
		slink[size] = length[size] = 0;
		return size++;
	}

	PalindromicTree() { reset(); }

	void reset()
	{
		size = slength = 0;
		length[new_node()] = -1;
		last = new_node();
	}

	int get_link(int p)
	{
		for (int i = slength - 1; 
			 i - 1 - length[p] < 0 || s[i - 1 - length[p]] != s[i];)
			p = slink[p];
		return p;
	}

	int _extend(int c)
	{
		s[slength++] = c;
		int p = get_link(last), np;
		if (go[p][c]) return go[p][c];
		length[np = new_node()] = 2 + length[p];
		go[p][c] = np;
		if (length[np] == 1) return slink[np] = 1, np;
		p = slink[p];
		slink[np] = go[get_link(p)][c];
		return np;
	}

	void extend(int c) { last = _extend(c); }
};
