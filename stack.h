typedef struct stack_array {
  int *data;
  int size;
  int top;
} stack_array;

#define FIRST_SIZE 10
#define PLUS_SIZE 10

stack_array *stack_create();
void stack_push(stack_array **stack, int value);
int stack_pop(stack_array **stack);
void stack_resize(stack_array *stack);
int stack_is_empty(stack_array *stack);
void stack_free(stack_array **stack);
void stack_print(stack_array *stack);