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
    hashtable_item* item = table->items[i];
    item = (hashtable_item *)pool_alloc(allocator);
    item->key = NULL;
    item->value = NULL;
    item->is_deleted = 0;
    item->is_occupied = 0;
  }
}

void hashtable_insert(hash_table *table, const char *key, void *value) {
  size_t hash = hash_func(key, table->capacity);

  
}

void* hashtable_get(hash_table *table, const char *key) {

  return 0;

}

void hashtable_del(hash_table *table, const char *key) {

}

void hashtable_free(hash_table *table) {

}
