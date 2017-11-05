
template<class F, class G>
double find_root(F f, G df, double x)
{
	for (int iter = 0; iter < 100; ++iter)
	{
		double fx = f(x), dfx = df(x);
		x -= fx / dfx;
		if (fabs(fx) < 1e-12)
			break;
	}
	return x;
}
