//
// Created by Павел on 20.03.2017.
//

#include "ibas.h"
#include "../collections/generic-vector.h"

#define $class String

$defineClass(Vector)(
    $implements(List, 4)
);

$constructor (new)(size_t capacity)(
    self = Vector.new(sizeof(char), capacity + 1, NULL);
    $setClass(self, $class);
)

String_t $public (toString)()(
    return self;
)

void $public (ensureCapacity)(size_t capacity)(
    $super(ensureCapacity)(capacity + 1);
)

void $public (add)(Pointer val)(
    $call(self, add)(val);
    ((char *) self->storage)[self->size] = 0;
)

void __String_insert(String_t str, int i, char val) {
  $super->insert(str, i, &val);
  ((char *) str->storage)[str->size] = 0;
}

void __String_addAll(String_t str1, String_t str2) {
  Vector.addAll(str1, str2);
  ((char *) str1->storage)[str1->size] = 0;
}

void __String_insertAll(String_t str1, int i, String_t str2) {
  Vector.insertAll(str1, i, str2);
  ((char *) str1->storage)[str1->size] = 0;
}

void __String_remove(String_t str, int i) {
  Vector.remove(str, i);
  ((char *) str->storage)[str->size] = 0;
}

void __String_iterInsert(String_t str, Object_t iter, char val) {
  Vector.iterInsert(str, iter, &val);
  ((char *) str->storage)[str->size] = 0;
}

void __String_iterInsertAll(String_t str1, Object_t iter, String_t str2) {
  Vector.iterInsertAll(str1, iter, str2);
  ((char *) str1->storage)[str1->size] = 0;
}

void __String_iterRemove(String_t str, Object_t iter) {
  Vector.iterRemove(str, iter);
  ((char *) str->storage)[str->size] = 0;
}

String_t __String_format(CString format, ...) {
  va_list va;
  va_start(va, format);

  int size = vsnprintf(NULL, 0, format, va);
  if (size < 0) throw(IllegalArgumentException, "String.format() failed!");

  String_t str = String.create((size_t) size + 1);
  size = vsnprintf(str->storage, (size_t) size + 1, format, va);
  if (size < 0) throw(IllegalArgumentException, "String.format() failed!");
  str->size = (size_t) size;

  va_end(va);
  return str;
}

/*
 * out-of-place concatenation
 * creates a new string
 */
String_t __String_concat(String_t str1, String_t str2) {
  String_t str = String.new(str1->size + str2->size);
  String.addAll(str, str1);
  String.addAll(str, str2);
  return str;
}

void __String_appendCStr(String_t str, CString cstr) {
  __Vector_insertSlice(str, (int) str->size, cstr, strlen(cstr));
}

void __String_prependCStr(String_t str, CString cstr) {
  __Vector_insertSlice(str, 0, cstr, strlen(cstr));
}

genericVectorInternals(_String, char, NULL);

String_c String = {
    __String_create,
    __Vector_destroy,
    __String_toString,
    __String_ensureCapacity,
    ___String_get,
    ___String_set,
    __String_add,
    __String_insert,
    __String_addAll,
    __String_insertAll,
    __String_remove,
    __Vector_clear,
    ___String_indexOf,
    __Vector_iter,
    __Vector_begin,
    __Vector_end,
    ___String_find,
    __Vector_iterNext,
    __Vector_iterPrev,
    __Vector_iterJump,
    ___String_iterGet,
    ___String_iterSet,
    __String_iterInsert,
    __String_iterInsertAll,
    __String_iterRemove,
    __String_format,
    __String_concat,
    __String_appendCStr,
    __String_prependCStr
};

#undef class
