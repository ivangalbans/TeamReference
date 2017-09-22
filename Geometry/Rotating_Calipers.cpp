/*
	Gets all the antipodal pair of points
	Time: O(n)
*/
#define NEXT(i) (((i) + 1) % n)
double area (point a, point b, point c) //2 * area
{
	return abs(cross(b - a, c - a));
}

vector<pair<int, int> > antipodal_pairs (polygon &P)
{
	vector<pair<int, int> > ans;
	int n = P.size();

	if (P.size() == 2)
		ans.push_back(make_pair(0, 1));

	if (P.size() < 3)
		return ans;

	int q0 = 0;

	while (area(P[n - 1], P[0], P[NEXT(q0)]) >
			area(P[n - 1], P[0], P[q0]))
		++q0;

	for (int q = q0, p = 0; q != 0 && p <= q0; ++p)
	{
		ans.push_back(make_pair(p, q));

		while (area(P[p], P[NEXT(p)], P[NEXT(q)]) >
				area(P[p], P[NEXT(p)], P[q]))
		{
			q = NEXT(q);

			if (p == q0 && q == 0)
				return ans;

			ans.push_back(make_pair(p, q));
		}

		if (area(P[p], P[NEXT(p)], P[NEXT(q)]) ==
				area(P[p], P[NEXT(p)], P[q]))
		{
			if (p != q0 || q != n - 1)
				ans.push_back(make_pair(p, NEXT(q)));
			else
				ans.push_back(make_pair(NEXT(p), q));
		}
	}

	return ans;
}


/*
	Gets the farthest pair of points of the given points.
	(maybe TLE using double)
	TESTED [POJ 2187]
*/
pair<point, point> farthest_pair (polygon &P)
{
	P = convex_hull(P);
	vector<pair<int, int> > pairs = antipodal_pairs(P);

	double best = 0;
	pair<point, point> ans;

	for (int i = 0; i < (int)pairs.size(); ++i)
	{
		point p1 = P[pairs[i].first];
		point p2 = P[pairs[i].second];

		double dist = norm(p1-p2);

		if (dist > best)
		{
			best = dist;
			ans = make_pair(p1, p2);
		}
	}

	return ans;
}



/*
	Gets the minimum distance between parallel lines of
	support of the convex polygon P
	Time: O(n)
*/

double check (int a, int b, int c, int d, polygon &P)
{
	for (int i = 0; i < 4 && a != c; ++i)
	{
		if (i == 1)
			swap(a, b);
		else
			swap(c, d);
	}
	if (a == c) //a admits a support line parallel to bd
	{
		//assert(b != d)
		double A = area(P[a], P[b], P[d]); //double of the triangle area
		double base = abs(P[b] - P[d]); //base of the triangle abd
		return A / base;
	}
	return oo;
}

double polygon_width (polygon &P)
{
	if (P.size() < 3)
		return 0;

	vector<pair<int, int> > pairs = antipodal_pairs(P);
	double best = oo;
	int n = pairs.size();

	for (int i = 0; i < n; ++i)
	{
		double tmp = check(pairs[i].first, pairs[i].second,
				pairs[NEXT(i)].first,
				pairs[NEXT(i)].second, P);
		best = min(best, tmp);
	}
	return best;
}