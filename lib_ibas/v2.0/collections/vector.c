//
// Created by Павел on 16.03.2017.
//

#include "vector.h"
#include "../base/base.h"

Vector_t __Vector_create(size_t capacity) {
  Vector_t vec = Vector.createPrimitive(capacity, sizeof(Pointer_t), Object.class);
  vec->primitive = false;
  return vec;
}

Vector_t __Vector_createPrimitive(size_t capacity, size_t elemSize, Class_t elemClass) {
  if (!elemSize) $throw(IllegalArgumentException, "Vector: elemSize must be greater than zero!");

  Vector_t self = Ibas.alloc(sizeof(Vector_s), NULL);

  self->class = Vector.class;
  self->size = self->capacity = 0;
  self->storage = NULL;
  self->elemSize = elemSize;
  self->elemClass = elemClass;
  self->primitive = true;

  Vector.ensureCapacity(self, capacity);

  return self;
}

void __Vector_destroy(Vector_t self) {
  if (!self) return;

  Vector.clear(self);
  free(self);
}

String_t __Vector_toString(Vector_t self) {
  if (!self->elemClass)
    return String.format("[[Vector size=%zd elemSize=%zd storage=%p]]", self->size, self->elemSize, self->storage);

  return List.toString(self, Vector.toList(self), self->elemClass->toString);
}

int __Vector_compare(Vector_t vec1, Vector_t vec2) {
  $throw(NotImplementedException, "Vector.compare() is not implemented!");
  return 0;
}

static void serialize(Vector_t self, Writer_t writer) {
  //TODO
}

static Vector_t deserialize(Vector_t self, Scanner_t scanner) {
  //TODO
}

List_i __Vector_toList(Vector_t self) {
  return (List_i) &Vector.toList;
}

Pointer_t __Vector_get(Vector_t self, int i) {
  if (i < 0 || i >= self->size) $throw(IllegalArgumentException, "Vector: index out of bounds!");

  return Vector.iterGet(self, Vector.iter(self, i));
}

void __Vector_set(Vector_t self, int i, Pointer_t val) {
  if (i < 0 || i >= self->size) $throw(IllegalArgumentException, "Vector: index out of bounds!");

  Vector.iterSet(self, Vector.iter(self, i), val);
}

void __Vector_insertSlice(Vector_t self, int i, Pointer_t slice, size_t size) {
  if (i < 0 || i > self->size) $throw(IllegalArgumentException, "Vector: index out of bounds!");

  size_t cap = self->capacity;
  while (cap < self->size + size) {
    cap = $max((size_t)(cap * VECTOR_GROWTH_FACTOR), cap + 1);
  }
  Vector.ensureCapacity(self, cap);

  Pointer_t ptr = self->storage + i * self->elemSize;
  memmove(ptr + size * self->elemSize, ptr, self->elemSize * (self->size - i));
  memcpy(ptr, slice, size * self->elemSize);
  self->size += size;
}

void __Vector_add(Vector_t self, Pointer_t val) {
  Vector.insert(self, (int) self->size, val);
}

void __Vector_insert(Vector_t self, int i, Pointer_t val) {
  __Vector_insertSlice(self, i, self->primitive? val : &val, 1);
}

void __Vector_addAll(Vector_t self, Vector_t vec) {
  Vector.insertAll(self, (int) self->size, vec);
}

void __Vector_insertAll(Vector_t self, int i, Vector_t vec) {
  if (self->elemSize != vec->elemSize) $throw(IllegalArgumentException, "Vector: element sizes don't match!");

  __Vector_insertSlice(self, i, vec->storage, vec->size);
}

void __Vector_remove(Vector_t self, int i) {
  Pointer_t ptr = Vector.get(self, i);
  memmove(ptr, ptr + self->elemSize, self->elemSize * (self->size - i - 1));
  self->size--;
}

void __Vector_clear(Vector_t self) {
  free(self->storage);

  self->size = self->capacity = 0;
  self->storage = NULL;
}

size_t __Vector_size(Vector_t self) {
  return self->size;
}

int __Vector_iterToIndex(Vector_t self, Object_t iter) {
  return (int) ((iter - self->storage) / self->elemSize);
}

int __Vector_indexOf(Vector_t self, Pointer_t val) {
  Object_t iter = Vector.find(self, val);

  if(iter == Vector.end(self)) return -1;
  else return __Vector_iterToIndex(self, iter);
}

Object_t __Vector_iter(Vector_t self, int i) {
  if (i < 0 || i >= self->size) return Vector.end(self);
  else return self->storage + i * self->elemSize;
}

Object_t __Vector_begin(Vector_t self) {
  return self->storage;
}

Object_t __Vector_end(Vector_t self) {
  return self->storage + self->size * self->elemSize;
}

Object_t __Vector_find(Vector_t self, Pointer_t val) {
  if (!self->elemClass)
    $throw(UnsupportedOperationException, "Vector: no comparator defined!");

  Object_t it = Vector.begin(self);
  for (; it != Vector.end(self); it = Vector.iterNext(self, it)) {
    if (!self->elemClass->compare(Vector.iterGet(self, it), val)) break;
  }

  return it;
}

Object_t __Vector_iterNext(Vector_t self, Object_t iter) {
  return Vector.iterJump(self, iter, 1);
}

Object_t __Vector_iterPrev(Vector_t self, Object_t iter) {
  return Vector.iterJump(self, iter, -1);
}

Object_t __Vector_iterJump(Vector_t self, Object_t iter, int length) {
  return Vector.iter(self, __Vector_iterToIndex(self, iter) + length);
}

Pointer_t __Vector_iterGet(Vector_t self, Object_t iter) {
  return self->primitive ? iter : *(Pointer_t *) iter;
}

void __Vector_iterSet(Vector_t self, Object_t iter, Pointer_t val) {
  memcpy(iter, self->primitive? val : &val, self->elemSize);
}

void __Vector_iterInsert(Vector_t self, Object_t iter, Pointer_t val) {
  Vector.insert(self, __Vector_iterToIndex(self, iter), val);
}

void __Vector_iterInsertAll(Vector_t self, Object_t iter, Vector_t vec) {
  Vector.insertAll(self, __Vector_iterToIndex(self, iter), vec);
}

void __Vector_iterRemove(Vector_t self, Object_t iter) {
  Vector.remove(self, __Vector_iterToIndex(self, iter));
}

void __Vector_ensureCapacity(Vector_t self, size_t capacity) {
  if (capacity <= self->capacity) return;

  Pointer_t storage = realloc(self->storage, capacity * self->elemSize);
  if (!storage) $throw(NotEnoughMemoryException, "Could not increase the vector's capacity");

  self->storage = storage;
  self->capacity = capacity;
}

static Compare_t sortComparator;

static int objCompare(Pointer_t *ptr1, Pointer_t *ptr2) {
  return sortComparator(*ptr1, *ptr2);
}

//TODO test
void __Vector_sort(Vector_t self, Compare_t comparator) {
  if (!comparator && !self->elemClass)
    $throw(UnsupportedOperationException, "Vector: no comparator defined!");

  if (!comparator) comparator = self->elemClass->compare;

  Compare_t tmpComp = sortComparator;
  if (!self->primitive) {
    sortComparator = comparator;
    comparator = (Compare_t) objCompare;
  }

  //@formatter:off
  $try {
    qsort(self->storage, self->size, self->elemSize, (int (*)(const void *, const void *)) comparator);
  } $finally {
    sortComparator = tmpComp;
  };
  //@formatter:off
}

$defineNamespace(Vector) {
    (Class_t) &Vector.destroy,
    __Vector_create,
    __Vector_createPrimitive,
    __Vector_destroy,
    __Vector_toString,
    __Vector_compare,
    serialize,
    deserialize,
    __Vector_toList,
    __Vector_get,
    __Vector_set,
    __Vector_add,
    __Vector_insert,
    __Vector_addAll,
    __Vector_insertAll,
    __Vector_remove,
    __Vector_clear,
    __Vector_size,
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
    __Vector_iterRemove,
    __Vector_ensureCapacity,
    __Vector_sort
};
