//
// Created by Павел on 16.03.2017.
//

//TODO add slice, clone, removeRange...

#pragma once

#include "../fwd.h"
#include "list.h"

#define VECTOR_GROWTH_FACTOR 1.5

$defineType(Vector) {
  Class_t class;
  size_t size, elemSize, capacity;
  Pointer_t storage;
  bool primitive;
  Class_t elemClass;
};

$declareNamespace(Vector) {
  Class_t class;
  
  Vector_t (*create)(size_t capacity);
  Vector_t (*createPrimitive)(size_t capacity, size_t elemSize, Class_t elemClass);

  $ObjectMethods(Vector);
  
  $ListMethods(Vector, Pointer_t);

  void (*ensureCapacity)(Vector_t self, size_t capacity);
  void (*sort)(Vector_t self, Compare_t comparator);
};

//expose some internals
void __Vector_destroy(Vector_t self);
String_t __Vector_toString(Vector_t self);
void __Vector_ensureCapacity(Vector_t self, size_t capacity);
Pointer_t __Vector_get(Vector_t self, int i);
void __Vector_set(Vector_t self, int i, Pointer_t val);
void __Vector_insertSlice(Vector_t self, int i, Pointer_t slice, size_t size);
void __Vector_add(Vector_t self, Pointer_t val);
void __Vector_insert(Vector_t self, int i, Pointer_t val);
void __Vector_addAll(Vector_t self, Vector_t vec);
void __Vector_insertAll(Vector_t self, int i, Vector_t vec);
void __Vector_remove(Vector_t self, int i);
void __Vector_clear(Vector_t self);
size_t __Vector_size(Vector_t self);
int __Vector_indexOf(Vector_t self, Pointer_t val);
Object_t __Vector_iter(Vector_t self, int i);
Object_t __Vector_begin(Vector_t self);
Object_t __Vector_end(Vector_t self);
Object_t __Vector_find(Vector_t self, Pointer_t val);
Object_t __Vector_iterNext(Vector_t self, Object_t iter);
Object_t __Vector_iterPrev(Vector_t self, Object_t iter);
int __Vector_iterToIndex(Vector_t self, Object_t iter);
Object_t __Vector_iterJump(Vector_t self, Object_t iter, int length);
Pointer_t __Vector_iterGet(Vector_t self, Object_t iter);
void __Vector_iterSet(Vector_t self, Object_t iter, Pointer_t val);
void __Vector_iterInsert(Vector_t self, Object_t iter, Pointer_t val);
void __Vector_iterInsertAll(Vector_t self, Object_t iter, Vector_t vec);
void __Vector_iterRemove(Vector_t self, Object_t iter);
