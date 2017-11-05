/*
	Cut a convex polygon by a line and
	return the part to the left of the line

	Tested: AIZU(judge.u-aizu.ac.jp) CGL.4C
	Complexity: O(n)
*/

polygon convex_cut(const polygon &P, const line &l)
{
	polygon Q;
	for (int i = 0, n = P.size(); i < n; ++i)
	{
		point A = P[i], B = P[(i + 1) % n];
		if (ccw(l.p, l.q, A) != -1) Q.push_back(A);
		if (ccw(l.p, l.q, A) * ccw(l.p, l.q, B) < 0)
			Q.push_back(crosspoint((line){ A, B }, l));
	}
	return Q;
}
