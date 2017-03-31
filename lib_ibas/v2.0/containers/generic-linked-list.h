//
// Created by Павел on 21.03.2017.
//

#pragma once

#include "../lib_ibas.h"
#include "linked-list.h"

#define genericLinkedListDeclaration(class, elemType) \
  typedef LinkedList_t class##_t; \
   \
  declareClass(class, { \
    class##_t (*create)(); \
    void (*destroy)(class##_t list); \
    String_t (*toString)(class##_t list); \
     \
    elemType (*get)(class##_t list, int i); \
    void (*set)(class##_t list, int i, elemType val); \
     \
    void (*add)(class##_t list, elemType val); \
    void (*insert)(class##_t list, int i, elemType val); \
    void (*addAll)(class##_t list1, class##_t list2); \
    void (*insertAll)(class##_t list1, int i, class##_t list2); \
     \
    void (*remove)(class##_t list, int i); \
    void (*clear)(class##_t list); \
     \
    void (*forEach)(class##_t list, bool (*func)(class##_t list, elemType val, Object ctx), Object ctx); \
    int (*find)(class##_t list, elemType val); \
  })


/*
 * CLion shows an error after substituting this macro, but actually there's no error
 * TODO suppress the error (seems not possible)
 * maybe I should report a bug
 */
#define genericLinkedListInternals(class, elemType, toString_) \
  LinkedList_t __##class##_create() { \
    return LinkedList.create(sizeof(elemType)); \
  } \
   \
  elemType __##class##_get(LinkedList_t list, int i) { \
    return *(elemType*)LinkedList.get(list, i); \
  } \
   \
  void __##class##_set(LinkedList_t list, int i, elemType val) { \
    LinkedList.set(list, i, &val); \
  } \
   \
  void __##class##_add(LinkedList_t list, elemType val) { \
    LinkedList.add(list, &val); \
  } \
   \
  void __##class##_insert(LinkedList_t list, int i, elemType val) { \
    LinkedList.insert(list, i, &val); \
  } \
   \
  bool __##class##_forEachIntermediate(LinkedList_t list, Object element, Object ctx) { \
    Pair *p = (Pair*) ctx; \
    return ((bool(*)(LinkedList_t, elemType, Object))(p->first))(list, *(elemType*)element, p->second); \
  } \
   \
  void __##class##_forEach(LinkedList_t list, bool (*func)(LinkedList_t list, elemType element, Object ctx), Object ctx) { \
    Pair p = {func, ctx}; \
    LinkedList.forEach(list, __##class##_forEachIntermediate, &p); \
  } \
   \
  int __##class##_find(LinkedList_t list, elemType val) { \
    return LinkedList.find(list, &val); \
  } \
   \
  String_t __##class##_toString(LinkedList_t list) { \
    if (toString_) { \
      String_t str = String.fromCStr("["); \
      for (int i = 0; i < list->size; i++) {\
        String.addAll(str, toString_(__##class##_get(list, i))); \
        if (i < list->size - 1) String.appendCStr(str, ", "); \
      } \
      String.add(str, ']'); \
      /*TODO trim to size*/ \
      return str; \
    } \
    return LinkedList.toString(list); \
  }


#define genericLinkedListImplementation(class, elemType, toString) \
  genericLinkedListInternals(class, elemType, toString) \
  class##_t_ class = { \
    __##class##_create, \
    __LinkedList_destroy, \
    __##class##_toString, \
    __##class##_get, \
    __##class##_set, \
    __##class##_add, \
    __##class##_insert, \
    __LinkedList_addAll, \
    __LinkedList_insertAll, \
    __LinkedList_remove, \
    __LinkedList_clear, \
    __##class##_forEach, \
    __##class##_find \
  };
