//
// Created by Павел on 20.03.2017.
//

#include "string.h"

genericVectorInternals(_String, char)

String_t __String_toString(String_t str) {
  return str;
}

String_t __String_fromCStr(CString cstr) {
  String_t str = String.create(0);
  __Vector_insertSlice(str, 0, cstr, strlen(cstr));
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

String_t_ String = {
    ___String_create,
    ___String_destroy,
    __String_toString,
    ___String_get,
    ___String_set,
    ___String_add,
    ___String_insert,
    ___String_addAll,
    ___String_insertAll,
    ___String_remove,
    ___String_clear,
    ___String_forEach,
    ___String_find,
    ___String_ensureCapacity,
    __String_fromCStr,
    __String_concat,
    __String_appendCStr,
    __String_prependCStr
};
