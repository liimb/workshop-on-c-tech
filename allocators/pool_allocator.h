#ifndef POOL_ALLOCATOR_H
#define POOL_ALLOCATOR_H

#include <stdio.h>

typedef struct block {
  struct block *next;
  char data[];
} block;

typedef struct pool_allocator {
  size_t block_size;
  size_t block_count;
  void *memory;
  block *free_blocks;
  block *used_blocks;
} pool_allocator;

pool_allocator *pool_init(size_t block_size, size_t block_count);
void *pool_alloc(void *allocator);
void pool_free(void *allocator, void *ptr);
void pool_close(void *allocator);

#endif
