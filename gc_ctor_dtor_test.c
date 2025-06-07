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
  my_object **obj = (my_object **)object_ptr;
  (*obj)->value = 123;
}

void my_destructor(void *object_ptr) {
  my_object **obj = (my_object **)object_ptr;
  free(*obj);
  *obj = NULL;
}

void ref_ctor_dtor_test() {
  pool_allocator *pool = pool_init(sizeof(ref_count_t), 4);
  ref_context ctx;

  ctx.alloc = pool_alloc_test;
  ctx.dealloc = pool_free_test;
  ctx.mem_context = pool;

  ref_count_t *ref = NULL;
  my_object *obj = malloc(sizeof(my_object));

  int res =
      ref_count_create_ext(&ref, &obj, ctx, my_constructor, my_destructor);

  assert(ref->constructor == my_constructor);
  assert(ref->destructor == my_destructor);
  assert(obj->value == 123);

  ref_count_release(ref);

  assert(obj == NULL);

  pool_close(pool);
}

int main() {
  ref_ctor_dtor_test();
  return 0;
}
