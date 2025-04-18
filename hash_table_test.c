#include "hash_table.h"
#include <assert.h>

void init_test() {
  hash_table *table;
  pool_allocator *pool = pool_init(64, 10);
  hashtable_init(&table, 10, pool);

  assert(table->capacity == 10);
}

void insert_test() {
  hash_table *table;
  pool_allocator *pool = pool_init(64, 10);
  hashtable_init(&table, 10, pool);
  hashtable_insert(&table, "key", (void *)123);

  assert((int)hashtable_get(&table, "key") == 123);
}

int main() {
  init_test();
  insert_test();

  return 0;
}
