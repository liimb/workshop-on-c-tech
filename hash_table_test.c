#include "hash_table.h"
#include <assert.h>
#include <stdint.h>

void init_test() {
  pool_allocator *pool;
  hash_table *table = hashtable_init(10, pool);

  assert(table != NULL);
  assert(table->capacity == 10);

  hashtable_free(table);
}

void insert_test() {
  pool_allocator *pool;
  hash_table *table = hashtable_init(10, pool);
  hashtable_insert(table, "one", (void *)123);
  hashtable_insert(table, "two", (void *)1234);
  hashtable_insert(table, "two", (void *)123456);

  assert((uintptr_t)hashtable_get(table, "one") == 123);
  assert((uintptr_t)hashtable_get(table, "two") == 123456);
  assert(hashtable_get(table, "key") == NULL);

  hashtable_free(table);
}

void delete_test() {
  pool_allocator *pool;
  hash_table *table = hashtable_init(10, pool);

  hashtable_insert(table, "key", (void *)123);

  assert((uintptr_t)hashtable_get(table, "key") == 123);

  hashtable_delete(table, "key");

  assert(hashtable_get(table, "key") == NULL);

  hashtable_free(table);
}

void capacity_test() {
  pool_allocator *pool;
  hash_table *table = hashtable_init(3, pool);

  hashtable_insert(table, "1", (void *)1);
  hashtable_insert(table, "2", (void *)2);
  hashtable_insert(table, "3", (void *)3);
  hashtable_insert(table, "4", (void *)4);
  hashtable_insert(table, "5", (void *)5);

  assert((uintptr_t)hashtable_get(table, "1") == 1);
  assert((uintptr_t)hashtable_get(table, "2") == 2);
  assert((uintptr_t)hashtable_get(table, "3") == 3);
  assert(hashtable_get(table, "4") == NULL);
  assert(hashtable_get(table, "5") == NULL);

  hashtable_free(table);
}

int main() {
  init_test();
  insert_test();
  delete_test();
  capacity_test();

  return 0;
}
