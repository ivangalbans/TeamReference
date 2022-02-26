/*
        Tested: COJ
        2121 - Environment Protection
*/
// METODO DE SIMPSON 1/3 Compuesta
//  a,b: intervalo de integracion
//  n = 10000: numero de pasos (ya multiplicado por 2)
double Simpson(int n, double a, double b, double (*f)(double)) {
  double s = 0;
  double h = (double)(b - a) / n;
  for (int i = 0; i <= n; ++i) {
    double x = a + h * i;
    s += f(x) * ((i == 0 || i == n) ? 1 : ((i & 1) == 0) ? 2 : 4);
  }
  return s * (h / 3);
}
