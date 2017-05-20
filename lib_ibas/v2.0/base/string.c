//
// Created by Павел on 20.03.2017.
//

#include "string.h"

/*---- WRAPPERS ----*/

static String_t create(size_t capacity) {
  String_t str = Vector.createPrimitive(capacity, sizeof(char), NULL);
  str->class = String.class;
  return str;
}

static String_t toString(String_t self) {
  return self;
}

static int compare(String_t str1, String_t str2) {
  return strcmp(String.CStr(str1), String.CStr(str2));
}

static char get(String_t self, int i) {
  return *(char *) Vector.get(self, i);
}

static void set(String_t self, int i, char val) {
  Vector.set(self, i, &val);
}

static void add(String_t self, char val) {
  Vector.add(self, &val);
}

static void insert(String_t self, int i, char val) {
  Vector.insert(self, i, &val);
}

static int indexOf(String_t self, char val) {
  return Vector.indexOf(self, &val);
}

static Object_t find(String_t self, char val) {
  return Vector.find(self, &val);
}

static char iterGet(String_t self, Object_t iter) {
  return *(char *) Vector.iterGet(self, iter);
}

static void iterSet(String_t self, Object_t iter, char val) {
  Vector.iterSet(self, iter, &val);
}

static void iterInsert(String_t self, Object_t iter, char val) {
  Vector.iterInsert(self, iter, &val);
}

static List_i toList(String_t self) {
  return (List_i) &String.toList;
}

/*---- METHODS ----*/

static CString_t CStr(String_t self) {
  //FIXME
  return self->storage;
}

void __Vector_insertSlice(Vector_t self, int i, Pointer_t slice, size_t size);

static void appendCStr(String_t str, CString_t cstr) {
  __Vector_insertSlice(str, (int) str->size, cstr, strlen(cstr));
}

static void prependCStr(String_t str, CString_t cstr) {
  __Vector_insertSlice(str, 0, cstr, strlen(cstr));
}

/*---- STATIC ----*/

static String_t format(CString_t format, ...) {
  va_list va;
  va_start(va, format);

  int size = vsnprintf(NULL, 0, format, va);
  if (size < 0) $throw(IllegalArgumentException, "String.format() failed!");

  String_t str = String.create((size_t) size + 1);
  size = vsnprintf(str->storage, (size_t) size + 1, format, va);
  if (size < 0) $throw(IllegalArgumentException, "String.format() failed!");
  str->size = (size_t) size;

  va_end(va);
  return str;
}

/*
 * out-of-place concatenation
 * creates a new string
 */
static String_t concat(String_t str1, String_t str2) {
  String_t str = String.create(str1->size + str2->size);
  String.addAll(str, str1);
  String.addAll(str, str2);
  return str;
}

void __Vector_destroy(Vector_t self);
void __Vector_addAll(Vector_t self, Vector_t vec);
void __Vector_insertAll(Vector_t self, int i, Vector_t vec);
void __Vector_remove(Vector_t self, int i);
void __Vector_clear(Vector_t self);
size_t __Vector_size(Vector_t self);
Pointer_t __Vector_iter(Vector_t self, int i);
Pointer_t __Vector_begin(Vector_t self);
Pointer_t __Vector_end(Vector_t self);
Pointer_t __Vector_iterNext(Vector_t self, Pointer_t iter);
Pointer_t __Vector_iterPrev(Vector_t self, Pointer_t iter);
Pointer_t __Vector_iterJump(Vector_t self, Pointer_t iter, int length);
void __Vector_iterInsertAll(Vector_t self, Pointer_t iter, Vector_t vec);
void __Vector_iterRemove(Vector_t self, Pointer_t iter);
void __Vector_ensureCapacity(Vector_t self, size_t capacity);

$defineNamespace(String) {
    (Class_t) &String.destroy,
    create,
    format,
    concat,
    __Vector_destroy,
    toString,
    compare,
    toList,
    get,
    set,
    add,
    insert,
    __Vector_addAll,
    __Vector_insertAll,
    __Vector_remove,
    __Vector_clear,
    __Vector_size,
    indexOf,
    __Vector_iter,
    __Vector_begin,
    __Vector_end,
    find,
    __Vector_iterNext,
    __Vector_iterPrev,
    __Vector_iterJump,
    iterGet,
    iterSet,
    iterInsert,
    __Vector_iterInsertAll,
    __Vector_iterRemove,
    __Vector_ensureCapacity,
    CStr,
    appendCStr,
    prependCStr
};
