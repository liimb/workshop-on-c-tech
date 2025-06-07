#include "linear_allocator.h"
#include <assert.h>

void linear_init_test() {
  linear_allocator *allocator = linear_init(16);

  assert(allocator->memory != NULL);
  assert(allocator->capacity == 16);
  assert(allocator->current == 0);

  linear_destroy(allocator);
}

void linear_alloc_test() {
  linear_allocator *allocator = linear_init(16);

  void *block1 = linear_alloc(allocator, 8);
  assert(block1 != NULL);
  assert(allocator->current == 8);

  void *block2 = linear_alloc(allocator, 8);
  assert(block2 != NULL);
  assert(allocator->current == 16);

  void *block3 = linear_alloc(allocator, 1);
  assert(block3 == NULL);

  void *block4 = linear_alloc(allocator, 0);
  assert(block4 == NULL);

  linear_destroy(allocator);
}

void linear_reset_test() {
  linear_allocator *allocator = linear_init(16);

  void *block = linear_alloc(allocator, 8);
  assert(block != NULL);
  assert(allocator->current == 8);

  linear_reset(allocator);
  assert(allocator->current == 0);

  linear_destroy(allocator);
}

int main() {
  linear_init_test();
  linear_alloc_test();
  linear_reset_test();

  return 0;
}
