#include "pool_allocator.h"
#include <assert.h>

void init_test() {
  pool_allocator *pool = pool_init(32, 4);

  assert(pool != NULL);
  assert(pool->block_count == 4);
  assert(pool->block_size >= 32);
  assert(pool->free_blocks != NULL);
  assert(pool->used_blocks == NULL);

  pool_close(pool);
}

void alloc_test() {
  pool_allocator *pool = pool_init(32, 2);

  void *block_one = pool_alloc(pool);
  assert(block_one != NULL);
  void *block_two = pool_alloc(pool);
  assert(block_two != NULL);
  void *block_three = pool_alloc(pool);
  assert(block_three == NULL);

  pool_close(pool);
}

void free_test() {
  pool_allocator *pool = pool_init(32, 1);

  void *block_one = pool_alloc(pool);
  assert(block_one != NULL);

  pool_free(pool, block_one);

  void *block_two = pool_alloc(pool);
  assert(block_two == block_one);

  pool_close(pool);
}

void data_test() {
  pool_allocator *pool = pool_init(64, 1);

  block *block_one = pool_alloc(pool);

  *block_one->data = 73;

  pool_free(pool, block_one);

  block *block_two = pool_alloc(pool);

  assert(*block_two->data == 73);

  pool_close(pool);
}

int main() {
  init_test();
  alloc_test();
  free_test();
  data_test();

  return 0;
}
