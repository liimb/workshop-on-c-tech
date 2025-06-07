#include "array_list.h"
#include <string.h>

void arraylist_init(array_list *list, size_t element_size,
                    linear_allocator *allocator) {
  list->data = NULL;
  list->element_size = element_size;
  list->count = 0;
  list->capacity = 0;
  list->allocator = allocator;
}

void arraylist_add(array_list *list, void *element, size_t index) {
  if (index > list->count)
    return;

  size_t s = list->element_size;

  if (list->data == NULL || list->count == list->capacity) {
    size_t new_capacity = list->capacity > 0 ? list->capacity * 2 : 10;
    void *new_data = linear_alloc(list->allocator, new_capacity * s);
    if (!new_data)
      return;

    if (list->data != NULL) {
      memcpy(new_data, list->data, list->count * s);
    }

    list->data = new_data;
    list->capacity = new_capacity;
  }

  if (index < list->count) {
    void *from = list->data + index * s;
    void *to = list->data + (index + 1) * s;
    size_t bytes_to_move = (list->count - index) * s;
    memcpy(to, from, bytes_to_move);
  }

  void *data = list->data + index * s;
  memcpy(data, element, s);

  list->count++;
}

void arraylist_del(array_list *list, size_t index) {
  if (index >= list->count)
    return;

  void *to = list->data + index * list->element_size;
  void *from = list->data + (index + 1) * list->element_size;
  size_t bytes_to_move = (list->count - index - 1) * list->element_size;
  memcpy(to, from, bytes_to_move);

  list->count--;
}

void *arraylist_get(array_list *list, size_t index) {
  if (index >= list->count)
    return NULL;

  return list->data + index * list->element_size;
}

void arraylist_free(array_list *list) {
  linear_destroy(list->allocator);
  list->allocator = NULL;
  list->data = NULL;
  list->count = 0;
  list->capacity = 0;
}
