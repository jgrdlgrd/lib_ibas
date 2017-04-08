//
// Created by Павел on 16.03.2017.
//

#include "vector.h"

//we couldn't include it in the header because of a circular dependency
#include "../base/string.h"

Vector_t __Vector_create(size_t elemSize, size_t capacity, ToString_t toStringFn) {
  if (!elemSize) throw(IllegalArgumentException, "Vector: elemSize must be greater than zero!");

  Vector_t vec = Ibas.alloc(sizeof(Vector_s), NULL);

  vec->class = &Vector_class;
  vec->size = vec->capacity = 0;
  vec->storage = NULL;
  vec->elemSize = elemSize;
  vec->toStringFn = toStringFn;

  Vector.ensureCapacity(vec, capacity);

  return vec;
}

void __Vector_destroy(Vector_t vec) {
  if (!vec) return;

  Vector.clear(vec);
  free(vec);
}

String_t __Vector_toString(Vector_t vec) {
  if (vec->toStringFn) return List.toString(vec);
  else return String.format("[[Vector size=%zd elemSize=%zd storage=%p]]", vec->size, vec->elemSize, vec->storage);
}

void __Vector_ensureCapacity(Vector_t vec, size_t capacity) {
  if (capacity <= vec->capacity) return;

  Object storage = realloc(vec->storage, capacity * vec->elemSize);
  if (!storage) throw(NotEnoughMemoryException, "Could not increase the vector's capacity");

  vec->storage = storage;
  vec->capacity = capacity;
}

ToString_t __Vector_getToStringFn(Vector_t vec) {
  return vec->toStringFn;
}

Object __Vector_get(Vector_t vec, int i) {
  if (i < 0 || i >= vec->size) throw(IllegalArgumentException, "Vector: index out of bounds!");

  return Vector.iterGet(vec, Vector.iter(vec, i));
}

void __Vector_set(Vector_t vec, int i, Object val) {
  if (i < 0 || i >= vec->size) throw(IllegalArgumentException, "Vector: index out of bounds!");

  Vector.iterSet(vec, Vector.iter(vec, i), val);
}

void __Vector_insertSlice(Vector_t vec, int i, void *slice, size_t size) {
  if (i < 0 || i > vec->size) throw(IllegalArgumentException, "Vector: index out of bounds!");

  size_t cap = vec->capacity;
  while (cap < vec->size + size) {
    cap = max((size_t)(cap * VECTOR_GROWTH_FACTOR), cap + 1);
  }
  Vector.ensureCapacity(vec, cap);

  Object ptr = vec->storage + i * vec->elemSize;
  memmove(ptr + size * vec->elemSize, ptr, vec->elemSize * (vec->size - i));
  memcpy(ptr, slice, size * vec->elemSize);
  vec->size += size;
}

void __Vector_insert(Vector_t vec, int i, Object val) {
  __Vector_insertSlice(vec, i, val, 1);
}

void __Vector_add(Vector_t vec, Object val) {
  Vector.insert(vec, (int) vec->size, val);
}

void __Vector_insertAll(Vector_t vec1, int i, Vector_t vec2) {
  if (vec1->elemSize != vec2->elemSize) throw(IllegalArgumentException, "Vector: element sizes don't match!");

  __Vector_insertSlice(vec1, i, vec2->storage, vec2->size);
}

void __Vector_addAll(Vector_t vec1, Vector_t vec2) {
  Vector.insertAll(vec1, (int) vec1->size, vec2);
}

void __Vector_remove(Vector_t vec, int i) {
  Object ptr = Vector.get(vec, i);
  memmove(ptr, ptr + vec->elemSize, vec->elemSize * (vec->size - i - 1));
  vec->size--;
}

void __Vector_clear(Vector_t vec) {
  free(vec->storage);

  vec->size = vec->capacity = 0;
  vec->storage = NULL;
}

int __Vector_indexOf(Vector_t vec, Object val) {
  Object iter = Vector.find(vec, val);

  if(iter == Vector.end(vec)) return -1;
  else return (int) ((iter - vec->storage) / vec->elemSize);
}

Object __Vector_iter(Vector_t vec, int i) {
  if (i < 0 || i >= vec->size) return Vector.end(vec);
  else return vec->storage + i * vec->elemSize;
}

Object __Vector_begin(Vector_t vec) {
  return vec->storage;
}

Object __Vector_end(Vector_t vec) {
  return vec->storage + vec->size * vec->elemSize;
}

Object __Vector_find(Vector_t vec, Object val) {
  Object it = Vector.begin(vec);
  for (; it != Vector.end(vec); it = Vector.iterNext(vec, it)) {
    if (!memcmp(Vector.iterGet(vec, it), val, vec->elemSize)) break;
  }

  return it;
}

Object __Vector_iterNext(Vector_t vec, Object iter) {
  return Vector.iterJump(vec, iter, 1);
}

Object __Vector_iterPrev(Vector_t vec, Object iter) {
  return Vector.iterJump(vec, iter, -1);
}

int __Vector_iterToIndex(Vector_t vec, Object iter) {
  return (int) ((iter - vec->storage) / vec->elemSize);
}

Object __Vector_iterJump(Vector_t vec, Object iter, int length) {
  return Vector.iter(vec, __Vector_iterToIndex(vec, iter) + length);
}

Object __Vector_iterGet(Vector_t vec, Object iter) {
  return iter;
}

void __Vector_iterSet(Vector_t vec, Object iter, Object val) {
  memcpy(iter, val, vec->elemSize);
}

void __Vector_iterInsert(Vector_t vec, Object iter, Object val) {
  Vector.insert(vec, __Vector_iterToIndex(vec, iter), val);
}

void __Vector_iterInsertAll(Vector_t vec1, Object iter, Vector_t vec2) {
  Vector.insertAll(vec1, __Vector_iterToIndex(vec1, iter), vec2);
}

void __Vector_iterRemove(Vector_t vec, Object iter) {
  Vector.remove(vec, __Vector_iterToIndex(vec, iter));
}

Vector_c Vector = {
    __Vector_create,
    __Vector_destroy,
    __Vector_toString,
    __Vector_ensureCapacity,
    __Vector_getToStringFn,
    __Vector_get,
    __Vector_set,
    __Vector_add,
    __Vector_insert,
    __Vector_addAll,
    __Vector_insertAll,
    __Vector_remove,
    __Vector_clear,
    __Vector_indexOf,
    __Vector_iter,
    __Vector_begin,
    __Vector_end,
    __Vector_find,
    __Vector_iterNext,
    __Vector_iterPrev,
    __Vector_iterJump,
    __Vector_iterGet,
    __Vector_iterSet,
    __Vector_iterInsert,
    __Vector_iterInsertAll,
    __Vector_iterRemove
};

Object Vector_class[] = {implements(Vector, List, 4), NULL};
