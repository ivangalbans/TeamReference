/*
    Minkowski sum of two convex polygons. O(n + m)

    Note: Polygons MUST be counterclockwise
*/

polygon minkowski(polygon &A, polygon &B){
	int na = (int)A.size(), nb = (int)B.size();

	if (A.empty() || B.empty()) return polygon();

	rotate(A.begin(), min_element(A.begin(), A.end()), A.end());
	rotate(B.begin(), min_element(B.begin(), B.end()), B.end());

	int pa = 0, pb = 0;

	polygon M;

	while (pa < na && pb < nb){
		M.push_back(A[pa] + B[pb]);
		double x = cross(A[(pa + 1) % na] - A[pa], 
						 B[(pb + 1) % nb] - B[pb]);
		if (x <= eps) pb++;
		if (-eps <= x) pa++;
	}

	while (pa < na) M.push_back(A[pa++] + B[0]);
	while (pb < nb) M.push_back(B[pb++] + A[0]);

	return M;
}