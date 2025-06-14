#include "pool_allocator.h"
#include <stdio.h>
#include <stdlib.h>

pool_allocator *pool_init(size_t block_size, size_t block_count) {
  pool_allocator *pool = malloc(sizeof(pool_allocator));

  if (pool == NULL) {
    return NULL;
  }

  size_t final_block_size = sizeof(block) + block_size;

  pool->block_count = block_count;
  pool->block_size = final_block_size;

  pool->memory = malloc(final_block_size * block_count);

  if (pool->memory == NULL) {
    free(pool);
    return NULL;
  }

  pool->free_blocks = NULL;
  pool->used_blocks = NULL;

  for (size_t i = 0; i < block_count; i++) {
    block *current_block =
        (block *)((char *)pool->memory + i * pool->block_size);
    current_block->next = pool->free_blocks;
    pool->free_blocks = current_block;
  }

  return pool;
}

void *pool_alloc(void *allocator) {
  pool_allocator *pool = (pool_allocator *)allocator;

  if (pool->free_blocks == NULL) {
    return NULL;
  }

  block *current_block = pool->free_blocks;
  pool->free_blocks = current_block->next;

  current_block->next = pool->used_blocks;
  pool->used_blocks = current_block;

  return (void *)(current_block->data);
}

void pool_free(void *allocator, void *ptr) {
  pool_allocator *pool = (pool_allocator *)allocator;

  block *block_to_free = (block *)((char *)ptr - sizeof(block));

  block *prev = NULL;
  block *curr = pool->used_blocks;

  while (curr != NULL) {
    if (curr == block_to_free) {
      if (prev == NULL) {
        pool->used_blocks = curr->next;
      } else {
        prev->next = curr->next;
      }

      block_to_free->next = pool->free_blocks;
      pool->free_blocks = block_to_free;

      return;
    }

    prev = curr;
    curr = curr->next;
  }
}

void pool_close(void *allocator) {
  pool_allocator *pool = (pool_allocator *)allocator;

  if (pool == NULL) {
    return;
  }

  free(pool->memory);
  free(pool);
}
