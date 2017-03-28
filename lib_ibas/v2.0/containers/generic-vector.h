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
    String_t (*toString)(class##_t vec); \
     \
    elemType (*get)(class##_t vec, int i); \
    void (*set)(class##_t vec, int i, elemType val); \
     \
    void (*add)(class##_t vec, elemType val); \
    void (*insert)(class##_t vec, int i, elemType val); \
    void (*addAll)(class##_t vec1, class##_t vec2); \
    void (*insertAll)(class##_t vec1, int i, class##_t vec2); \
     \
    void (*remove)(class##_t vec, int i); \
    void (*clear)(class##_t vec); \
     \
    void (*forEach)(class##_t vec, bool (*func)(class##_t vec, elemType val, Object ctx), Object ctx); \
    int (*find)(class##_t vec, elemType val); \
     \
    void (*ensureCapacity)(class##_t vec, size_t capacity); \
  })


/*
 * CLion shows an error after substituting this macro, but actually there's no error
 * TODO suppress the error (seems not possible)
 * maybe I should report a bug
 */
#define genericVectorInternals(class, elemType, toString_) \
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
  void __##class##_addAll(Vector_t vec1, Vector_t vec2) { \
    Vector.addAll(vec1, vec2); \
  } \
   \
  void __##class##_insertAll(Vector_t vec1, int i, Vector_t vec2) { \
    Vector.insertAll(vec1, i, vec2); \
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
  void __##class##_ensureCapacity(Vector_t vec, size_t capacity) { \
    Vector.ensureCapacity(vec, capacity); \
  } \
   \
  String_t __##class##_toString(Vector_t vec) { \
    if (toString_) { \
      String_t (*toStr)(elemType elem) = toString_; \
      String_t str = String.fromCStr("["); \
      for (int i = 0; i < vec->size; i++) {\
        String.addAll(str, toStr(__##class##_get(vec, i))); \
        if (i < vec->size - 1) String.appendCStr(str, ", "); \
      } \
      String.add(str, ']'); \
      /*TODO trim to size*/ \
      return str; \
    } \
    return Vector.toString(vec); \
  }


#define genericVectorImplementation(class, elemType, toString) \
  genericVectorInternals(class, elemType, toString) \
  class##_t_ class = { \
    __##class##_create, \
    __##class##_destroy, \
    __##class##_toString, \
    __##class##_get, \
    __##class##_set, \
    __##class##_add, \
    __##class##_insert, \
    __##class##_addAll, \
    __##class##_insertAll, \
    __##class##_remove, \
    __##class##_clear, \
    __##class##_forEach, \
    __##class##_find, \
    __##class##_ensureCapacity \
  };
