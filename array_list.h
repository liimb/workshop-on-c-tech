#include "linear_allocator.h"

typedef struct array_list {
  void *data;
  size_t element_size;
  size_t count;
  size_t capacity;
  linear_allocator *allocator;
} array_list;

void arraylist_init(array_list *list, size_t element_size,
                    linear_allocator *allocator);
void arraylist_add(array_list *list, void *data, size_t index);
void *arraylist_get(array_list *list, size_t index);
void arraylist_del(array_list *list, size_t index);
void arraylist_free(array_list *list);
