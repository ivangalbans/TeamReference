/*
	Complexity: O(n)
*/

int minimum_rotation(const string &s)
{
	int n = s.length(), i = 0, j = 1, k = 0;

	while (i + k < 2 * n && j + k < 2 * n)
	{
		char a = i + k < n ? s[i + k] : s[i + k - n];
		char b = j + k < n ? s[j + k] : s[j + k - n];

		if (a > b)
		{
			i += k + 1;
			k = 0;
			if (i <= j)
				i = j + 1;
		}
		else if (a < b)
		{
			j += k + 1;
			k = 0;
			if (j <= i)
				j = i + 1;
		}
		else ++k;
	}

	return min(i, j);
}
