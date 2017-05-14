//
// Created by Павел on 20.03.2017.
//

#include "string.h"

/*---- WRAPPERS ----*/

String_t __String_create(size_t capacity) {
  String_t str = Vector.createPrimitive(capacity, sizeof(char), NULL);
  str->class = String.class;
  return str;
}

String_t __String_toString(String_t self) {
  return self;
}

int __String_compare(String_t str1, String_t str2) {
  return strcmp(String.CStr(str1), String.CStr(str2));
}

char __String_get(String_t self, int i) {
  return *(char *) Vector.get(self, i);
}

void __String_set(String_t self, int i, char val) {
  Vector.set(self, i, &val);
}

void __String_add(String_t self, char val) {
  Vector.add(self, &val);
}

void __String_insert(String_t self, int i, char val) {
  Vector.insert(self, i, &val);
}

int __String_indexOf(String_t self, char val) {
  return Vector.indexOf(self, &val);
}

Object_t __String_find(String_t self, char val) {
  return Vector.find(self, &val);
}

char __String_iterGet(String_t self, Object_t iter) {
  return *(char *) Vector.iterGet(self, iter);
}

void __String_iterSet(String_t self, Object_t iter, char val) {
  Vector.iterSet(self, iter, &val);
}

void __String_iterInsert(String_t self, Object_t iter, char val) {
  Vector.iterInsert(self, iter, &val);
}

List_i __String_toList(String_t self) {
  return (List_i) &String.toList;
}

/*---- METHODS ----*/

CString_t __String_CStr(String_t self) {
  //FIXME
  return self->storage;
}

void __String_appendCStr(String_t str, CString_t cstr) {
  __Vector_insertSlice(str, (int) str->size, cstr, strlen(cstr));
}

void __String_prependCStr(String_t str, CString_t cstr) {
  __Vector_insertSlice(str, 0, cstr, strlen(cstr));
}

/*---- STATIC ----*/

String_t __String_format(CString_t format, ...) {
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

$defineNamespace(String) {
    (Class_t) &String.destroy,
    __String_create,
    __String_format,
    __String_concat,
    __Vector_destroy,
    __String_toString,
    __String_compare,
    __String_toList,
    __String_get,
    __String_set,
    __String_add,
    __String_insert,
    __Vector_addAll,
    __Vector_insertAll,
    __Vector_remove,
    __Vector_clear,
    __Vector_size,
    __String_indexOf,
    __Vector_iter,
    __Vector_begin,
    __Vector_end,
    __String_find,
    __Vector_iterNext,
    __Vector_iterPrev,
    __Vector_iterJump,
    __String_iterGet,
    __String_iterSet,
    __String_iterInsert,
    __Vector_iterInsertAll,
    __Vector_iterRemove,
    __Vector_ensureCapacity,
    __String_CStr,
    __String_appendCStr,
    __String_prependCStr
};
