//
// Created by Павел on 20.03.2017.
//

#include "string.h"
#include "../collections/generic-vector.h"

String_t __String_create(size_t capacity) {
  Vector_t vec = Vector.create(sizeof(char), capacity, NULL);
  vec->class = &String_class;
  return vec;
}

String_t __String_toString(String_t str) {
  return str;
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
  String_t str = String.create(str1->size + str2->size);
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
    __Vector_ensureCapacity,
    ___String_get,
    ___String_set,
    ___String_add,
    ___String_insert,
    __Vector_addAll,
    __Vector_insertAll,
    __Vector_remove,
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
    ___String_iterInsert,
    __Vector_iterInsertAll,
    __Vector_iterRemove,
    __String_format,
    __String_concat,
    __String_appendCStr,
    __String_prependCStr
};

Pointer String_class[] = {implements(String, Object, 0),
                          implements(String, List, 4),
                          NULL};
