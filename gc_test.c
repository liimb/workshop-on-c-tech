#include "gc.h"
#include "pool_allocator.h"
#include <assert.h>

void *pool_alloc_test(void *allocator) {
  return pool_alloc((pool_allocator *)allocator);
}

void pool_free_test(void *allocator, void *ptr) { pool_free(allocator, ptr); }

void ref_create_test() {
  pool_allocator *pool = pool_init(64, 4);
  ref_context ctx;

  ctx.alloc = pool_alloc_test;
  ctx.dealloc = pool_free_test;
  ctx.mem_context = pool;

  ref_count_t *ref = NULL;
  int res = ref_count_create(&ref, NULL, ctx);
  assert(res == SUCCESS);
  assert(ref != NULL);
  assert(ref->count == 1);
  assert(ref->dependencies == NULL);
  assert(ref->object == NULL);

  ref_count_release(ref);
  pool_close(pool);
}

void ref_count_retain_test() {
  pool_allocator *pool = pool_init(64, 4);
  ref_context ctx;

  ctx.alloc = pool_alloc_test;
  ctx.dealloc = pool_free_test;
  ctx.mem_context = pool;

  ref_count_t *ref = NULL;
  ref_count_create(&ref, NULL, ctx);
  assert(ref->count == 1);
  ref_count_retain(ref);
  assert(ref->count == 2);

  int res1 = ref_count_release(ref);
  assert(res1 == SUCCESS);
  assert(ref->count == 1);

  int res2 = ref_count_release(ref);
  assert(res2 == SUCCESS);
  pool_close(pool);
}

void ref_count_dep_chain_test() {
  pool_allocator *pool = pool_init(128, 16);
  ref_context ctx;

  ctx.alloc = pool_alloc_test;
  ctx.dealloc = pool_free_test;
  ctx.mem_context = pool;

  ref_count_t *a = NULL, *b = NULL, *c = NULL;
  ref_count_create(&a, NULL, ctx);
  ref_count_create(&b, NULL, ctx);
  ref_count_create(&c, NULL, ctx);

  ref_count_add_dependency(a, b);
  ref_count_add_dependency(b, c);

  ref_count_release(b);
  assert(a->count == 1);
  assert(b->count == 1);
  assert(c->count == 2);

  pool_close(pool);
}

int main() {
  ref_create_test();
  ref_count_retain_test();
  ref_count_dep_chain_test();

  return 0;
}
