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
  void **nextPtr = list->head;
  while (nextPtr && !func(list, nextPtr + 1, ctx)) {
    nextPtr = *nextPtr;
  }
}

void __LinkedList_clear(LinkedList_t list) {
  void *nextPtr = list->head, *tmp;
  while (nextPtr) {
    tmp = nextPtr;
    nextPtr = *((void **) nextPtr);
    free(tmp);
  }
  list->size = 0;
}

void __LinkedList_destroy(LinkedList_t list) {
  if (list) {
    LinkedList.clear(list);
    free(list);
  }
}

Object __LinkedList_get(LinkedList_t list, int i) {
  if (i < 0 || i >= list->size) throw(IllegalArgumentException, "List index out of bounds");

  void **nextPtr = list->head;
  while (i > 0) {
    nextPtr = *nextPtr;
    i--;
  }

  return nextPtr + 1;
}

void __LinkedList_set(LinkedList_t list, int i, Object val) {
  Object node = LinkedList.get(list, i) - sizeof(void *);
  memcpy(node, val, list->elemSize);
}

void __LinkedList_insert(LinkedList_t list, int i, Object val) {
  if (i < 0 || i > list->size) throw(IllegalArgumentException, "List index out of bounds");

  Object *prev = &list->head;
  if (i > 0) {
    prev = LinkedList.get(list, i - 1) - sizeof(void *);
  }

  void **newNode = Ibas.alloc(sizeof(void *) + list->elemSize, NULL);

  Object next = *prev;
  *prev = newNode;
  *newNode = next;
  memcpy(newNode + 1, val, list->elemSize);
  list->size++;
}

void __LinkedList_add(LinkedList_t list, Object val) {
  LinkedList.insert(list, (int) list->size, val);
}

void __LinkedList_insertAll(LinkedList_t list1, int i, LinkedList_t list2) {
  if (list1->elemSize != list2->elemSize) throw(IllegalArgumentException, "LinkedList element sizes don't match!");

  for (int j = 0; j < list2->size; j++) {
    LinkedList.insert(list1, i++, LinkedList.get(list2, j));
  }
}

void __LinkedList_addAll(LinkedList_t list1, LinkedList_t list2) {
  LinkedList.insertAll(list1, (int) list1->size, list2);
}

void __LinkedList_remove(LinkedList_t list, int i) {
  if (i < 0 || i >= list->size) throw(IllegalArgumentException, "List index out of bounds");
  void ****prev;
  void *deleted;

  if (i == 0) {
    prev = deleted = list->head;
    list->head = *prev;
  } else {
    prev = LinkedList.get(list, i - 1) - sizeof(void *);
    deleted = **prev;

    if (i + 1 == list->size) *prev = NULL;
    else *prev = ***prev;
  }

  free(deleted);
  list->size--;
}

int __LinkedList_find(LinkedList_t list, Object obj) {
  int i = 0;
  void **nextPtr = list->head;

  while (i < list->size) {
    if (!memcmp(nextPtr + 1, obj, list->elemSize)) return i;

    nextPtr = *nextPtr;
    i++;
  }

  return -1;
}

String_t __LinkedList_toString(LinkedList_t list) {
  return String.format("[[LinkedList size=%zd elemSize=%zd head=%p]]", list->size, list->elemSize, list->head);
}

LinkedList_t_ LinkedList = {
    __LinkedList_create,
    __LinkedList_destroy,
    __LinkedList_toString,
    __LinkedList_get,
    __LinkedList_set,
    __LinkedList_add,
    __LinkedList_insert,
    __LinkedList_addAll,
    __LinkedList_insertAll,
    __LinkedList_remove,
    __LinkedList_clear,
    __LinkedList_forEach,
    __LinkedList_find
};
