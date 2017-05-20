//
// Created by Павел on 19.03.2017.
//

#include "linked-list.h"
#include "../base/base.h"
#include "../io/console.h"

#define PTR_SIZE sizeof(Pointer_t)

static Compare_t sortComparator;

static LinkedList_t create() {
  LinkedList_t list = LinkedList.createPrimitive(PTR_SIZE, Object.class);
  list->primitive = false;
  return list;
}

static LinkedList_t createPrimitive(size_t elemSize, Class_t elemClass) {
  if (!elemSize) $throw(IllegalArgumentException, "LinkedList: elemSize must be greater than zero!");

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

static void destroy(LinkedList_t self) {
  if (!self) return;

  LinkedList.clear(self);
  free(self);
}

static String_t toString(LinkedList_t self) {
  if (!self->elemClass)
    return String.format("[[LinkedList size=%zd elemSize=%zd head=%p tail=%p]]", self->size, self->elemSize, self->head, self->tail);

  return List.toString(self, LinkedList.toList(self), self->elemClass->toString);
}

static int compare(LinkedList_t list1, LinkedList_t list2) {
  $throw(NotImplementedException, "LinkedList.compare() is not implemented!");
  return 0;
}

static List_i toList(LinkedList_t self) {
  return (List_i) &LinkedList.toList;
}

static Pointer_t get(LinkedList_t self, int i) {
  if (i < 0 || i >= self->size) $throw(IllegalArgumentException, "LinkedList: index out of bounds!");

  return LinkedList.iterGet(self, LinkedList.iter(self, i));
}

static void set(LinkedList_t self, int i, Pointer_t val) {
  if (i < 0 || i >= self->size) $throw(IllegalArgumentException, "LinkedList: index out of bounds!");

  LinkedList.iterSet(self, LinkedList.iter(self, i), val);
}

static void add(LinkedList_t self, Pointer_t val) {
  LinkedList.insert(self, (int) self->size, val);
}

static void insert(LinkedList_t self, int i, Pointer_t val) {
  if (i < 0 || i > self->size) $throw(IllegalArgumentException, "LinkedList: index out of bounds!");

  LinkedList.iterInsert(self, LinkedList.iter(self, i), val);
}

static void addAll(LinkedList_t self, LinkedList_t list) {
  LinkedList.insertAll(self, (int) self->size, list);
}

static void insertAll(LinkedList_t self, int i, LinkedList_t list) {
  if (i < 0 || i > self->size) $throw(IllegalArgumentException, "LinkedList: index out of bounds!");

  LinkedList.iterInsertAll(self, LinkedList.iter(self, i), list);
}

static void remove_(LinkedList_t self, int i) {
  if (i < 0 || i >= self->size) $throw(IllegalArgumentException, "LinkedList: index out of bounds!");

  LinkedList.iterRemove(self, LinkedList.iter(self, i));
}

static void clear(LinkedList_t self) {
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

static size_t size_(LinkedList_t self) {
  return self->size;
}

static int indexOf(LinkedList_t self, Pointer_t val) {
  if (!self->elemClass)
    $throw(UnsupportedOperationException, "LinkedList: no comparator defined!");

  int i = 0;
  Pointer_t it = LinkedList.begin(self), end = LinkedList.end(self);

  for (; it != end; it = LinkedList.iterNext(self, it)) {
    if (!self->elemClass->compare(LinkedList.iterGet(self, it), val)) break;
    i++;
  }

  return it == end ? -1 : i;
}

static Pointer_t iter(LinkedList_t self, int i) {
  return LinkedList.iterJump(self, LinkedList.begin(self), i);
}

static Pointer_t begin(LinkedList_t self) {
  return self->head;
}

static Pointer_t end(LinkedList_t self) {
  return &self->head;
}

static Pointer_t find(LinkedList_t self, Pointer_t val) {
  if (!self->elemClass)
    $throw(UnsupportedOperationException, "LinkedList: no comparator defined!");

  Pointer_t it = LinkedList.begin(self);
  for (; it != LinkedList.end(self); it = LinkedList.iterNext(self, it)) {
    if (!self->elemClass->compare(LinkedList.iterGet(self, it), val)) break;
  }

  return it;
}

static Pointer_t iterNext(LinkedList_t self, Pointer_t iter) {
  return LinkedList.iterJump(self, iter, 1);
}

static Pointer_t iterPrev(LinkedList_t self, Pointer_t iter) {
  return LinkedList.iterJump(self, iter, -1);
}

static Pointer_t iterJump(LinkedList_t self, Pointer_t iter, int length) {
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

static Pointer_t iterGet(LinkedList_t self, Pointer_t iter) {
  return iter + 2 * PTR_SIZE;
}

static void iterSet(LinkedList_t self, Pointer_t iter, Pointer_t val) {
  memcpy(iter + 2 * PTR_SIZE, self->primitive? val : &val, self->elemSize);
}

static void iterInsert(LinkedList_t self, Pointer_t iter, Pointer_t val) {
  Pointer_t *next = iter;
  Pointer_t *prev = *(next + 1) - PTR_SIZE;
  Pointer_t *new = Ibas.alloc(2 * PTR_SIZE + self->elemSize, NULL);

  *prev = new;
  *new = next;

  *(next + 1) = new + 1;
  *(new + 1) = prev + 1;

  memcpy(new + 2, self->primitive? val : &val, self->elemSize);
  self->size++;
}

static void iterInsertAll(LinkedList_t self, Pointer_t iter, LinkedList_t list) {
  if (self->elemSize != list->elemSize) $throw(IllegalArgumentException, "LinkedList: element sizes don't match!");

  for (Pointer_t i = LinkedList.begin(list); i != LinkedList.end(list); i = LinkedList.iterNext(list, i)) {
    LinkedList.iterInsert(self, iter, LinkedList.iterGet(list, i));
  }
}

static void iterRemove(LinkedList_t self, Pointer_t iter) {
  Pointer_t *deleted = iter;
  Pointer_t *prev = *(deleted + 1) - PTR_SIZE;;
  Pointer_t *next = *deleted;

  *prev = next;
  *(next + 1) = prev + 1;

  free(deleted);
  self->size--;
}

static int sortCompare(Pointer_t *ptr1, Pointer_t *ptr2) {
  return sortComparator(*ptr1, *ptr2);
}

static void sort(LinkedList_t self, Compare_t comparator) {
  if (!comparator && !self->elemClass)
    $throw(UnsupportedOperationException, "LinkedList: no comparator defined!");

  Compare_t tmpComp = sortComparator;
  sortComparator = comparator ? comparator : self->elemClass->compare;

  //@formatter:off
  $withAuto(Vector_t, vec) {
    vec = Vector.create(self->size);
  } $use {
    Pointer_t iter = LinkedList.begin(self);
    while (iter != LinkedList.end(self)) {
      Vector.add(vec, LinkedList.iterGet(self, iter));
      iter = LinkedList.iterNext(self, iter);
    }

    Vector.sort(vec, (Compare_t) sortCompare);

    iter = Vector.begin(vec);
    Pointer_t *prev = &self->head, *cur;

    while (iter != Vector.end(vec)) {
      cur = *(Pointer_t *) Vector.iterGet(vec, iter) - 2 * PTR_SIZE;

      *prev = cur;
      *(cur + 1) = prev + 1;

      iter = Vector.iterNext(vec, iter);
      prev = cur;
    }

    cur = &self->head;
    *prev = cur;
    *(cur + 1) = prev + 1;
  } $finally {
    sortComparator = tmpComp;
  };
  //@formatter:off
}

static String_t toPrettyString(LinkedList_t self) {
  if (!self->elemClass)
    $throw(UnsupportedOperationException, "LinkedList: no stringifier defined!");

  String_t str = NULL;

  //@formatter:off
  $with(str) {
    str = String.create(0);
  } $use {
    Pointer_t it = LinkedList.begin(self);
    if (it != LinkedList.end(self)) {
      while (true) {
        Pointer_t elem = LinkedList.iterGet(self, it);

        String.appendCStr(str, Colors.RED);
        String.add(str, '[');
        String.appendCStr(str, Colors.RESET);
        
        $withAuto(String_t, str1) {
          str1 = self->elemClass->toString(elem);
        } $use {
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

#undef PTR_SIZE

$defineNamespace(LinkedList) {
    (Class_t) &LinkedList.destroy,
    create,
    createPrimitive,
    destroy,
    toString,
    compare,
    toList,
    get,
    set,
    add,
    insert,
    addAll,
    insertAll,
    remove_,
    clear,
    size_,
    indexOf,
    iter,
    begin,
    end,
    find,
    iterNext,
    iterPrev,
    iterJump,
    iterGet,
    iterSet,
    iterInsert,
    iterInsertAll,
    iterRemove,
    sort,
    toPrettyString
};
