//
// Created by Павел on 21.03.2017.
//

#pragma once

#include "../lib_ibas.h"
#include "vector.h"

#define genericVectorDeclaration(class, elemType) \
  typedef Vector_t class##_t; \
   \
  declareClass(class, { \
    Vector_t (*create)(size_t size); \
    void (*destroy)(Vector_t vec); \
     \
    elemType (*get)(Vector_t vec, int i); \
    void (*set)(Vector_t vec, int i, elemType val); \
     \
    void (*add)(Vector_t vec, elemType val); \
    void (*insert)(Vector_t vec, int i, elemType val); \
    void (*remove)(Vector_t vec, int i); \
     \
    void (*forEach)(Vector_t vec, bool (*func)(Vector_t vec, elemType val, Object ctx), Object ctx); \
    int (*find)(Vector_t vec, elemType val); \
     \
    void (*clear)(Vector_t vec); \
    String_t (*toString)(Vector_t vec); \
  })


/*
 * CLion shows an error after substituting this macro, but actually there's no error
 * TODO suppress the error (seems not possible)
 * maybe I should report a bug
 */
#define genericVectorInternals(class, elemType) \
  Vector_t __##class##_create(size_t size) { \
    return Vector.create(size, sizeof(elemType)); \
  } \
   \
  void __##class##_destroy(Vector_t vec) { \
    Vector.destroy(vec); \
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
  void __##class##_remove(Vector_t vec, int i) { \
    Vector.remove(vec, i); \
  } \
   \
  bool __##class##_forEachIntermediate(Vector_t vec, Object element, Object ctx) { \
    Pair *p = (Pair*) ctx; \
    return ((bool(*)(Vector_t, elemType, Object))(p->first))(vec, *(elemType*)element, p->second); \
  } \
   \
  void __##class##_forEach(Vector_t vec, bool (*func)(Vector_t vec, elemType element, Object ctx), Object ctx) { \
    Pair p = {func, ctx}; \
    Vector.forEach(vec, __##class##_forEachIntermediate, &p); \
  } \
   \
  int __##class##_find(Vector_t vec, elemType val) { \
    return Vector.find(vec, &val); \
  } \
   \
  void __##class##_clear(Vector_t vec) { \
    Vector.clear(vec); \
  } \
   \
  String_t __##class##_toString(Vector_t vec) { \
    Vector.clear(vec); \
  }


#define genericVectorImplementation(class, elemType) \
  genericVectorInternals(class, type) \
  class##_t_ class = { \
    __##class##_create, \
    __##class##_destroy, \
    __##class##_get, \
    __##class##_set, \
    __##class##_add, \
    __##class##_insert, \
    __##class##_remove, \
    __##class##_forEach, \
    __##class##_find, \
    __##class##_clear, \
    __##class##_toString \
  };
