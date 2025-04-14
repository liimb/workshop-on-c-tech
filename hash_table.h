#include <stdio.h>
#include "pool_allocator.h"

typedef struct hashtable_item
{
    char* key;
    void* value;
    int is_occupied;
    int is_deleted;
} hashtable_item;

typedef struct hash_table
{
    hashtable_item** items;
    size_t capacity;
    pool_allocator* allocator;
} hash_table;

void hashtable_init(hash_table* table, size_t capacity, pool_allocator* allocator);
void hashtable_insert(hash_table* table, const char* key, void* value);
void* hashtable_get(hash_table* table, const char* key);
void hashtable_del(hash_table* table, const char* key);
void hashtable_free(hash_table* table);
