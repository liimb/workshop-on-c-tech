#include "quadratic_solver.h"
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void test_a_zero() {
  int root_count;
  double *roots = quadratic_solver(0, 1, 1, &root_count);
  assert(root_count == -1);
  assert(roots == NULL);
}

void test_two_root() {
  int root_count;
  double *roots = quadratic_solver(1, 0, -1, &root_count);
  assert(root_count == 2);
  assert(roots[0] == -1);
  assert(roots[1] == 1);
}

void test_one_root() {
  int root_count;
  double *roots = quadratic_solver(1, 0, 0, &root_count);
  assert(root_count == 1);
  assert(roots[0] == 0);
}

void test_zero_root() {
  int root_count;
  double *roots = quadratic_solver(1, 0, 1, &root_count);
  assert(root_count == 0);
}

void test_one_root_accuracy() {
  int root_count;
  double *roots = quadratic_solver(1, 0, -1E-7, &root_count);
  assert(root_count == 2);
  assert(fabs(roots[0] - (-3E-4)) < 1E-4);
  assert(fabs(roots[1] - (3E-4)) < 1E-4);
}

void test_two_root_accuracy() {
  int root_count;
  double *roots = quadratic_solver(1, -1E+10, -1, &root_count);
  assert(root_count == 2);
  assert(fabs(roots[0] - (-1E-10)) < 1E-11);
  assert(fabs(roots[1] - (1E+10)) < 1E-11);
}

void test_three_root_accuracy() {
  int root_count;
  double *roots = quadratic_solver(1, 0, -1E-8, &root_count);
  assert(root_count == 2);
  assert(fabs(roots[0] - (-1E-4)) < 1E-7);
  assert(fabs(roots[1] - 1E-4) < 1E-7);
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