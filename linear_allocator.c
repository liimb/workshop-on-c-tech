#include "linear_allocator.h"
#include <stdlib.h>

linear_allocator *linear_init(size_t size) {
  linear_allocator *allocator = malloc(sizeof(linear_allocator));

  if (allocator == NULL)
    return NULL;

  allocator->capacity = size;
  allocator->current = 0;
  allocator->memory = malloc(size);

  return allocator;
}

void linear_destroy(linear_allocator *allocator) {
  if (allocator == NULL)
    return;

  if (allocator->memory != NULL)
    free(allocator->memory);

  free(allocator);
}

void linear_reset(linear_allocator *allocator) {
  if (allocator == NULL)
    return;

  allocator->current = 0;
}

void *linear_alloc(linear_allocator *allocator, size_t size) {
  if (allocator == NULL)
    return NULL;

  if (allocator->current + size > allocator->capacity || size == 0)
    return NULL;

  void *adr = allocator->memory + allocator->current;
  allocator->current += size;

  return adr;
}
