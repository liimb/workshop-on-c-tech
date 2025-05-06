#include "hash_table.h"
#include "pool_allocator.h"
#include <stdlib.h>
#include <string.h>

size_t hash_func(const char *key, size_t capacity) {
  size_t hash = 0;
  while (*key) {
    hash++;
    key++;
  }
  return hash % capacity;
}

hash_table *hashtable_init(size_t capacity, pool_allocator *allocator) {
  size_t total_size = sizeof(hash_table) + sizeof(hashtable_item) * capacity;

  allocator = pool_init(total_size, 1);

  if (!allocator)
    return NULL;

  hash_table *table = (hash_table *)pool_alloc(allocator);
  if (!table) {
    pool_close(allocator);
    return NULL;
  }

  table->allocator = allocator;
  table->capacity = capacity;

  for (size_t i = 0; i < capacity; i++) {
    table->items[i].key = NULL;
    table->items[i].value = NULL;
    table->items[i].is_deleted = 0;
    table->items[i].is_occupied = 0;
  }

  return table;
}

void hashtable_insert(hash_table *table, const char *key, void *value) {
  size_t hash = hash_func(key, table->capacity);
  size_t original_hash = hash;

  int a = 0;

  while (a <= table->capacity) {
    if (hash >= (table->capacity)) {
      hash = 0;
    }

    if (table->items[hash].is_occupied == 0 || table->items[hash].is_deleted) {
      table->items[hash].value = value;
      table->items[hash].key = key;
      table->items[hash].is_occupied = 1;
      table->items[hash].is_deleted = 0;
      return;
    } else if (table->items[hash].is_occupied &&
               table->items[hash].key != NULL &&
               strcmp(table->items[hash].key, key) == 0) {
      table->items[hash].value = value;
      table->items[hash].is_deleted = 0;
      return;
    }

    a++;
    hash++;
  }
}

void *hashtable_get(hash_table *table, const char *key) {
  size_t hash = hash_func(key, table->capacity);
  int a = 0;

  while (a < table->capacity) {
    if (hash >= (table->capacity)) {
      hash = 0;
    }

    hashtable_item *item = &table->items[hash];

    if (item->is_occupied) {
      if (!item->is_deleted && item->key != NULL &&
          strcmp(item->key, key) == 0) {
        return item->value;
      }
    } else if (!item->is_occupied && !item->is_deleted) {
      return NULL;
    }

    hash++;
    a++;
  }

  return NULL;
}

void hashtable_delete(hash_table *table, const char *key) {
  size_t hash = hash_func(key, table->capacity);
  int steps = 0;

  while (steps < table->capacity) {
    hashtable_item *item = &table->items[hash];

    if (item->is_occupied) {
      if (!item->is_deleted && item->key != NULL &&
          strcmp(item->key, key) == 0) {
        item->is_deleted = 1;
        item->is_occupied = 0;
        item->value = NULL;
        item->key = NULL;
        return;
      }
    } else if (!item->is_occupied && !item->is_deleted) {
      return;
    }

    hash = (hash + 1) % table->capacity;
    steps++;
  }
}

void hashtable_free(hash_table *table) {
  if (table == NULL) {
    return;
  }

  pool_close(table->allocator);
}
