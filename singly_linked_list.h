typedef struct node {
  int value;
  struct node *next;
} node;

node *list_create(int value);
node *list_get_at(node **list, int index);
int list_length(node *list);
void list_add_end(node **list, int value);
void list_add_start(node **list, int value);
void list_add_middle(node **list, int value);
void list_add_at(node **list, int index, int value);
void list_delete_at(node **list, int index);
void list_print(node *list);
