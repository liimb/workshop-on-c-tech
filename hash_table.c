#include "hash_table.h"
#include "pool_allocator.h"

void hashtable_init(hash_table* table, size_t capacity, pool_allocator* allocator){
    table->allocator = allocator;
    table->capacity = capacity;

    allocator = pool_init(sizeof(hashtable_item), capacity);

    for(size_t i = 0; i < capacity; i++) {
        table->items[i] = (hashtable_item*)pool_alloc(allocator);
    }
}
