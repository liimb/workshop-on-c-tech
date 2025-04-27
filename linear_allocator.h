#include <stdio.h>

typedef struct linear_allocator {
  void *memory;
  size_t current;
  size_t capacity;
} linear_allocator;

linear_allocator *linear_init(size_t size);
void linear_destroy(linear_allocator *allocator);
void *linear_alloc(linear_allocator *allocator, size_t size);
void linear_reset(linear_allocator *allocator);
