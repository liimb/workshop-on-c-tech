#include <stdio.h>

#define ERROR -1
#define SUCCESS 0

typedef struct ref_context {
  void *(*alloc)(void *allocator);
  void (*dealloc)(void *allocator, void *ptr);
  void *mem_context;
} ref_context;

typedef struct dependent_ref {
  struct ref_count_t *ref;
  struct dependent_ref *next;
} dependent_ref;

typedef void (*dtor)(void *object);
typedef void (*ctor)(void *object);

typedef struct ref_count_t {
  size_t count;
  void *object;
  ctor constructor;
  dtor destructor;
  dependent_ref *dependencies;
  ref_context ref_ctx;
} ref_count_t;

int ref_count_create(ref_count_t **out_ref, void *object, ref_context ctx);
int ref_count_create_ext(ref_count_t **out_ref, void *object, ref_context ctx,
                         ctor constructor, dtor destructor);
int ref_count_retain(ref_count_t *ref);
int ref_count_release(ref_count_t *ref);
int ref_count_add_dependency(ref_count_t *parent, ref_count_t *child);

void default_constructor(void *object);
void default_destructor(void *object);
