#include "pool_allocator.h"
#include <stdio.h>

typedef struct hashtable_item {
  int is_occupied;
  int is_deleted;
  const char *key;
  void *value;
} hashtable_item;

typedef struct hash_table {
  size_t capacity;
  size_t value_size;
  pool_allocator *allocator;
  hashtable_item *items;
} hash_table;

size_t hash_func(const char *key, size_t capacity);
void hashtable_init(size_t capacity, size_t value_size,
                    pool_allocator *allocator, hash_table *table);
void hashtable_insert(hash_table *table, const char *key, void *value);
void *hashtable_get(hash_table *table, const char *key);
void hashtable_delete(hash_table *table, const char *key);
void hashtable_free(hash_table *table);
