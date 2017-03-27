//
// Created by Павел on 19.03.2017.
//

#pragma once

#include "../lib_ibas.h"

declareType(LinkedList, {
  size_t elemSize;
  int size;
  void *head;
})

declareClass(LinkedList, {
  LinkedList_t (*create)(size_t elemSize);
  void (*destroy)(LinkedList_t list);

  Object (*get)(LinkedList_t list, int i);
  void (*set)(LinkedList_t list, int i, Object val);

  void (*add)(LinkedList_t list, Object val);
  void (*insert)(LinkedList_t list, int i, Object val);
  void (*remove)(LinkedList_t list, int i);

  void (*forEach)(LinkedList_t list, bool (*func)(LinkedList_t list, Object element, Object ctx), Object ctx);
  int (*find)(LinkedList_t list, Object obj);

  void (*clear)(LinkedList_t list);

  String_t (*toString)(LinkedList_t list);
})
