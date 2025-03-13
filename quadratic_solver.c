#include "quadratic_solver.h"
#include <math.h>
#include <stdlib.h>

int quadratic_solver(double a, double b, double c, double eps, double **roots) {
  if (fabs(a) < eps) {
    *roots = NULL;
    return NOT_A_QUADRATIC_EQUATION;
  }

  b = b / a;
  c = c / a;

  double d = pow(b, 2) - 4 * c;

  if (d < -eps) {
    *roots = NULL;
    return NO_REAL_ROOTS;
  }

  if (fabs(d) <= eps) {
    *roots = (double *)malloc(1 * sizeof(double));
    (*roots)[0] = -b / 2;
    return ONE_ROOT;
  }

  int sign;

  if (b >= eps) {
    sign = 1;
  } else {
    sign = -1;
  }

  double x1 = (-b - sign * sqrt(d)) / 2;
  double x2 = c / x1;

  *roots = (double *)malloc(2 * sizeof(double));

  if (x1 > x2) {
    (*roots)[0] = x2;
    (*roots)[1] = x1;
  } else {
    (*roots)[0] = x1;
    (*roots)[1] = x2;
  }

  return TWO_ROOTS;
}
