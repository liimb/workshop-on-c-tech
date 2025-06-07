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

void hashtable_init(size_t capacity, size_t value_size, hash_table *table) {
  size_t total_size = sizeof(hashtable_item) + value_size;

  pool_allocator *allocator = pool_init(total_size, capacity);
  if (!allocator)
    return;

  table->allocator = allocator;
  table->capacity = capacity;
  table->value_size = value_size;
  table->items = allocator->memory;

  for (size_t i = 0; i < capacity; i++) {
    void *block = (char *)table->allocator->memory + i * total_size;
    hashtable_item *item = (hashtable_item *)block;
    item->key = NULL;
    item->value = NULL;
    item->is_deleted = 0;
    item->is_occupied = 0;
  }
}

void hashtable_insert(hash_table *table, const char *key, void *value) {
  size_t hash = hash_func(key, table->capacity);
  size_t steps = 0;
  size_t item_size = sizeof(hashtable_item) + table->value_size;

  while (steps < table->capacity) {
    if (hash >= table->capacity) {
      hash = 0;
    }

    void *block = (char *)table->allocator->memory + hash * item_size;
    hashtable_item *item = (hashtable_item *)block;
    void *val_ptr = (char *)block + sizeof(hashtable_item);

    if (!item->is_occupied || item->is_deleted) {
      memcpy(val_ptr, value, table->value_size);
      item->key = key;
      item->is_occupied = 1;
      item->is_deleted = 0;
      item->value = val_ptr;
      return;
    } else if (item->is_occupied && item->key && strcmp(item->key, key) == 0) {
      memcpy(item->value, value, table->value_size);
      item->is_deleted = 0;
      return;
    }

    hash++;
    steps++;
  }
}

void *hashtable_get(hash_table *table, const char *key) {
  size_t hash = hash_func(key, table->capacity);
  size_t steps = 0;
  size_t item_size = sizeof(hashtable_item) + table->value_size;

  while (steps < table->capacity) {
    if (hash >= table->capacity) {
      hash = 0;
    }

    void *block = (char *)table->allocator->memory + hash * item_size;
    hashtable_item *item = (hashtable_item *)block;

    if (item->is_occupied) {
      if (!item->is_deleted && item->key && strcmp(item->key, key) == 0) {
        return item->value;
      }
    } else if (!item->is_occupied && !item->is_deleted) {
      return NULL;
    }

    hash++;
    steps++;
  }

  return NULL;
}

void hashtable_delete(hash_table *table, const char *key) {
  size_t hash = hash_func(key, table->capacity);
  size_t steps = 0;
  size_t item_size = sizeof(hashtable_item) + table->value_size;

  while (steps < table->capacity) {
    if (hash >= table->capacity) {
      hash = 0;
    }

    void *block = (char *)table->allocator->memory + hash * item_size;
    hashtable_item *item = (hashtable_item *)block;

    if (item->is_occupied) {
      if (!item->is_deleted && item->key && strcmp(item->key, key) == 0) {
        item->is_deleted = 1;
        item->is_occupied = 0;
        item->key = NULL;
        item->value = NULL;
        return;
      }
    } else if (!item->is_occupied && !item->is_deleted) {
      return;
    }

    hash++;
    steps++;
  }
}

void hashtable_free(hash_table *table) {
  if (table == NULL) {
    return;
  }

  pool_close(table->allocator);
}
