#include "gc.h"
#include <stdbool.h>

void default_constructor(void *object) { (void)object; }

void default_destructor(void *object) { (void)object; }

int ref_count_create(ref_count_t **out_ref, void *object, ref_context *ctx) {
  return ref_count_create_ext(out_ref, object, ctx, NULL, NULL);
}

int ref_count_create_ext(ref_count_t **out_ref, void *object, ref_context *ctx,
                         ctor constructor, dtor destructor) {
  if (!out_ref || !ctx->alloc)
    return ERROR;

  ref_count_t *ref = ctx->alloc(ctx->mem_context);
  if (!ref)
    return ERROR;

  ref->count = 1;
  ref->object = object;
  ref->dependencies = NULL;
  ref->ref_ctx = ctx;
  ref->constructor = constructor ? constructor : default_constructor;
  ref->destructor = destructor ? destructor : default_destructor;

  if (ref->constructor && object)
    ref->constructor(object);

  ref->next_global = ctx->all_refs_head;
  ctx->all_refs_head = ref;

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

  dependent_ref *dep = parent->ref_ctx->alloc(parent->ref_ctx->mem_context);

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
      ref->ref_ctx->dealloc(ref->ref_ctx->mem_context, dep);
      dep = next;
    }
    ref->dependencies = NULL;

    void *mem_ctx = ref->ref_ctx->mem_context;
    void (*dealloc)(void *, void *) = ref->ref_ctx->dealloc;

    if (ref->object) {
      ref->destructor(ref->object);
    }

    dealloc(mem_ctx, ref);
  }

  return SUCCESS;
}

void gc_mark(ref_count_t *ref) {
  if (!ref || ref->marked)
    return;

  ref->marked = 1;

  for (dependent_ref *dep = ref->dependencies; dep; dep = dep->next) {
    gc_mark(dep->ref);
  }
}

void gc_collect(ref_context *ctx) {
  if (!ctx)
    return;

  for (ref_count_t *ref = ctx->all_refs_head; ref; ref = ref->next_global) {
    ref->marked = 0;
  }

  for (ref_count_t *ref = ctx->all_refs_head; ref; ref = ref->next_global) {
    bool externally_referenced = true;
    for (ref_count_t *other = ctx->all_refs_head; other;
         other = other->next_global) {
      if (other == ref)
        continue;
      for (dependent_ref *dep = other->dependencies; dep; dep = dep->next) {
        if (dep->ref == ref) {
          externally_referenced = false;
          break;
        }
      }
      if (!externally_referenced)
        break;
    }

    if (externally_referenced && ref->count > 0) {
      gc_mark(ref);
    }
  }

  ref_count_t **prev = &ctx->all_refs_head;
  ref_count_t *cur = ctx->all_refs_head;
  while (cur) {
    ref_count_t *next = cur->next_global;
    if (!cur->marked) {
      cur->count = 1;
      ref_count_release(cur);
      *prev = next;
    } else {
      prev = &cur->next_global;
    }
    cur = next;
  }
}
