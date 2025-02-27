#include "quadratic_solver.h"
#include <math.h>
#include <stdlib.h>

double *quadratic_solver(double a, double b, double c, int *root_count) {
  if (a == 0) {
    *root_count = -1;
    double *roots = NULL;
    return roots;
  }

  double d = pow(b, 2) - 4 * a * c;

  if (d < 0) {
    *root_count = 0;
    double *roots = NULL;
    return roots;
  }

  if (d == 0) {
    *root_count = 1;
    double *roots = (double *)malloc(1 * sizeof(double));
    roots[0] = -b / (2 * a);
    return roots;
  }

  int sign;

  if (b >= 0) {
    sign = 1;
  } else {
    sign = -1;
  }

  double x1 = (-b - sign * sqrt(d)) / 2;
  double x2 = c / x1;

  double *roots = (double *)malloc(2 * sizeof(double));

  if (x1 > x2) {
    roots[0] = x2;
    roots[1] = x1;
  } else {
    roots[0] = x1;
    roots[1] = x2;
  }

  *root_count = 2;

  return roots;
}