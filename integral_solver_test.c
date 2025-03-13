#include "integral_solver.h"
#include <assert.h>
#include <math.h>
#include <stdio.h>

double func_ln(double x) { return 1 / log(x); }

double func_sin_cos(double x) { return sin(x) * cos(x); }

double func_quad(double x) { return pow(x, 2); }

void test_integral_1() {
  double res = integral_solver(func_ln, 2, 5, 3);
  assert(fabs(res - 2.663) < 0.001);
}

void test_integral_2() {
  double res = integral_solver(func_ln, 2, 5, 5);
  assert(fabs(res - 2.617) < 0.001);
}

void test_integral_3() {
  double res = integral_solver(func_sin_cos, 10, 20, 100);
  assert(fabs(res - 0.268) < 0.01);
}

void test_integral_4() {
  double res = integral_solver(func_quad, -5, 5, 5);
  assert(fabs(res - 90) < 0.001);
}

void test_integral_5() {
  double res = integral_solver(func_quad, -5, 5, -100);
  assert(fabs(res) < 1E-10);
}

int main() {
  test_integral_1();
  test_integral_2();
  test_integral_3();
  test_integral_4();
  test_integral_5();

  return 0;
}
