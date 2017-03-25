//
// Created by Павел on 19.03.2017.
//

#include "linked-list.h"

LinkedList_t __LinkedList_create(size_t elemSize) {
  if (!elemSize) throw(IllegalArgumentException, "ElemSize must be greater than zero");

  LinkedList_t list = Ibas.alloc(sizeof(LinkedList_s), NULL);

  list->elemSize = elemSize;
  list->size = 0;
  list->head = NULL;

  return list;
}

void __LinkedList_forEach(LinkedList_t list, bool (*func)(LinkedList_t list, Object element, Object ctx), Object ctx) {
  void *nextPtr = list->head;
  while (nextPtr && !func(list, nextPtr, ctx)) {
    nextPtr = *((void **) nextPtr);
  }
}

bool __LinkedList_freeNode(LinkedList_t list, Object element, Object ctx) {
  free(element - sizeof(void *));
  return false;
}

void __LinkedList_clear(LinkedList_t list) {
  __LinkedList_forEach(list, __LinkedList_freeNode, NULL);
  list->size = 0;
}

void __LinkedList_destroy(LinkedList_t list) {
  if (list) {
    __LinkedList_clear(list);
    free(list);
  }
}

Object __LinkedList_get(LinkedList_t list, int i) {
  if (i < 0 || i >= list->size) throw(IllegalArgumentException, "List index out of bounds");

  void *nextPtr = list->head;
  while (i > 0) {
    nextPtr = *((void **) nextPtr);
    i--;
  }

  return nextPtr + sizeof(void *);
}

void __LinkedList_set(LinkedList_t list, int i, Object val) {
  Object node = __LinkedList_get(list, i) - sizeof(void *);
  memcpy(node + sizeof(void *), val, list->elemSize);
}

void __LinkedList_insert(LinkedList_t list, int i, Object val) {
  if (i < 0 || i > list->size) throw(IllegalArgumentException, "List index out of bounds");

  Object *prev = &list->head;
  if (i > 0) {
    prev = __LinkedList_get(list, i - 1);
  }

  Object *newNode = Ibas.alloc(sizeof(void *) + list->elemSize, NULL);

  Object tmp = *prev;
  *prev = newNode;
  *newNode = tmp;
  memcpy(newNode + sizeof(void *), val, list->elemSize);
}

void __LinkedList_add(LinkedList_t list, Object val) {
  __LinkedList_insert(list, list->size, val);
}

void __LinkedList_remove(LinkedList_t list, int i) {
  if (i < 0 || i >= list->size) throw(IllegalArgumentException, "List index out of bounds");

  Object *prev = &list->head;
  if (i > 0) {
    prev = __LinkedList_get(list, i - 1);
  }

  *prev = **(Object **) prev;
  free(*prev);
}

int __LinkedList_find(LinkedList_t list, Object obj) {
  int i = 0;
  void *nextPtr = list->head;

  while (i < list->size) {
    if (!memcmp(nextPtr + sizeof(void *), obj, list->elemSize)) return i;

    nextPtr = *((void **) nextPtr);
    i++;
  }

  return -1;
}

//TODO implement
String_t __LinkedList_toString(LinkedList_t list) {
  String_t str = String.create(20);
  return str;
}

LinkedList_t_ LinkedList = {
    __LinkedList_create,
    __LinkedList_destroy,
    __LinkedList_get,
    __LinkedList_set,
    __LinkedList_add,
    __LinkedList_insert,
    __LinkedList_remove,
    __LinkedList_forEach,
    __LinkedList_find,
    __LinkedList_clear,
    __LinkedList_toString
};
