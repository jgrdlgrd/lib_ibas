//
// Created by Павел on 19.03.2017.
//

#include "linked-list.h"

#define __PTR_SIZE sizeof(void *)

//TODO only a madman would implement dynamic types in C
/*void __LinkedList_instanceCheck(LinkedList_t obj, bool typeOnly) {
  if (obj->class != &LinkedList) throw(IllegalArgumentException, "LinkedList: dynamic type check failed!");
  if (typeOnly) return;
  if ((LinkedList_t) obj->elemSize == 0) throw(IllegalArgumentException, "LinkedList: trying to operate on non-initialized instance!");
}*/

LinkedList_t __LinkedList_create() {
  LinkedList_t list = Ibas.alloc(sizeof(LinkedList_s), NULL);

  list->class = &LinkedList;
  list->elemSize = list->size = 0;
  list->head = &list->head;
  list->tail = &list->tail;
  list->toStringFn = NULL;

  return list;
}

void __LinkedList_init(LinkedList_t list, size_t elemSize, ToString_t toStringFn) {
  if (!elemSize) throw(IllegalArgumentException, "LinkedList: elemSize must be greater than zero!");

  list->elemSize = elemSize;
  list->toStringFn = toStringFn;
}

void __LinkedList_destroy(LinkedList_t list) {
  if (!list) return;

  LinkedList.clear(list);
  free(list);
}

Object __LinkedList_get(LinkedList_t list, int i) {
  if (i < 0 || i >= list->size) throw(IllegalArgumentException, "LinkedList: index out of bounds!");

  return LinkedList.iterGet(list, LinkedList.iter(list, i));
}

void __LinkedList_set(LinkedList_t list, int i, Object val) {
  if (i < 0 || i >= list->size) throw(IllegalArgumentException, "LinkedList: index out of bounds!");

  LinkedList.iterSet(list, LinkedList.iter(list, i), val);
}

void __LinkedList_insert(LinkedList_t list, int i, Object val) {
  if (i < 0 || i > list->size) throw(IllegalArgumentException, "LinkedList: index out of bounds!");

  LinkedList.iterInsert(list, LinkedList.iter(list, i), val);
}

void __LinkedList_add(LinkedList_t list, Object val) {
  LinkedList.insert(list, (int) list->size, val);
}

void __LinkedList_insertAll(LinkedList_t list1, int i, LinkedList_t list2) {
  if (i < 0 || i > list1->size) throw(IllegalArgumentException, "LinkedList: index out of bounds!");
  LinkedList.iterInsertAll(list1, LinkedList.iter(list1, i), list2);
}

void __LinkedList_addAll(LinkedList_t list1, LinkedList_t list2) {
  LinkedList.insertAll(list1, (int) list1->size, list2);
}

void __LinkedList_remove(LinkedList_t list, int i) {
  if (i < 0 || i >= list->size) throw(IllegalArgumentException, "LinkedList: index out of bounds!");
  LinkedList.iterRemove(list, LinkedList.iter(list, i));
}

void __LinkedList_clear(LinkedList_t list) {
  void **nextPtr = list->head, *tmp;
  while (nextPtr != &list->head) {
    tmp = nextPtr;
    nextPtr = *nextPtr;
    free(tmp);
  }

  list->size = 0;
  list->head = &list->head;
  list->tail = &list->tail;
}

int __LinkedList_indexOf(LinkedList_t list, Object obj) {
  int i = 0;
  Object it = LinkedList.begin(list), end = LinkedList.end(list);

  for (; it != end; it = LinkedList.iterNext(list, it)) {
    if (!memcmp(LinkedList.iterGet(list, it), obj, list->elemSize)) break;
    i++;
  }

  return it == end ? -1 : i;
}

Object __LinkedList_iter(LinkedList_t list, int i) {
  return LinkedList.iterJump(list, LinkedList.begin(list), i);
}

Object __LinkedList_begin(LinkedList_t list) {
  return list->head;
}

Object __LinkedList_end(LinkedList_t list) {
  return &list->head;
}

Object __LinkedList_find(LinkedList_t list, Object obj) {
  Object it = LinkedList.begin(list);
  for (; it != LinkedList.end(list); it = LinkedList.iterNext(list, it)) {
    if (!memcmp(LinkedList.iterGet(list, it), obj, list->elemSize)) break;
  }

  return it;
}

Object __LinkedList_iterGet(LinkedList_t list, Object iter) {
  return iter + 2 * __PTR_SIZE;
}

void __LinkedList_iterSet(LinkedList_t list, Object iter, Object val) {
  memcpy(iter + 2 * __PTR_SIZE, val, list->elemSize);
}

Object __LinkedList_iterNext(LinkedList_t list, Object iter) {
  return LinkedList.iterJump(list, iter, 1);
}

Object __LinkedList_iterPrev(LinkedList_t list, Object iter) {
  return LinkedList.iterJump(list, iter, -1);
}

Object __LinkedList_iterJump(LinkedList_t list, Object iter, int length) {
  void **it = iter;
  bool reverse = length < 0;
  if (reverse) {
    length = -length;
    it++;
  }

  while (it != &list->head && it != &list->tail && length > 0) {
    it = *it;
    length--;
  }

  if (reverse) it--;
  return it;
}

void __LinkedList_iterInsert(LinkedList_t list, Object iter, Object val) {
  void **next = iter;
  void **prev = *(next + 1) - __PTR_SIZE;
  void **new = Ibas.alloc(2 * __PTR_SIZE + list->elemSize, NULL);

  *prev = new;
  *new = next;

  *(next + 1) = new + 1;
  *(new + 1) = prev + 1;

  memcpy(new + 2, val, list->elemSize);
  list->size++;
}

void __LinkedList_iterInsertAll(LinkedList_t list1, Object iter, LinkedList_t list2) {
  if (list1->elemSize != list2->elemSize) throw(IllegalArgumentException, "LinkedList element sizes don't match!");

  for (Object i = LinkedList.begin(list2); i != LinkedList.end(list2); i = LinkedList.iterNext(list2, i)) {
    LinkedList.iterInsert(list1, iter, LinkedList.iterGet(list2, i));
  }
}

void __LinkedList_iterRemove(LinkedList_t list, Object iter) {
  void **deleted = iter;
  void **prev = *(deleted + 1) - __PTR_SIZE;;
  void **next = *deleted;

  *prev = next;
  *(next + 1) = prev + 1;

  free(deleted);
  list->size--;
}

String_t cts(LinkedList_t list, ToString_t tstr) {
  String_t str = String.fromCStr("[");

  for (Object i = LinkedList.begin(list); ; ) {
    String.addAll(str, tstr(LinkedList.iterGet(list, i)));

    i = LinkedList.iterNext(list, i);
    if (i == LinkedList.end(list)) break;

    String.appendCStr(str, ", ");
  }

  String.add(str, ']');
  /*TODO trim to size*/
  return str; \
}

String_t __LinkedList_toString(LinkedList_t list) {
  if (list->elemSize && list->toStringFn) return cts(list, list->toStringFn);
  else return String.format("[[LinkedList size=%zd elemSize=%zd head=%p tail=%p]]", list->size, list->elemSize, list->head, list->tail);
}

LinkedList_c LinkedList = {
    __LinkedList_create,
    __LinkedList_destroy,
    __LinkedList_toString,
    __LinkedList_init,
    __LinkedList_get,
    __LinkedList_set,
    __LinkedList_add,
    __LinkedList_insert,
    __LinkedList_addAll,
    __LinkedList_insertAll,
    __LinkedList_remove,
    __LinkedList_clear,
    __LinkedList_indexOf,
    __LinkedList_iter,
    __LinkedList_begin,
    __LinkedList_end,
    __LinkedList_find,
    __LinkedList_iterNext,
    __LinkedList_iterPrev,
    __LinkedList_iterJump,
    __LinkedList_iterGet,
    __LinkedList_iterSet,
    __LinkedList_iterInsert,
    __LinkedList_iterInsertAll,
    __LinkedList_iterRemove
};
