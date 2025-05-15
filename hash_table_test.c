#include "hash_table.h"
#include <assert.h>
#include <stdint.h>

void init_test() {
  pool_allocator pool;
  hash_table table;

  hashtable_init(10, sizeof(int), &pool, &table);

  assert(table.capacity == 10);

  hashtable_free(&table);
}

void insert_test() {
  pool_allocator pool;
  hash_table table;

  hashtable_init(10, sizeof(int), &pool, &table);

  int a = 123;
  int b = 1234;
  int c = 123456;

  hashtable_insert(&table, "one", &a);
  hashtable_insert(&table, "two", &b);
  hashtable_insert(&table, "two", &c);

  assert(*(int *)hashtable_get(&table, "one") == a);
  assert(*(int *)hashtable_get(&table, "two") == c);
  assert(hashtable_get(&table, "key") == NULL);

  hashtable_free(&table);
}

void delete_test() {
  pool_allocator pool;
  hash_table table;

  hashtable_init(10, sizeof(int), &pool, &table);

  int a = 123;

  hashtable_insert(&table, "key", &a);

  assert(*(int *)hashtable_get(&table, "key") == a);

  hashtable_delete(&table, "key");

  assert(hashtable_get(&table, "key") == NULL);

  hashtable_free(&table);
}

void capacity_test() {
  pool_allocator pool;
  hash_table table;

  hashtable_init(10, sizeof(int), &pool, &table);

  int a = 1;
  int b = 2;
  int c = 3;
  int d = 4;
  int e = 5;

  hashtable_insert(&table, "1", &a);
  hashtable_insert(&table, "2", &b);
  hashtable_insert(&table, "3", &c);
  hashtable_insert(&table, "4", &d);
  hashtable_insert(&table, "5", &e);

  assert(*(int *)hashtable_get(&table, "1") == a);
  assert(*(int *)hashtable_get(&table, "2") == b);
  assert(*(int *)hashtable_get(&table, "3") == c);
  assert(*(int *)hashtable_get(&table, "4") == d);
  assert(*(int *)hashtable_get(&table, "5") == e);

  hashtable_free(&table);
}

int main() {
  init_test();
  insert_test();
  delete_test();
  capacity_test();

  return 0;
}
