//
// Created by Павел on 16.03.2017.
//

//TODO add slice, clone, removeRange, indexOf, implement toString
//TODO think about iterators

#pragma once

#include "../base/base.h"

#define VECTOR_GROWTH_FACTOR 1.5

declareType(Vector, {
  size_t size;
  size_t elemSize;
  size_t capacity;
  Object storage;
})

declareClass(Vector, {
  Vector_t (*create)(size_t size, size_t elemSize);
  void (*destroy)(Vector_t vec);

  Object (*get)(Vector_t vec, int i);
  void (*set)(Vector_t vec, int i, Object val);

  void (*add)(Vector_t vec, Object val);
  void (*insert)(Vector_t vec, int i, Object val);
  void (*remove)(Vector_t vec, int i);

  void (*addAll)(Vector_t vec1, Vector_t vec2);
  void (*insertAll)(Vector_t vec, int i, Vector_t vec2);

  void (*forEach)(Vector_t vec, bool (*func)(Vector_t vec, Object element, Object ctx), Object ctx);
  int (*find)(Vector_t vec, Object obj);

  void (*clear)(Vector_t vec);

  /*
   * we do not use String_t here to avoid circular dependency
   * it's ok since Vector_t and String_t are synonyms
   */
  Vector_t (*toString)(Vector_t vec);

  void (*ensureCapacity)(Vector_t vec, size_t capacity);
})
