//
// Created by Павел on 19.03.2017.
//

#pragma once

#include "../lib_ibas.h"

declareType(LinkedList, {
  size_t elemSize;
  size_t size;
  void *head;
})

declareClass(LinkedList, {
  LinkedList_t (*create)(size_t elemSize);
  void (*destroy)(LinkedList_t list);
  String_t (*toString)(LinkedList_t list);

  Object (*get)(LinkedList_t list, int i);
  void (*set)(LinkedList_t list, int i, Object val);

  void (*add)(LinkedList_t list, Object val);
  void (*insert)(LinkedList_t list, int i, Object val);
  void (*addAll)(LinkedList_t list1, LinkedList_t list2);
  void (*insertAll)(LinkedList_t list1, int i, LinkedList_t list2);

  void (*remove)(LinkedList_t list, int i);
  void (*clear)(LinkedList_t list);

  void (*forEach)(LinkedList_t list, bool (*func)(LinkedList_t list, Object element, Object ctx), Object ctx);
  int (*find)(LinkedList_t list, Object obj);
})

//export internals
LinkedList_t __LinkedList_create(size_t elemSize);
void __LinkedList_forEach(LinkedList_t list, bool (*func)(LinkedList_t list, Object element, Object ctx), Object ctx);
void __LinkedList_clear(LinkedList_t list);
void __LinkedList_destroy(LinkedList_t list);
Object __LinkedList_get(LinkedList_t list, int i);
void __LinkedList_set(LinkedList_t list, int i, Object val);
void __LinkedList_insert(LinkedList_t list, int i, Object val);
void __LinkedList_add(LinkedList_t list, Object val);
void __LinkedList_insertAll(LinkedList_t list1, int i, LinkedList_t list2);
void __LinkedList_addAll(LinkedList_t list1, LinkedList_t list2);
void __LinkedList_remove(LinkedList_t list, int i);
int __LinkedList_find(LinkedList_t list, Object obj);
String_t __LinkedList_toString(LinkedList_t list);
