//
// Created by Павел on 20.03.2017.
//

#include "string.h"

String_t __String_toString(String_t str) {
  return str;
}

String_t __String_fromCStr(CString cstr) {
  String_t str = String.create(0);
  __Vector_insertSlice(str, 0, cstr, strlen(cstr));
  return str;
}

String_t __String_fromInt(int val) {
  return String.format("%d", val);
}

String_t __String_fromDouble(double val) {
  return String.format("%lf", val);
}

//TODO implement
String_t __String_fromObject(Object obj) {
  throw(RuntimeException, "Not implemented!");
}

String_t __String_format(CString format, ...) {
  va_list va;
  va_start(va, format);

  int size = vsnprintf(NULL, 0, format, va);
  if (size < 0) throw(IllegalArgumentException, "String.format() failed");

  String_t str = String.create((size_t) size + 1);
  size = vsnprintf(str->storage, (size_t) size + 1, format, va);
  if (size < 0) throw(IllegalArgumentException, "String.format() failed");
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
    ___String_create,
    __Vector_destroy,
    __String_toString,
    ___String_get,
    ___String_set,
    ___String_add,
    ___String_insert,
    __Vector_addAll,
    __Vector_insertAll,
    __Vector_remove,
    __Vector_clear,
    ___String_forEach,
    ___String_find,
    __Vector_ensureCapacity,
    __String_fromCStr,
    __String_fromInt,
    __String_fromDouble,
    __String_fromObject,
    __String_format,
    __String_concat,
    __String_appendCStr,
    __String_prependCStr
};
