#include "singly_linked_list.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void list_create_test() {
  node *list = list_create(1234);
  assert(list->value == 1234);
  assert(list->next == NULL);

  list_free(list);
}

void list_add_at_test() {
  node *list = list_create(5);
  list_add_at(&list, -6, 1);
  list_add_at(&list, 0, 1);
  list_add_at(&list, 10, 3);
  list_add_at(&list, 1, 3);

  assert(list_get_at(&list, 1)->value == 3);

  list_free(list);
}

void list_get_at_test() {
  node *list = list_create(5);
  list_add_at(&list, 0, 1);
  list_add_at(&list, 1, 30);

  assert(list_get_at(&list, -1) == NULL);
  assert(list_get_at(&list, 100) == NULL);
  assert(list_get_at(&list, 1)->value == 30);

  list_free(list);
}

void list_delete_at_test() {
  node *list = list_create(5);
  list_add_end(&list, 6);
  list_add_end(&list, 7);
  list_add_end(&list, 10);

  list_delete_at(&list, 20);
  list_delete_at(&list, -1);
  list_delete_at(&list, 2);

  assert(list_length(list) == 3);
  assert(list_get_at(&list, 2)->value == 10);

  list_free(list);
}

void list_length_test() {
  node *list = list_create(5);
  list_add_end(&list, 6);
  list_add_end(&list, 7);
  list_add_end(&list, 10);

  list_delete_at(&list, 3);

  list_add_at(&list, 3, 3);
  list_add_at(&list, 3, 4);

  assert(list_length(list) == 5);

  list_free(list);
}

int main() {
  list_create_test();
  list_add_at_test();
  list_get_at_test();
  list_delete_at_test();
  list_length_test();

  return 0;
}
