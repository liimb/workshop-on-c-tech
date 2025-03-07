#include "quadratic_solver.h"
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void test_a_zero() {
  int root_count;
  double *roots = quadratic_solver(0, 1, 1, 1E-14, &root_count);
  assert(root_count == -1);
  assert(roots == NULL);
}

void test_two_root() {
  int root_count;
  double *roots = quadratic_solver(1, 0, -1, 1E-14, &root_count);
  assert(root_count == 2);
  assert(roots[0] == -1);
  assert(roots[1] == 1);
}

void test_one_root() {
  int root_count;
  double *roots = quadratic_solver(1, 0, 0, 1E-14, &root_count);
  assert(root_count == 1);
  assert(roots[0] == 0);
}

void test_zero_root() {
  int root_count;
  double *roots = quadratic_solver(1, 0, 1, 1E-14, &root_count);
  assert(root_count == 0);
}

void test_one_root_accuracy() {
  double eps = 1E-7;
  double e = 1E-4;
  int root_count;
  double *roots = quadratic_solver(1, 0, -1E-7, eps, &root_count);
  assert(root_count == 2);
  assert(fabs(roots[0] + 3E-4) < e);
  assert(fabs(roots[1] - 3E-4) < e);
}

void test_two_root_accuracy() {
  double eps = 1E-11;
  int root_count;
  double *roots = quadratic_solver(1, -1E+10, -1, eps, &root_count);
  assert(root_count == 2);
  assert(fabs(roots[0] - (-1E-10)) < eps);
  assert(fabs(roots[1]) - 1E+10 < eps);
}

void test_three_root_accuracy() {
  int root_count;
  double *roots = quadratic_solver(1, 0, -1E-8, 1E-7, &root_count);
  assert(root_count == 1);
  assert(roots[0] == 0);
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
