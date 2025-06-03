#include "gc.h"
#include "pool_allocator.h"
#include <assert.h>
#include <stdlib.h>

void *pool_alloc_test(void *allocator) {
  return pool_alloc((pool_allocator *)allocator);
}

void pool_free_test(void *allocator, void *ptr) { pool_free(allocator, ptr); }

typedef struct my_object {
  int value;
} my_object;

void my_constructor(void *object_ptr) {
  my_object *obj = (my_object *)object_ptr;
  obj->value = 123;
}

void my_destructor(void *object_ptr) {
  my_object *obj = (my_object *)object_ptr;
  obj->value = 0;
}

void cyclic_links_test() {
  pool_allocator *pool = pool_init(sizeof(ref_count_t), 4);
  ref_context ctx;

  ctx.alloc = pool_alloc_test;
  ctx.dealloc = pool_free_test;
  ctx.mem_context = pool;
  ctx.all_refs_head = NULL;

  ref_count_t *a = NULL;
  ref_count_t *b = NULL;

  my_object a_obj;
  my_object b_obj;

  ref_count_create_ext(&a, &a_obj, &ctx, my_constructor, my_destructor);
  ref_count_create_ext(&b, &b_obj, &ctx, my_constructor, my_destructor);

  ref_count_add_dependency(a, b);
  ref_count_add_dependency(b, a);

  ref_count_release(a);
  ref_count_release(b);

  assert(a_obj.value == 123);
  assert(b_obj.value == 123);

  gc_collect(&ctx);

  assert(a_obj.value == 0);
  assert(b_obj.value == 0);

  pool_close(pool);
}

int main() {
  cyclic_links_test();
  return 0;
}
