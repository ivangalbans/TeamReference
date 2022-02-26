double area_heron(double const &a, double const &b, double const &c) {
  double s = (a + b + c) / 2;
  return sqrt(s * (s - a) * (s - b) * (s - c));
}

double circumradius(const double &a, const double &b, const double &c) {
  return a * b * c / 4 / area_heron(a, b, c);
}

double inradius(const double &a, const double &b, const double &c) {
  return 2 * area_heron(a, b, c) / (a + b + c);
}

/*
Center of the circumference of a triangle
[Tested COJ 1572 - Joining the Centers]
*/
point circunference_center(point a, point b, point c) {
  point x = 1.0 / conj(b - a), y = 1.0 / conj(c - a);
  return (y - x) / (conj(x) * y - x * conj(y)) + a;
}

bool circunference_center(point &a, point &b, point &c, point &r) {
  double d = (a.x() * (b.y() - c.y()) + b.x() * (c.y() - a.y()) +
              c.x() * (a.y() - b.y())) *
             2.0;
  if (fabs(d) < EPS)
    return false;
  r.x() = ((a.x() * a.x() + a.y() * a.y()) * (b.y() - c.y()) +
           (b.x() * b.x() + b.y() * b.y()) * (c.y() - a.y()) +
           (c.x() * c.x() + c.y() * c.y()) * (a.y() - b.y())) /
          d;
  r.y() = -((a.x() * a.x() + a.y() * a.y()) * (b.x() - c.x()) +
            (b.x() * b.x() + b.y() * b.y()) * (c.x() - a.x()) +
            (c.x() * c.x() + c.y() * c.y()) * (a.x() - b.x())) /
          d;
  return true;
}

/*
//Interseccion de las bisectrices
double incenter(vect &a,vect &b,vect &c,vect &r)
{
        double u=(b-c).length(),v=(c-a).length(),w=(a-b).length(),s=u+v+w;
        if(s<EPS) {r=a;return 0.0;}
        r.x=(a.x*u+b.x*v+c.x*w)/s;
        r.y=(a.y*u+b.y*v+c.y*w)/s;
        return sqrt((v+w-u)*(w+u-v)*(u+v-w)/s)*0.5;
}

//Interseccion de las alturas
bool orthocenter(vect &a,vect &b,vect &c,vect &r)
{
        double d=a.x*(b.y-c.y)+b.x*(c.y-a.y)+c.x*(a.y-b.y);
        if(fabs(d)<EPS) return false;
        r.x=((c.x*b.x+c.y*b.y)*(c.y-b.y)+(a.x*c.x+a.y*c.y)*(a.y-c.y)
                        +(b.x*a.x+b.y*a.y)*(b.y-a.y))/d;
        r.y=-((c.x*b.x+c.y*b.y)*(c.x-b.x)+(a.x*c.x+a.y*c.y)*(a.x-c.x)
                        +(b.x*a.x+b.y*a.y)*(b.x-a.x))/d;
        return true;
}
*/

double signed_area(const point &p1, const point &p2, const point &p3) {
  return cross(p2 - p1, p3 - p1);
}
double triangle_area(const point &a, const point &b, const point &c) {
  return 0.5 * abs(cross(b - a, c - a));
}
