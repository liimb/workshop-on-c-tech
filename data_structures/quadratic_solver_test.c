#include "quadratic_solver.h"
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void test_a_zero() {
  double *roots;
  int return_code = quadratic_solver(0, 1, 1, 1E-14, &roots);

  assert(return_code == NOT_A_QUADRATIC_EQUATION);
  assert(roots == NULL);
}

void test_two_root() {
  double eps = 1E-14;
  double *roots;
  int return_code = quadratic_solver(1, 0, -1, eps, &roots);

  assert(return_code == TWO_ROOTS);
  assert(fabs(roots[0] - (-1)) < eps);
  assert(fabs(roots[1] - 1) < eps);

  free(roots);
}

void test_one_root() {
  double eps = 1E-14;
  double *roots;
  int return_code = quadratic_solver(1, 0, 0, eps, &roots);

  assert(return_code == ONE_ROOT);
  assert(fabs(roots[0]) < eps);

  free(roots);
}

void test_zero_root() {
  double eps = 1E-14;
  double *roots;
  int return_code = quadratic_solver(1, 0, 1, eps, &roots);

  assert(return_code == NO_REAL_ROOTS);
  assert(roots == NULL);

  free(roots);
}

void test_one_root_accuracy() {
  double eps = 1E-7;
  double e = 1E-4;
  double *roots;
  int return_code = quadratic_solver(1, 0, -1E-7, eps, &roots);

  assert(return_code == TWO_ROOTS);
  assert(fabs(roots[0] + 3E-4) < e);
  assert(fabs(roots[1] - 3E-4) < e);

  free(roots);
}

void test_two_root_accuracy() {
  double eps = 1E-11;
  double *roots;
  int return_code = quadratic_solver(1, -1E+10, -1, eps, &roots);

  assert(return_code == TWO_ROOTS);
  assert(fabs(roots[0] - (-1E-10)) < eps);
  assert(fabs(roots[1]) - 1E+10 < eps);

  free(roots);
}

void test_three_root_accuracy() {
  double eps = 1E-7;
  double *roots;
  int return_code = quadratic_solver(1, 0, -1E-8, eps, &roots);

  assert(return_code == ONE_ROOT);
  assert(fabs(roots[0]) < eps);

  free(roots);
}

int main() {
  test_a_zero();
  test_two_root();
  test_one_root();
  test_zero_root();
  test_one_root_accuracy();
  test_two_root_accuracy();
  test_three_root_accuracy();
  return 0;
}
