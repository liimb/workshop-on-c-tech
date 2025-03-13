#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

stack_array *stack_create() {
  stack_array *stack = malloc(sizeof(stack_array));
  stack->size = FIRST_SIZE;
  stack->data = malloc(stack->size * sizeof(int));
  stack->top = 0;
  return stack;
}

void stack_resize(stack_array *stack) {
  stack->size += PLUS_SIZE;
  stack->data = realloc(stack->data, stack->size * sizeof(int));
}

int stack_is_empty(stack_array *stack) {
  if (stack->top == 0) {
    return 1;
  } else {
    return 0;
  }
}

void stack_push(stack_array **stack, int value) {
  if ((*stack)->top >= (*stack)->size) {
    stack_resize(*stack);
  }

  (*stack)->data[(*stack)->top] = value;
  (*stack)->top++;
}

int stack_pop(stack_array **stack) {
  (*stack)->top--;
  return (*stack)->data[(*stack)->top];
}

void stack_free(stack_array **stack) {
  free((*stack)->data);
  free(*stack);
  *stack = NULL;
}
