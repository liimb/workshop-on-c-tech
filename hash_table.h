#include "pool_allocator.h"
#include <stdio.h>

typedef struct hashtable_item {
  int is_occupied;
  int is_deleted;
  void *value;
} hashtable_item;

typedef struct hash_table {
  size_t capacity;
  pool_allocator *allocator;
  hashtable_item items[];
} hash_table;

size_t hash_func(const char *key, size_t capacity);
void hashtable_init(hash_table **table, size_t capacity,
                    pool_allocator *allocator);
void hashtable_insert(hash_table **table, const char *key, void *value);
void *hashtable_get(hash_table **table, const char *key);
void hashtable_del(hash_table *table, const char *key);
void hashtable_free(hash_table *table);
