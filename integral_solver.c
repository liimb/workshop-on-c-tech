#include "integral_solver.h"

double integral_solver(double (*function)(double), double a, double b, int n) {
  if (n <= 0) {
    return 0;
  }

  double step = (b - a) / n;
  double res = (function(a) + function(b)) / 2;

  for (int i = 1; i < n; i++) {
    res = res + function(a + step * i);
  }

  return res * step;
}
