#include "array_list.h"
#include "linear_allocator.h"
#include <assert.h>

void test_add_and_get() {
  linear_allocator *alloc = linear_init(128);
  array_list list;
  arraylist_init(&list, sizeof(int), alloc);

  int value = 42;
  arraylist_add(&list, &value, 0);

  assert(*(int *)arraylist_get(&list, 0) == 42);

  arraylist_free(&list);
}

void test_delete() {
  linear_allocator *alloc = linear_init(128);
  array_list list;
  arraylist_init(&list, sizeof(int), alloc);

  int a = 10, b = 20, c = 30;
  arraylist_add(&list, &a, 0);
  arraylist_add(&list, &b, 1);
  arraylist_add(&list, &c, 2);

  arraylist_del(&list, 1);

  assert(list.count == 2);
  assert(*(int *)arraylist_get(&list, 0) == 10);
  assert(*(int *)arraylist_get(&list, 1) == 30);

  arraylist_free(&list);
}

void test_add_insert_middle() {
  linear_allocator *alloc = linear_init(256);
  array_list list;
  arraylist_init(&list, sizeof(int), alloc);

  int a = 1, b = 2, c = 99;
  arraylist_add(&list, &a, 0);
  arraylist_add(&list, &b, 1);
  arraylist_add(&list, &c, 1);

  assert(list.count == 3);
  assert(*(int *)arraylist_get(&list, 0) == 1);
  assert(*(int *)arraylist_get(&list, 1) == 99);
  assert(*(int *)arraylist_get(&list, 2) == 2);

  arraylist_free(&list);
}

void test_add_memory_out() {
  linear_allocator *alloc = linear_init(64);
  array_list list;
  arraylist_init(&list, sizeof(int), alloc);

  int inserted = 0;

  for (int i = 0; i < 100; ++i) {
    arraylist_add(&list, &i, i);
    if (list.count == i + 1)
      inserted++;
    else
      break;
  }

  assert(inserted > 0);

  for (int i = 0; i < inserted; ++i) {
    int *v = arraylist_get(&list, i);
    assert(v != NULL);
    assert(*v == i);
  }

  arraylist_free(&list);
}

int main() {
  test_add_and_get();
  test_delete();
  test_add_memory_out();
  test_add_insert_middle();

  return 0;
}
