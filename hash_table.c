#include "hash_table.h"
#include "pool_allocator.h"

size_t hash_func(const char *key, size_t capacity) {
  size_t hash = 0;
  while (*key) {
    hash++;
  }
  return hash % capacity;
}

void hashtable_init(hash_table *table, size_t capacity,
                    pool_allocator *allocator) {
  table->allocator = allocator;
  table->capacity = capacity;

  allocator = pool_init(sizeof(hashtable_item), capacity);

  for (size_t i = 0; i < capacity; i++) {
    table->items[i] = (hashtable_item *)pool_alloc(allocator);
  }
}
