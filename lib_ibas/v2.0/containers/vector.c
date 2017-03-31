//
// Created by Павел on 16.03.2017.
//

#include "vector.h"

//we couldn't include it in the header because of a circular dependency
#include "../lib_ibas.h"

Vector_t __Vector_create(size_t capacity, size_t elemSize) {
  if (!elemSize) throw(IllegalArgumentException, "ElemSize must be greater than zero");

  Vector_t vec = Ibas.alloc(sizeof(Vector_s), NULL);
  if (!vec) throw(NotEnoughMemoryException, "Could not allocate the vector");

  vec->storage = NULL;
  vec->capacity = vec->size = 0;
  vec->elemSize = elemSize;

  Vector.ensureCapacity(vec, capacity);

  return vec;
}

void __Vector_destroy(Vector_t vec) {
  if (vec) {
    free(vec->storage);
    free(vec);
  }
}

Object __Vector_get(Vector_t vec, int i) {
  if (i < 0 || i >= vec->size) throw(IllegalArgumentException, "Vector index out of bounds");
  return vec->storage + i * vec->elemSize;
}

void __Vector_set(Vector_t vec, int i, Object val) {
  memcpy(Vector.get(vec, i), val, vec->elemSize);
}

void __Vector_ensureCapacity(Vector_t vec, size_t capacity) {
  if (capacity <= vec->capacity) return;

  Object storage = realloc(vec->storage, capacity * vec->elemSize);
  if (!storage) throw(NotEnoughMemoryException, "Could not increase the vector's capacity");

  vec->storage = storage;
  vec->capacity = capacity;
}

void __Vector_insertSlice(Vector_t vec, int i, void *slice, size_t size) {
  if (i < 0 || i > vec->size) throw(IllegalArgumentException, "Vector index out of bounds");

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

void __Vector_insertAll(Vector_t vec1, int i, Vector_t vec2) {
  if (vec1->elemSize != vec2->elemSize) throw(IllegalArgumentException, "Vector element sizes don't match!");

  __Vector_insertSlice(vec1, i, vec2->storage, vec2->size);
}

void __Vector_addAll(Vector_t vec1, Vector_t vec2) {
  Vector.insertAll(vec1, (int) vec1->size, vec2);
}

void __Vector_insert(Vector_t vec, int i, Object val) {
  __Vector_insertSlice(vec, i, val, 1);
}

void __Vector_add(Vector_t vec, Object val) {
  Vector.insert(vec, (int) vec->size, val);
}

void __Vector_remove(Vector_t vec, int i) {
  Object ptr = __Vector_get(vec, i);
  memmove(ptr, ptr + vec->elemSize, vec->elemSize * (vec->size - i - 1));
  vec->size--;
}

void __Vector_forEach(Vector_t vec, bool (*func)(Vector_t vec, Object element, Object ctx), Object ctx) {
  Object el = vec->storage;
  for (int i = 0; i < vec->size && !func(vec, el, ctx); i++, el += vec->elemSize);
}

int __Vector_find(Vector_t vec, Object obj) {
  Object el = vec->storage;
  for (int i = 0; i < vec->size; i++, el += vec->elemSize) {
    if (!memcpy(el, obj, vec->elemSize)) return i;
  }

  return -1;
}

void __Vector_clear(Vector_t vec) {
  free(vec->storage);
  vec->size = vec->capacity = 0;
}

String_t __Vector_toString(Vector_t vec) {
  return String.format("[[Vector size=%zd elemSize=%zd storage=%p]]", vec->size, vec->elemSize, vec->storage);
}

Vector_t_ Vector = {
    __Vector_create,
    __Vector_destroy,
    __Vector_toString,
    __Vector_get,
    __Vector_set,
    __Vector_add,
    __Vector_insert,
    __Vector_addAll,
    __Vector_insertAll,
    __Vector_remove,
    __Vector_clear,
    __Vector_forEach,
    __Vector_find,
    __Vector_ensureCapacity
};
