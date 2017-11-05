/*
	Minimum of unimodal function (goldsection search)

	Tested: COJ 2890 :(
*/

template<class F>
double find_min(F f, double a, double d, double eps = 1e-9)
{
	const int iter = 150;
	const double r = 2 / (3 + sqrt(5.));
	double b = a + r * (d - a), c = d - r * (d - a), fb = f(b), fc = f(c);
	for (int it = 0; it < iter && d - a > eps; ++it)
	{
		// '<': maximum, '>': minimum
		if (fb > fc)
		{
			a = b;
			b = c;
			c = d - r * (d - a);
			fb = fc;
			fc = f(c);
		}
		else
		{
			d = c;
			c = b;
			b = a + r * (d - a);
			fc = fb;
			fb = f(b);
		}
	}
	return c;
}
