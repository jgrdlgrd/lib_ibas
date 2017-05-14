//
// Created by Павел on 19.03.2017.
//

#include "linked-list.h"
#include "../base/ibas.h"

#define __PTR_SIZE sizeof(Pointer)

#define $class LinkedList
$defineClass(
    $implements(Object, 1),
    $implements(List, 3)
);

//TODO only a madman would implement dynamic types in C
/*void __LinkedList_instanceCheck(LinkedList_t obj, bool typeOnly) {
  if (obj->class != &LinkedList) throw(IllegalArgumentException, "LinkedList: dynamic type check failed!");
  if (typeOnly) return;
  if ((LinkedList_t) obj->elemSize == 0) throw(IllegalArgumentException, "LinkedList: trying to operate on non-initialized instance!");
}*/

$constructor(size_t elemSize, ToString_t stringifier)(
  if (!elemSize) throw(IllegalArgumentException, "LinkedList: elemSize must be greater than zero!");
  $construct;

  self->size = 0;
  self->head = &self->head;
  self->tail = &self->tail;
  self->elemSize = elemSize;
  self->stringifier = stringifier;
)

void $public(destroy)()(
  if (!self) return;

  this->clear(self);
  free(self);
)

String_t $public(toString)()(
  if (self->stringifier) return List.toString(self, self->stringifier);
  else return String.format("[[LinkedList size=%zd elemSize=%zd head=%p tail=%p]]", self->size, self->elemSize, self->head, self->tail);
)

Pointer $public(get)(int i)(
  if (i < 0 || i >= self->size) throw(IllegalArgumentException, "LinkedList: index out of bounds!");

  return this->iterGet(self, this->iter(self, i));
)

void $public(set)(int i, Pointer val)(
  if (i < 0 || i >= self->size) throw(IllegalArgumentException, "LinkedList: index out of bounds!");

  this->iterSet(self, this->iter(self, i), val);
)

void $public(add)(Pointer val)(
  this->insert(self, (int) self->size, val);
)

void $public(insert)(int i, Pointer val)(
  if (i < 0 || i > self->size) throw(IllegalArgumentException, "LinkedList: index out of bounds!");

  this->iterInsert(self, this->iter(self, i), val);
)

void $public(addAll)(LinkedList_t list2)(
  this->insertAll(self, (int) self->size, list2);
)

void $public(insertAll)(int i, LinkedList_t list2)(
  if (i < 0 || i > self->size) throw(IllegalArgumentException, "LinkedList: index out of bounds!");

  this->iterInsertAll(self, this->iter(self, i), list2);
)

void $public(remove)(int i)(
  if (i < 0 || i >= self->size) throw(IllegalArgumentException, "LinkedList: index out of bounds!");

  this->iterRemove(self, this->iter(self, i));
)

void $public(clear)()(
  Pointer *nextPtr = self->head, tmp;
  while (nextPtr != &self->head) {
    tmp = nextPtr;
    nextPtr = *nextPtr;
    free(tmp);
  }

  self->size = 0;
  self->head = &self->head;
  self->tail = &self->tail;
)

int $public(indexOf)(Pointer val)(
  int i = 0;
  Object_t it = this->begin(self), end = this->end(self);

  for (; it != end; it = this->iterNext(self, it)) {
    if (!memcmp(this->iterGet(self, it), val, self->elemSize)) break;
    i++;
  }

  return it == end ? -1 : i;
)

Object_t $public(iter)(int i)(
  return this->iterJump(self, this->begin(self), i);
)

Object_t $public(begin)()(
  return self->head;
)

Object_t $public(end)()(
  return &self->head;
)

Object_t $public(find)(Pointer val)(
  Object_t it = this->begin(self);
  for (; it != this->end(self); it = this->iterNext(self, it)) {
    if (!memcmp(this->iterGet(self, it), val, self->elemSize)) break;
  }

  return it;
)

Object_t $public(iterNext)(Object_t iter)(
  return this->iterJump(self, iter, 1);
)

Object_t $public(iterPrev)(Object_t iter)(
  return this->iterJump(self, iter, -1);
)

Object_t $public(iterJump)(Object_t iter, int length)(
  Pointer *it = iter;
  bool reverse = length < 0;
  if (reverse) {
    length = -length;
    it++;
  }

  while (it != &self->head && it != &self->tail && length > 0) {
    it = *it;
    length--;
  }

  if (reverse) it--;
  return it;
)

Pointer $public(iterGet)(Object_t iter)(
  return iter + 2 * __PTR_SIZE;
)

void $public(iterSet)(Object_t iter, Pointer val)(
  memcpy(iter + 2 * __PTR_SIZE, val, self->elemSize);
)

void $public(iterInsert)(Object_t iter, Pointer val)(
  Pointer *next = iter;
  Pointer *prev = *(next + 1) - __PTR_SIZE;
  Pointer *new = Ibas.alloc(2 * __PTR_SIZE + self->elemSize, NULL);

  *prev = new;
  *new = next;

  *(next + 1) = new + 1;
  *(new + 1) = prev + 1;

  memcpy(new + 2, val, self->elemSize);
  self->size++;
)

void $public(iterInsertAll)(Object_t iter, LinkedList_t list2)(
  if (self->elemSize != list2->elemSize) throw(IllegalArgumentException, "LinkedList: element sizes don't match!");

  for (Object_t i = this->begin(list2); i != this->end(list2); i = this->iterNext(list2, i)) {
    this->iterInsert(self, iter, this->iterGet(list2, i));
  }
)

void $public(iterRemove)(Object_t iter)(
  Pointer *deleted = iter;
  Pointer *prev = *(deleted + 1) - __PTR_SIZE;;
  Pointer *next = *deleted;

  *prev = next;
  *(next + 1) = prev + 1;

  free(deleted);
  self->size--;
)

LinkedList_c LinkedList = {
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
