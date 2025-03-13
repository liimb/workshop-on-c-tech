#include "stack.h"
#include <assert.h>

void stack_create_test() {
  stack_array *stack = stack_create();

  assert(stack->size == FIRST_SIZE);
  assert(stack->top == 0);

  stack_free(&stack);
}

void stack_push_test() {
  stack_array *stack = stack_create();
  stack_push(&stack, 2);
  stack_push(&stack, 3);
  stack_push(&stack, 4);

  assert(stack->top == 3);

  stack_free(&stack);
}

void stack_pop_test() {
  stack_array *stack = stack_create();
  stack_push(&stack, 2);
  stack_push(&stack, 3);
  stack_push(&stack, 4);

  assert(stack_pop(&stack) == 4);
  assert(stack_pop(&stack) == 3);
  assert(stack_pop(&stack) == 2);

  stack_free(&stack);
}

void stack_is_empty_test() {
  stack_array *stack = stack_create();
  stack_push(&stack, 4);
  stack_pop(&stack);

  assert(stack_is_empty(stack) == 1);

  stack_free(&stack);
}

int main() {
  stack_create_test();
  stack_push_test();
  stack_pop_test();
  stack_is_empty_test();

  return 0;
}
