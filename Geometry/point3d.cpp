
const double pi = acos(-1.0);

// Construct a point on a sphere with center on the origin and radius R
// TESTED [COJ-1436]
struct point3d
{
	double x, y, z;

	point3d(double x = 0, double y = 0, double z = 0) : x(x), y(y), z(z) {}

	double operator*(const point3d &p) const
	{
		return x * p.x + y * p.y + z * p.z;
	}

	point3d operator-(const point3d &p) const
	{
		return point3d(x - p.x, y - p.y, z - p.z);
	}
};

double abs(point3d p)
{
	return sqrt(p.x * p.x + p.y * p.y + p.z * p.z);
}

point3d from_polar(double lat, double lon, double R)
{
	lat = lat / 180.0 * pi;
	lon = lon / 180.0 * pi;
	return point3d(R * cos(lat) * sin(lon), 
				   R * cos(lat) * cos(lon), R * sin(lat));
}

struct plane
{
	double A, B, C, D;
};

double euclideanDistance(point3d p, point3d q)
{
	return abs(p - q);
}

/*
 Geodisic distance between points in a sphere
 R is the radius of the sphere
 */
double geodesic_distance(point3d p, point3d q, double r)
{
	return r * acos(p * q / r / r);
}

const double eps = 1e-9;

// Find the rect of intersection of two planes on the space
// The rect is given parametrical
// TESTED [TIMUS 1239]
void planePlaneIntersection(plane p, plane q)
{
	if (abs(p.C * q.B - q.C * p.B) < eps)
		return; // Planes are parallel

	double mz = (q.A * p.B - p.A * q.B) / (p.C * q.B - q.C * p.B);
	double nz = (q.D * p.B - p.D * q.B) / (p.C * q.B - q.C * p.B);

	double my = (q.A * p.C - p.A * q.C) / (p.B * q.C - p.C * q.B);
	double ny = (q.D * p.C - p.D * q.C) / (p.B * q.C - p.C * q.B);

	// parametric rect: (x, my * x + ny, mz * x * nz)
}
