//
// Created by Павел on 21.03.2017.
//

#pragma once

#include "linked-list.h"

#define genericLinkedListDeclaration(class, elemType) \
  typedef LinkedList_t class##_t; \
   \
  declareClass(class, { \
    LinkedList_t (*create)(); \
    void (*destroy)(LinkedList_t list); \
    String_t (*toString)(LinkedList_t list); \
     \
    elemType (*get)(LinkedList_t list, int i); \
    void (*set)(LinkedList_t list, int i, elemType val); \
     \
    void (*add)(LinkedList_t list, elemType val); \
    void (*insert)(LinkedList_t list, int i, elemType val); \
    void (*addAll)(LinkedList_t list1, LinkedList_t list2); \
    void (*insertAll)(LinkedList_t list1, int i, LinkedList_t list2); \
     \
    void (*remove)(LinkedList_t list, int i); \
    void (*clear)(LinkedList_t list); \
     \
    int (*indexOf)(LinkedList_t list, elemType obj); \
     \
    Object (*iter)(LinkedList_t list, int i); \
    Object (*begin)(LinkedList_t list); \
    Object (*end)(LinkedList_t list); \
    Object (*find)(LinkedList_t list, elemType val); \
     \
    Object (*iterNext)(LinkedList_t list, Object iter); \
    Object (*iterPrev)(LinkedList_t list, Object iter); \
    Object (*iterJump)(LinkedList_t list, Object iter, int length); \
     \
    elemType (*iterGet)(LinkedList_t list, Object iter); \
    void (*iterSet)(LinkedList_t list, Object iter, elemType val); \
     \
    void (*iterInsert)(LinkedList_t list, Object iter, elemType val); \
    void (*iterInsertAll)(LinkedList_t list1, Object iter, LinkedList_t list2); \
     \
    void (*iterRemove)(LinkedList_t list, Object iter); \
  });


#define genericLinkedListInternals(class, elemType, toStringFn) \
  LinkedList_t __##class##_create() { \
    return LinkedList.create(sizeof(elemType), toStringFn); \
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
  int __##class##_indexOf(LinkedList_t list, elemType val) { \
    return LinkedList.indexOf(list, &val); \
  } \
   \
  Object __##class##_find(LinkedList_t list, elemType val) { \
    return LinkedList.find(list, &val); \
  } \
   \
  elemType __##class##_iterGet(LinkedList_t list, Object iter) { \
    return *(elemType*)LinkedList.iterGet(list, iter); \
  } \
   \
  void __##class##_iterSet(LinkedList_t list, Object iter, elemType val) { \
    LinkedList.iterSet(list, iter, &val); \
  } \
   \
  void __##class##_iterInsert(LinkedList_t list, Object iter, elemType val) { \
    LinkedList.iterInsert(list, iter, &val); \
  }


#define genericLinkedListImplementation(class, elemType, toStringFn) \
  genericLinkedListInternals(class, elemType, toStringFn); \
  class##_c class = { \
    __##class##_create, \
    __LinkedList_destroy, \
    __LinkedList_toString, \
    __##class##_get, \
    __##class##_set, \
    __##class##_add, \
    __##class##_insert, \
    __LinkedList_addAll, \
    __LinkedList_insertAll, \
    __LinkedList_remove, \
    __LinkedList_clear, \
    __##class##_indexOf, \
    __LinkedList_iter, \
    __LinkedList_begin, \
    __LinkedList_end, \
    __##class##_find, \
    __LinkedList_iterNext, \
    __LinkedList_iterPrev, \
    __LinkedList_iterJump, \
    __##class##_iterGet, \
    __##class##_iterSet, \
    __##class##_iterInsert, \
    __LinkedList_iterInsertAll, \
    __LinkedList_iterRemove \
  };
