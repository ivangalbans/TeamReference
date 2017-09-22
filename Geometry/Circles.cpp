struct circle{
	point center;
	double ratio;

	circle(point center, double ratio) : center(center) , ratio(ratio){}
};

//Tested [BAPC 2010 Clocks]
vector<point> circles_intersection(const circle &c1, const circle &c2)
{
	vector<point> ret;
	double d = dist(c1.center, c2.center);
	if (d > c1.ratio + c2.ratio || d + min(c1.ratio, c2.ratio) < max(c1.ratio, c2.ratio))
		return ret;
	double x = ( d*d - c2.ratio*c2.ratio + c1.ratio*c1.ratio ) / ( 2*d );
	double y = sqrt( c1.ratio * c1.ratio - x*x );
	point v = (c2.center - c1.center) / d;
	ret.push_back(c1.center + v*x + rotateCCW90(v) * y);
	if (y > 0)
		ret.push_back(c1.center + v*x - rotateCCW90(v) * y);
	return ret;
}

//Interseccion Linea-Circulo
vector<point> intersectLC(line l, circle c)
{
	point a = l[0], b = l[1];
	vector<point> ret;
	b = b-a;
	a = a - c.center;
	double A = dot(b, b);
	double B = dot(a, b);
	double C = dot(a, a) - c.ratio*c.ratio;
	double D = B*B - A*C;

	if (cmp(D) < 0)	return ret;
	ret.push_back(c.center + a + b*(-B + sqrt(D+EPS)) / A);
	if (cmp(D) > 0)	ret.push_back(c.center + a + b * (-B - sqrt(D)) / A);

	return ret;
}


/*
	Area of the intersection of a circle with a polygon
	Circle's center lies in (0,0)
	Polygon must be given counterclockwise
	Tested [Light OJ 1358]
*/

#define xx(_t) (xa+(_t)*a)
#define yy(_t) (ya+(_t)*b)

double radian(double xa,double ya,double xb,double yb)
{
	return atan2(xa*yb - xb*ya, xa*xb + ya*yb);
}


double part(double xa,double ya,double xb,double yb,double r)
{
	double l = sqrt((xa-xb) * (xa-xb) + (ya-yb) * (ya-yb));
	double a = (xb-xa) / l, b = (yb - ya) / l, c = a*xa + b*ya;
	double d = 4.0 * (c*c - xa*xa - ya*ya + r*r);
	if(d < EPS) return radian(xa,ya,xb,yb) * r * r * 0.5;
	else
	{
		d = sqrt(d) * 0.5;
		double s = -c-d, t = -c+d;
		if(s < 0.0) s = 0.0;
		else if(s > l) s = l;
		if(t < 0.0) t = 0.0;
		else if(t > l) t = l;
		return (xx(s)*yy(t) - xx(t)*yy(s) + (radian(xa,ya,xx(s),yy(s))
						+ radian(xx(t),yy(t),xb,yb))*r*r) * 0.5;
	}
}


double area_intersectionPC(polygon P, double r)
{
	double s = 0.0;
	int n = (int)P.size();
	P.push_back(P[0]);
	for(int i = 0; i < n; ++i)
		s += part(P[i].x(), P[i].y(), P[NEXT(i)].x(), P[NEXT(i)].y(), r);
	return fabs(s);
}