#include "singly_linked_list.h"
#include <stdio.h>
#include <stdlib.h>

node *list_create(int value) {
  node *list = (struct node *)malloc(sizeof(struct node));
  list->value = value;
  list->next = NULL;
  return list;
}

int list_length(node *list) {
  int length = 1;
  if (list->next == NULL) {
    return length;
  }

  node *last_node = list->next;

  while (last_node != NULL) {
    last_node = last_node->next;
    length++;
  }

  return length;
}

void list_add_end(node **list, int value) {
  node *new_node = (struct node *)malloc(sizeof(struct node));
  new_node->value = value;
  new_node->next = NULL;

  if ((*list)->next == NULL) {
    (*list)->next = new_node;
    return;
  }
  node *last_node = (*list)->next;

  while (last_node->next != NULL) {
    last_node = last_node->next;
  }

  last_node->next = new_node;
}

void list_add_start(node **list, int value) {
  node *new_node = (struct node *)malloc(sizeof(struct node));
  new_node->value = value;

  if ((*list)->next == NULL) {
    new_node->next = (*list);
    *list = new_node;
  } else {
    new_node->next = (*list);
    (*list) = new_node;
  }
}

void list_add_at(node **list, int index, int value) {
  if (index == 0) {
    list_add_start(list, value);
    return;
  }

  node *before = (*list);
  node *after = (*list)->next;

  int a = 1;

  while (after != NULL && a < index) {
    before = after;
    after = after->next;
    a++;
  }

  if (a != index) {
    return;
  }

  if (a > index) {
    return;
  }

  node *new_node = (struct node *)malloc(sizeof(struct node));
  new_node->value = value;

  before->next = new_node;
  new_node->next = after;
}

void list_add_middle(node **list, int value) {
  list_add_at(list, list_length(*list) / 2, value);
}

void list_delete_at(node **list, int index) {
  if ((*list) == NULL || index < 0) {
    return;
  }

  node *node_for_delete = *list;

  if (index == 0) {

    if (node_for_delete->next == NULL) {
      free(node_for_delete);
      return;
    }

    node *temp = node_for_delete->next;
    *list = temp;
    free(node_for_delete);
    return;
  }

  int a = 0;
  node *before_delete;

  while (node_for_delete->next != NULL) {
    before_delete = node_for_delete;
    node_for_delete = node_for_delete->next;
    a++;

    if (a == index) {
      break;
    }
  }

  if (a < index) {
    return;
  }

  node *temp = node_for_delete->next;
  before_delete->next = temp;
  free(node_for_delete);
}

node *list_get_at(node **list, int index) {
  if ((*list) == NULL || index < 0) {
    return NULL;
  }

  node *last_node = *list;

  int a = 0;

  while (a < index) {

    if (last_node->next != NULL) {
      last_node = last_node->next;
      a++;
    } else {
      return NULL;
    }
  }

  return last_node;
}

void list_print(node *list) {
  if (list == NULL) {
    return;
  }

  node *last_node = list;

  printf("%i \n", last_node->value);

  while (last_node->next != NULL) {
    last_node = last_node->next;
    printf("%i \n", last_node->value);
  }
}
