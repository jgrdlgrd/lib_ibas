//
// Created by Павел on 21.03.2017.
//

#pragma once

#include "vector.h"

#define genericVectorDeclaration(class, elemType) \
  typedef Vector_t class##_t; \
   \
  declareClass(class, { \
    Vector_t (*create)(size_t capacity); \
    void (*destroy)(Vector_t vec); \
    String_t (*toString)(Vector_t vec); \
     \
    void (*ensureCapacity)(Vector_t vec, size_t capacity); \
     \
    ListMethods(Vector, vec, elemType); \
  });


#define genericVectorInternals(class, elemType, stringifier) \
  Vector_t __##class##_create(size_t capacity) { \
    return Vector.create(sizeof(elemType), capacity, stringifier); \
  } \
   \
  elemType __##class##_get(Vector_t vec, int i) { \
    return *(elemType*)Vector.get(vec, i); \
  } \
   \
  void __##class##_set(Vector_t vec, int i, elemType val) { \
    Vector.set(vec, i, &val); \
  } \
   \
  void __##class##_add(Vector_t vec, elemType val) { \
    Vector.add(vec, &val); \
  } \
   \
  void __##class##_insert(Vector_t vec, int i, elemType val) { \
    Vector.insert(vec, i, &val); \
  } \
   \
  int __##class##_indexOf(Vector_t vec, elemType val) { \
    return Vector.indexOf(vec, &val); \
  } \
   \
  Object __##class##_find(Vector_t vec, elemType val) { \
    return Vector.find(vec, &val); \
  } \
   \
  elemType __##class##_iterGet(Vector_t vec, Object iter) { \
    return *(elemType*)Vector.iterGet(vec, iter); \
  } \
   \
  void __##class##_iterSet(Vector_t vec, Object iter, elemType val) { \
    Vector.iterSet(vec, iter, &val); \
  } \
   \
  void __##class##_iterInsert(Vector_t vec, Object iter, elemType val) { \
    Vector.iterInsert(vec, iter, &val); \
  }


#define genericVectorImplementation(class, elemType, stringifier) \
  genericVectorInternals(class, elemType, stringifier); \
  class##_c class = { \
    __##class##_create, \
    __Vector_destroy, \
    __Vector_toString, \
    __Vector_ensureCapacity, \
    __##class##_get, \
    __##class##_set, \
    __##class##_add, \
    __##class##_insert, \
    __Vector_addAll, \
    __Vector_insertAll, \
    __Vector_remove, \
    __Vector_clear, \
    __##class##_indexOf, \
    __Vector_iter, \
    __Vector_begin, \
    __Vector_end, \
    __##class##_find, \
    __Vector_iterNext, \
    __Vector_iterPrev, \
    __Vector_iterJump, \
    __##class##_iterGet, \
    __##class##_iterSet, \
    __##class##_iterInsert, \
    __Vector_iterInsertAll, \
    __Vector_iterRemove \
  };
