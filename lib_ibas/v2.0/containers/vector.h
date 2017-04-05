//
// Created by Павел on 16.03.2017.
//

//TODO add slice, clone, removeRange, indexOf
//TODO think about iterators

#pragma once

#include "../base/base.h"

#define VECTOR_GROWTH_FACTOR 1.5

declareType(Vector, {
  size_t size;
  size_t elemSize;
  size_t capacity;
  Object storage;
});

declareClass(Vector, {
  Vector_t (*create)(size_t size, size_t elemSize);
  void (*destroy)(Vector_t vec);
  /*
   * we do not use String_t here to avoid circular dependency
   * it's ok since Vector_t and String_t are synonyms
   */
  Vector_t (*toString)(Vector_t vec);

  Object (*get)(Vector_t vec, int i);
  void (*set)(Vector_t vec, int i, Object val);

  void (*add)(Vector_t vec, Object val);
  void (*insert)(Vector_t vec, int i, Object val);
  void (*addAll)(Vector_t vec1, Vector_t vec2);
  void (*insertAll)(Vector_t vec, int i, Vector_t vec2);

  void (*remove)(Vector_t vec, int i);
  void (*clear)(Vector_t vec);

  void (*forEach)(Vector_t vec, bool (*func)(Vector_t vec, Object element, Object ctx), Object ctx);
  int (*find)(Vector_t vec, Object obj);

  void (*ensureCapacity)(Vector_t vec, size_t capacity);
});

//export internals
Vector_t __Vector_create(size_t capacity, size_t elemSize);
void __Vector_destroy(Vector_t vec);
Object __Vector_get(Vector_t vec, int i);
void __Vector_set(Vector_t vec, int i, Object val);
void __Vector_ensureCapacity(Vector_t vec, size_t capacity);
void __Vector_insertSlice(Vector_t vec, int i, void *slice, size_t size);
void __Vector_insertAll(Vector_t vec1, int i, Vector_t vec2);
void __Vector_addAll(Vector_t vec1, Vector_t vec2);
void __Vector_insert(Vector_t vec, int i, Object val);
void __Vector_add(Vector_t vec, Object val);
void __Vector_remove(Vector_t vec, int i);
void __Vector_forEach(Vector_t vec, bool (*func)(Vector_t vec, Object element, Object ctx), Object ctx);
int __Vector_find(Vector_t vec, Object obj);
void __Vector_clear(Vector_t vec);
Vector_t __Vector_toString(Vector_t vec);
