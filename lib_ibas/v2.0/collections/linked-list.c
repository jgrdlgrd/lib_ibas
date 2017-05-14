//
// Created by Павел on 19.03.2017.
//

#include "linked-list.h"
#include "../base/base.h"
#include "../io/console.h"

#define __PTR_SIZE sizeof(Pointer_t)

Compare_t __LinkedList_sortComparator;

LinkedList_t __LinkedList_create() {
  LinkedList_t list = LinkedList.createPrimitive(__PTR_SIZE, Object.class);
  list->primitive = false;
  return list;
}

LinkedList_t __LinkedList_createPrimitive(size_t elemSize, Class_t elemClass) {
  if (!elemSize) throw(IllegalArgumentException, "LinkedList: elemSize must be greater than zero!");

  LinkedList_t self = Ibas.alloc(sizeof(LinkedList_s), NULL);

  self->class = LinkedList.class;
  self->size = 0;
  self->head = &self->head;
  self->tail = &self->tail;
  self->elemSize = elemSize;
  self->elemClass = elemClass;
  self->primitive = true;

  return self;
}

void __LinkedList_destroy(LinkedList_t self) {
  if (!self) return;

  LinkedList.clear(self);
  free(self);
}

String_t __LinkedList_toString(LinkedList_t self) {
  if (!self->elemClass)
    return String.format("[[LinkedList size=%zd elemSize=%zd head=%p tail=%p]]", self->size, self->elemSize, self->head, self->tail);

  return List.toString(self, LinkedList.toList(self), self->elemClass->toString);
}

int __LinkedList_compare(LinkedList_t list1, LinkedList_t list2) {
  throw(NotImplementedException, "LinkedList.compare() is not implemented!");
}

List_i __LinkedList_toList(LinkedList_t self) {
  return (List_i) &LinkedList.toList;
}

Pointer_t __LinkedList_get(LinkedList_t self, int i) {
  if (i < 0 || i >= self->size) throw(IllegalArgumentException, "LinkedList: index out of bounds!");

  return LinkedList.iterGet(self, LinkedList.iter(self, i));
}

void __LinkedList_set(LinkedList_t self, int i, Pointer_t val) {
  if (i < 0 || i >= self->size) throw(IllegalArgumentException, "LinkedList: index out of bounds!");

  LinkedList.iterSet(self, LinkedList.iter(self, i), val);
}

void __LinkedList_add(LinkedList_t self, Pointer_t val) {
  LinkedList.insert(self, (int) self->size, val);
}

void __LinkedList_insert(LinkedList_t self, int i, Pointer_t val) {
  if (i < 0 || i > self->size) throw(IllegalArgumentException, "LinkedList: index out of bounds!");

  LinkedList.iterInsert(self, LinkedList.iter(self, i), val);
}

void __LinkedList_addAll(LinkedList_t self, LinkedList_t list) {
  LinkedList.insertAll(self, (int) self->size, list);
}

void __LinkedList_insertAll(LinkedList_t self, int i, LinkedList_t list) {
  if (i < 0 || i > self->size) throw(IllegalArgumentException, "LinkedList: index out of bounds!");

  LinkedList.iterInsertAll(self, LinkedList.iter(self, i), list);
}

void __LinkedList_remove(LinkedList_t self, int i) {
  if (i < 0 || i >= self->size) throw(IllegalArgumentException, "LinkedList: index out of bounds!");

  LinkedList.iterRemove(self, LinkedList.iter(self, i));
}

void __LinkedList_clear(LinkedList_t self) {
  Pointer_t *nextPtr = self->head, tmp;
  while (nextPtr != &self->head) {
    tmp = nextPtr;
    nextPtr = *nextPtr;
    free(tmp);
  }

  self->size = 0;
  self->head = &self->head;
  self->tail = &self->tail;
}

size_t __LinkedList_size(LinkedList_t self) {
  return self->size;
}

int __LinkedList_indexOf(LinkedList_t self, Pointer_t val) {
  if (!self->elemClass)
    throw(UnsupportedOperationException, "LinkedList: no comparator defined!");

  int i = 0;
  Object_t it = LinkedList.begin(self), end = LinkedList.end(self);

  for (; it != end; it = LinkedList.iterNext(self, it)) {
    if (!self->elemClass->compare(LinkedList.iterGet(self, it), val)) break;
    i++;
  }

  return it == end ? -1 : i;
}

Object_t __LinkedList_iter(LinkedList_t self, int i) {
  return LinkedList.iterJump(self, LinkedList.begin(self), i);
}

Object_t __LinkedList_begin(LinkedList_t self) {
  return self->head;
}

Object_t __LinkedList_end(LinkedList_t self) {
  return &self->head;
}

Object_t __LinkedList_find(LinkedList_t self, Pointer_t val) {
  if (!self->elemClass)
    throw(UnsupportedOperationException, "LinkedList: no comparator defined!");

  Object_t it = LinkedList.begin(self);
  for (; it != LinkedList.end(self); it = LinkedList.iterNext(self, it)) {
    if (!self->elemClass->compare(LinkedList.iterGet(self, it), val)) break;
  }

  return it;
}

Object_t __LinkedList_iterNext(LinkedList_t self, Object_t iter) {
  return LinkedList.iterJump(self, iter, 1);
}

Object_t __LinkedList_iterPrev(LinkedList_t self, Object_t iter) {
  return LinkedList.iterJump(self, iter, -1);
}

Object_t __LinkedList_iterJump(LinkedList_t self, Object_t iter, int length) {
  Pointer_t *it = iter;
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
}

Pointer_t __LinkedList_iterGet(LinkedList_t self, Object_t iter) {
  return iter + 2 * __PTR_SIZE;
}

void __LinkedList_iterSet(LinkedList_t self, Object_t iter, Pointer_t val) {
  memcpy(iter + 2 * __PTR_SIZE, self->primitive? val : &val, self->elemSize);
}

void __LinkedList_iterInsert(LinkedList_t self, Object_t iter, Pointer_t val) {
  Pointer_t *next = iter;
  Pointer_t *prev = *(next + 1) - __PTR_SIZE;
  Pointer_t *new = Ibas.alloc(2 * __PTR_SIZE + self->elemSize, NULL);

  *prev = new;
  *new = next;

  *(next + 1) = new + 1;
  *(new + 1) = prev + 1;

  memcpy(new + 2, self->primitive? val : &val, self->elemSize);
  self->size++;
}

void __LinkedList_iterInsertAll(LinkedList_t self, Object_t iter, LinkedList_t list) {
  if (self->elemSize != list->elemSize) throw(IllegalArgumentException, "LinkedList: element sizes don't match!");

  for (Object_t i = LinkedList.begin(list); i != LinkedList.end(list); i = LinkedList.iterNext(list, i)) {
    LinkedList.iterInsert(self, iter, LinkedList.iterGet(list, i));
  }
}

void __LinkedList_iterRemove(LinkedList_t self, Object_t iter) {
  Pointer_t *deleted = iter;
  Pointer_t *prev = *(deleted + 1) - __PTR_SIZE;;
  Pointer_t *next = *deleted;

  *prev = next;
  *(next + 1) = prev + 1;

  free(deleted);
  self->size--;
}

int __LinkedList_sortCompare(Pointer_t *ptr1, Pointer_t *ptr2) {
  return __LinkedList_sortComparator(*ptr1, *ptr2);
}

void __LinkedList_sort(LinkedList_t self, Compare_t comparator) {
  if (!comparator && !self->elemClass)
    throw(UnsupportedOperationException, "LinkedList: no comparator defined!");

  Compare_t tmpComp = __LinkedList_sortComparator;
  __LinkedList_sortComparator = comparator ? comparator : self->elemClass->compare;

  //@formatter:off
  $withObj(Vector_t, vec) {
    vec = Vector.create(self->size);
  } use {
    Object_t iter = LinkedList.begin(self);
    while (iter != LinkedList.end(self)) {
      Vector.add(vec, LinkedList.iterGet(self, iter));
      iter = LinkedList.iterNext(self, iter);
    }

    Vector.sort(vec, (Compare_t) __LinkedList_sortCompare);

    iter = Vector.begin(vec);
    Pointer_t *prev = &self->head, *cur;

    while (iter != Vector.end(vec)) {
      cur = *(Pointer_t *) Vector.iterGet(vec, iter) - 2 * __PTR_SIZE;

      *prev = cur;
      *(cur + 1) = prev + 1;

      iter = Vector.iterNext(vec, iter);
      prev = cur;
    }

    cur = &self->head;
    *prev = cur;
    *(cur + 1) = prev + 1;
  } finally {
    __LinkedList_sortComparator = tmpComp;
  };
  //@formatter:off
}

String_t __LinkedList_toPrettyString(LinkedList_t self) {
  if (!self->elemClass)
    throw(UnsupportedOperationException, "LinkedList: no stringifier defined!");

  String_t str = NULL;

  //@formatter:off
  $withObjF(str) {
    str = String.create(0);
  } use {
    Object_t it = LinkedList.begin(self);
    if (it != LinkedList.end(self)) {
      while (true) {
        Object_t elem = LinkedList.iterGet(self, it);

        String.appendCStr(str, Colors.RED);
        String.add(str, '[');
        String.appendCStr(str, Colors.RESET);
        
        $withObj(String_t, str1) {
          str1 = self->elemClass->toString(elem);
        } use{
          String.addAll(str, str1);
        };

        String.appendCStr(str, Colors.RED);
        String.appendCStr(str, "]->");
        String.appendCStr(str, Colors.RESET);
  
        it = LinkedList.iterNext(self, it);
        if (it == LinkedList.end(self)) break;
      }
    }
  
    String.appendCStr(str, "NULL");
  };
  //@formatter:on

  return str;
}

$defineNamespace(LinkedList) {
    (Class_t) &LinkedList.destroy,
    __LinkedList_create,
    __LinkedList_createPrimitive,
    __LinkedList_destroy,
    __LinkedList_toString,
    __LinkedList_compare,
    __LinkedList_toList,
    __LinkedList_get,
    __LinkedList_set,
    __LinkedList_add,
    __LinkedList_insert,
    __LinkedList_addAll,
    __LinkedList_insertAll,
    __LinkedList_remove,
    __LinkedList_clear,
    __LinkedList_size,
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
    __LinkedList_iterRemove,
    __LinkedList_sort,
    __LinkedList_toPrettyString
};
