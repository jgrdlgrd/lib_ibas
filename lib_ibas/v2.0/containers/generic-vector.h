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
    class##_t (*create)(size_t size); \
    void (*destroy)(class##_t vec); \
     \
    elemType (*get)(class##_t vec, int i); \
    void (*set)(class##_t vec, int i, elemType val); \
     \
    void (*add)(class##_t vec, elemType val); \
    void (*insert)(class##_t vec, int i, elemType val); \
    void (*remove)(class##_t vec, int i); \
     \
    void (*addAll)(class##_t vec1, class##_t vec2); \
    void (*insertAll)(class##_t vec1, int i, class##_t vec2); \
     \
    void (*forEach)(class##_t vec, bool (*func)(class##_t vec, elemType val, Object ctx), Object ctx); \
    int (*find)(class##_t vec, elemType val); \
     \
    void (*clear)(class##_t vec); \
    String_t (*toString)(class##_t vec); \
  })


/*
 * CLion shows an error after substituting this macro, but actually there's no error
 * TODO suppress the error (seems not possible)
 * maybe I should report a bug
 */
#define genericVectorInternals(class, elemType) \
  class##_t __##class##_create(size_t size) { \
    return Vector.create(size, sizeof(elemType)); \
  } \
   \
  void __##class##_destroy(class##_t vec) { \
    Vector.destroy(vec); \
  } \
   \
  elemType __##class##_get(class##_t vec, int i) { \
    return *(elemType*)Vector.get(vec, i); \
  } \
   \
  void __##class##_set(class##_t vec, int i, elemType val) { \
    Vector.set(vec, i, &val); \
  } \
   \
  void __##class##_add(class##_t vec, elemType val) { \
    Vector.add(vec, &val); \
  } \
   \
  void __##class##_insert(class##_t vec, int i, elemType val) { \
    Vector.insert(vec, i, &val); \
  } \
   \
  void __##class##_remove(class##_t vec, int i) { \
    Vector.remove(vec, i); \
  } \
   \
  void __##class##_addAll(class##_t vec1, class##_t vec2) { \
    Vector.addAll(vec1, vec2); \
  } \
   \
  void __##class##_insertAll(class##_t vec1, int i, class##_t vec2) { \
    Vector.insertAll(vec1, i, vec2); \
  } \
   \
  bool __##class##_forEachIntermediate(class##_t vec, Object element, Object ctx) { \
    Pair *p = (Pair*) ctx; \
    return ((bool(*)(class##_t, elemType, Object))(p->first))(vec, *(elemType*)element, p->second); \
  } \
   \
  void __##class##_forEach(class##_t vec, bool (*func)(class##_t vec, elemType element, Object ctx), Object ctx) { \
    Pair p = {func, ctx}; \
    Vector.forEach(vec, __##class##_forEachIntermediate, &p); \
  } \
   \
  int __##class##_find(class##_t vec, elemType val) { \
    return Vector.find(vec, &val); \
  } \
   \
  void __##class##_clear(class##_t vec) { \
    Vector.clear(vec); \
  } \
   \
  String_t __##class##_toString(class##_t vec) { \
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
    __##class##_addAll, \
    __##class##_insertAll, \
    __##class##_forEach, \
    __##class##_find, \
    __##class##_clear, \
    __##class##_toString \
  };
