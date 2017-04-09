//
// Created by Павел on 19.03.2017.
//

#pragma once

#include "../fwd.h"
#include "list.h"

struct LinkedList {
  Object class;
  size_t elemSize, size;
  Pointer head, tail;
  ToString_t stringifier;
};

declareClass(LinkedList, {
  LinkedList_t (*create)(size_t elemSize, ToString_t stringifier);
  void (*destroy)(LinkedList_t list);
  String_t (*toString)(LinkedList_t list);

  ListMethods(LinkedList, list, Pointer);
});

//expose internals
LinkedList_t __LinkedList_create(size_t elemSize, ToString_t stringifier);
void __LinkedList_destroy(LinkedList_t list);
String_t __LinkedList_toString(LinkedList_t list);
Pointer __LinkedList_get(LinkedList_t list, int i);
void __LinkedList_set(LinkedList_t list, int i, Pointer val);
void __LinkedList_add(LinkedList_t list, Pointer val);
void __LinkedList_insert(LinkedList_t list, int i, Pointer val);
void __LinkedList_addAll(LinkedList_t list1, LinkedList_t list2);
void __LinkedList_insertAll(LinkedList_t list1, int i, LinkedList_t list2);
void __LinkedList_remove(LinkedList_t list, int i);
void __LinkedList_clear(LinkedList_t list);
int __LinkedList_indexOf(LinkedList_t list, Pointer val);
Object __LinkedList_iter(LinkedList_t list, int i);
Object __LinkedList_begin(LinkedList_t list);
Object __LinkedList_end(LinkedList_t list);
Object __LinkedList_find(LinkedList_t list, Pointer val);
Pointer __LinkedList_iterGet(LinkedList_t list, Object iter);
void __LinkedList_iterSet(LinkedList_t list, Object iter, Pointer val);
Object __LinkedList_iterNext(LinkedList_t list, Object iter);
Object __LinkedList_iterPrev(LinkedList_t list, Object iter);
Object __LinkedList_iterJump(LinkedList_t list, Object iter, int length);
void __LinkedList_iterInsert(LinkedList_t list, Object iter, Pointer val);
void __LinkedList_iterInsertAll(LinkedList_t list1, Object iter, LinkedList_t list2);
void __LinkedList_iterRemove(LinkedList_t list, Object iter);
