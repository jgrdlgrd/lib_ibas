//
// Created by Павел on 16.03.2017.
//

#pragma once

#include "lib_ibas/v2.0/base/base.h"
#include "generic-list.h"

#define VECTOR_GROWTH_FACTOR 1.5

declareFields(Vector, {
  size_t size;
  size_t elemSize;
  size_t capacity;
  Object storage;
})

declareClass(Vector, {
  Vector_t (*create)(size_t size, size_t elemSize);

  genericListMethodsDeclStripped(Vector_t, vec, Object)

  /*
   * we do not use String_t here to avoid circular dependency
   * it's ok since Vector_t and String_t are synonyms
   */
  Vector_t (*toString)(Vector_t vec);

  void (*ensureCapacity)(Vector_t vec, size_t capacity);
})
