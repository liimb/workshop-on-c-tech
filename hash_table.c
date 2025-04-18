#include "hash_table.h"
#include "pool_allocator.h"
#include <stdlib.h>

size_t hash_func(const char *key, size_t capacity) {
  size_t hash = 0;
  while (*key) {
    hash++;
    key++;
  }
  return hash % capacity;
}

void hashtable_init(hash_table **table, size_t capacity,
                    pool_allocator *allocator) {

  allocator = pool_init(
      sizeof(hash_table *) + sizeof(hashtable_item *) * capacity, capacity + 1);

  (*table) = (hash_table *)pool_alloc(allocator);
  (*table)->allocator = allocator;
  (*table)->capacity = capacity;

  for (size_t i = 0; i < capacity; i++) {
    hashtable_item *item = (hashtable_item *)pool_alloc(allocator);
    (*table)->items[i].value = NULL;
    (*table)->items[i].is_deleted = 0;
    item->is_occupied = 0;
  }
}

void hashtable_insert(hash_table **table, const char *key, void *value) {
  size_t hash = hash_func(key, (*table)->capacity);

  int a = 0;

  while (a <= (*table)->capacity) {
    if (hash >= ((*table)->capacity - 1)) {
      hash = 0;
    }

    if ((*table)->items[hash].is_occupied == 0) {
      (*table)->items[hash].value = value;
      (*table)->items[hash].is_occupied = 1;
      return;
    }

    a++;
    hash++;
  }
}

void *hashtable_get(hash_table **table, const char *key) {
  size_t hash = hash_func(key, (*table)->capacity);
  return (*table)->items[hash].value;
}

void hashtable_del(hash_table *table, const char *key) {}

void hashtable_free(hash_table *table) {}
