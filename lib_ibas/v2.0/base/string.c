//
// Created by Павел on 20.03.2017.
//

#include "string.h"

String_t __String_create(size_t size) {
  return Vector.create(size, sizeof(char));
}

void __String_destroy(String_t str) {
  Vector.destroy(str);
}

char __String_get(String_t str, int i) {
  return *(char*)Vector.get(str, i);
}

void __String_set(String_t str, int i, char val) {
  Vector.set(str, i, &val);
}

void __String_add(String_t str, char val) {
  Vector.add(str, &val);
}

void __String_insert(String_t str, int i, char val) {
  Vector.insert(str, i, &val);
}

void __String_remove(String_t str, int i) {
  Vector.remove(str, i);
}

bool __String_forEachIntermediate(String_t str, Object element, Object ctx) {
  Pair *p = (Pair*) ctx;
  return ((bool(*)(String_t, char, Object))(p->first))(str, *(char*)element, p->second);
}

void __String_forEach(String_t str, bool (*func)(String_t str, char element, Object ctx), Object ctx) {
  Pair p = {func, ctx};
  Vector.forEach(str, __String_forEachIntermediate, &p);
}

int __String_find(String_t str, char val) {
  return Vector.find(str, &val);
}

void __String_clear(String_t str) {
  Vector.clear(str);
}

//TODO implement
void __String_concat(String_t str1, String_t str2) {

}

void __String_appendCStr(String_t str1, CString str2) {

}

void __String_prependCStr(String_t str2, CString str1) {

}

String_t_ String = {
    __String_create,
    __String_destroy,
    __String_get,
    __String_set,
    __String_add,
    __String_insert,
    __String_remove,
    __String_forEach,
    __String_find,
    __String_clear,
    __String_concat,
    __String_appendCStr,
    __String_prependCStr
};
