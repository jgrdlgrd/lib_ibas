//
// Created by Павел on 16.03.2017.
//

//TODO add slice, clone, removeRange, indexOf

#pragma once

#include "../base/base.h"

#define VECTOR_GROWTH_FACTOR 1.5

declareType(Vector, {
  Object class;
  size_t size;
  size_t elemSize;
  size_t capacity;
  Object storage;
  //TODO find a way to solve this problem
  Object (*toStringFn)(Object);
});

/*
 * we do not use String_t and ToString_t below to avoid circular dependency
 * it's ok since Vector_t and String_t are synonyms
 */

declareClass(Vector, {
  Vector_t (*create)(size_t elemSize, size_t capacity, Vector_t (*toStringFn)(Object));
  void (*destroy)(Vector_t vec);
  Vector_t (*toString)(Vector_t vec);

  void (*ensureCapacity)(Vector_t vec, size_t capacity);

  Object (*get)(Vector_t vec, int i);
  void (*set)(Vector_t vec, int i, Object val);

  void (*add)(Vector_t vec, Object val);
  void (*insert)(Vector_t vec, int i, Object val);
  void (*addAll)(Vector_t vec1, Vector_t vec2);
  void (*insertAll)(Vector_t vec1, int i, Vector_t vec2);

  void (*remove)(Vector_t vec, int i);
  void (*clear)(Vector_t vec);

  int (*indexOf)(Vector_t vec, Object val);

  Object (*iter)(Vector_t vec, int i);
  Object (*begin)(Vector_t vec);
  Object (*end)(Vector_t vec);
  Object (*find)(Vector_t vec, Object val);

  Object (*iterNext)(Vector_t vec, Object iter);
  Object (*iterPrev)(Vector_t vec, Object iter);
  Object (*iterJump)(Vector_t vec, Object iter, int length);

  Object (*iterGet)(Vector_t vec, Object iter);
  void (*iterSet)(Vector_t vec, Object iter, Object val);

  void (*iterInsert)(Vector_t vec, Object iter, Object val);
  void (*iterInsertAll)(Vector_t vec1, Object iter, Vector_t vec2);

  void (*iterRemove)(Vector_t vec, Object iter);
});

//expose internals
Vector_t __Vector_create(size_t elemSize, size_t capacity, Vector_t (*toStringFn)(Object));
void __Vector_destroy(Vector_t vec);
Vector_t __Vector_toString(Vector_t vec);
void __Vector_ensureCapacity(Vector_t vec, size_t capacity);
Object __Vector_get(Vector_t vec, int i);
void __Vector_set(Vector_t vec, int i, Object val);
void __Vector_insertSlice(Vector_t vec, int i, void *slice, size_t size);
void __Vector_insert(Vector_t vec, int i, Object val);
void __Vector_add(Vector_t vec, Object val);
void __Vector_insertAll(Vector_t vec1, int i, Vector_t vec2);
void __Vector_addAll(Vector_t vec1, Vector_t vec2);
void __Vector_remove(Vector_t vec, int i);
void __Vector_clear(Vector_t vec);
int __Vector_indexOf(Vector_t vec, Object val);
Object __Vector_iter(Vector_t vec, int i);
Object __Vector_begin(Vector_t vec);
Object __Vector_end(Vector_t vec);
Object __Vector_find(Vector_t vec, Object val);
Object __Vector_iterNext(Vector_t vec, Object iter);
Object __Vector_iterPrev(Vector_t vec, Object iter);
int __Vector_iterToIndex(Vector_t vec, Object iter);
Object __Vector_iterJump(Vector_t vec, Object iter, int length);
Object __Vector_iterGet(Vector_t vec, Object iter);
void __Vector_iterSet(Vector_t vec, Object iter, Object val);
void __Vector_iterInsert(Vector_t vec, Object iter, Object val);
void __Vector_iterInsertAll(Vector_t vec1, Object iter, Vector_t vec2);
void __Vector_iterRemove(Vector_t vec, Object iter);
