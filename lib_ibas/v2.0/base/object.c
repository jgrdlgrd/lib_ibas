//
// Created by Павел on 14.05.2017.
//

#include "object.h"
#include "base.h"

void __Object_destroy(Object_t obj) {
  return Object.getClass(obj)->destroy(obj);
}

String_t __Object_toString(Object_t obj) {
  return Object.getClass(obj)->toString(obj);
}

int __Object_compare(Object_t obj1, Object_t obj2) {
  return Object.getClass(obj1)->compare(obj1, obj2);
}

Class_t __Object_getClass(Object_t obj) {
  return *(Class_t *) obj;
}

$defineNamespace(Object) {
    (Class_t) &Object.destroy,
    __Object_destroy,
    __Object_toString,
    __Object_compare,
    __Object_getClass,
};
