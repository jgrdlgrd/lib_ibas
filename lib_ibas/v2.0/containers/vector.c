//
// Created by Павел on 16.03.2017.
//

#include "vector.h"
#include "lib_ibas/v2.0/lib_ibas.h"

Vector_t __Vector_create(size_t size, size_t elemSize) {
  if (!elemSize) throw(IllegalArgumentException, "ElemSize must be greater than zero");

  Vector_t vec = Ibas.alloc(sizeof(Vector_s), NULL);
  if (!vec) throw(NotEnoughMemoryException, "Could not allocate the vector");

  if (size) {
    vec->storage = Ibas.alloc(size * elemSize, NULL);
  }

  vec->size = vec->capacity = size;
  vec->elemSize = elemSize;

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
  memcpy(__Vector_get(vec, i), val, vec->elemSize);
}

void __Vector_ensureCapacity(Vector_t vec, size_t capacity) {
  if (capacity <= vec->capacity) return;

  Object storage = realloc(vec->storage, capacity * vec->elemSize);
  if (!storage) throw(NotEnoughMemoryException, "Could not increase the vector's capacity");

  vec->storage = storage;
  vec->capacity = capacity;
}

void __Vector_insert(Vector_t vec, int i, Object val) {
  if (i < 0 || i > vec->size) throw(IllegalArgumentException, "Vector index out of bounds");

  if (vec->size == vec->capacity)
    __Vector_ensureCapacity(vec, max((int)(vec->capacity * VECTOR_GROWTH_FACTOR), vec->capacity + 1));

  Object ptr = vec->storage + i * vec->elemSize;
  memmove(ptr + vec->elemSize, ptr, vec->elemSize * (vec->size - i));
  memcpy(vec->storage + i * vec->elemSize, val, vec->elemSize);
  vec->size++;
}

void __Vector_add(Vector_t vec, Object val) {
  __Vector_insert(vec, (int) vec->size, val);
}

void __Vector_remove(Vector_t vec, int i) {
  Object ptr = __Vector_get(vec, i);
  memmove(ptr + vec->elemSize, ptr, vec->elemSize * (vec->size - i - 1));
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
  vec->size = 0;
}

//TODO implement
String_t __Vector_toString(Vector_t vec) {

}

Vector_t_ Vector = {
    genericListMethodsList(Vector),
    __Vector_ensureCapacity
};
