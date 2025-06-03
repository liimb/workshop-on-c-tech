#include "gc.h"

int ref_count_create(ref_count_t **out_ref, void *object, ref_context ctx) {
  if (!out_ref || !ctx.alloc)
    return ERROR;

  ref_count_t *ref = ctx.alloc(ctx.mem_context);
  if (!ref)
    return ERROR;

  ref->count = 1;
  ref->object = object;
  ref->dependencies = NULL;
  ref->ref_ctx = ctx;

  *out_ref = ref;
  return SUCCESS;
}

int ref_count_retain(ref_count_t *ref) {
  if (!ref)
    return ERROR;

  ref->count++;
  return SUCCESS;
}

int ref_count_add_dependency(ref_count_t *parent, ref_count_t *child) {
  if (!parent || !child)
    return ERROR;

  dependent_ref *dep = parent->ref_ctx.alloc(parent->ref_ctx.mem_context);

  if (!dep)
    return ERROR;

  dep->ref = child;
  dep->next = parent->dependencies;
  parent->dependencies = dep;

  return ref_count_retain(child);
}

int ref_count_release(ref_count_t *ref) {
  if (!ref)
    return ERROR;

  if (ref->count == 0)
    return ERROR;

  ref->count--;

  if (ref->count == 0) {
    dependent_ref *dep = ref->dependencies;
    while (dep) {
      dependent_ref *next = dep->next;
      ref_count_release(dep->ref);
      ref->ref_ctx.dealloc(ref->ref_ctx.mem_context, dep);
      dep = next;
    }
    ref->dependencies = NULL;

    void *mem_ctx = ref->ref_ctx.mem_context;
    void (*dealloc)(void *, void *) = ref->ref_ctx.dealloc;

    dealloc(mem_ctx, ref);
  }

  return SUCCESS;
}
